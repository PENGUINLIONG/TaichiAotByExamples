import os
from pathlib import Path
import re

class Block:
    def __init__(self, ty: str):
        # top/header/text/cpp
        self.ty = ty
        self.indent = None
        self.lines = []

    def trim(self):
        """Remove trailing empty lines."""
        while self.lines and self.lines[-1] == "":
            self.lines.pop()

    def push_line(self, line: str, dont_indent: bool):
        # Ignore leading empty lines.
        if line.strip() == "" and not self.lines:
            return
        if self.indent is None and dont_indent == False:
            self.indent = len(line) - len(line.lstrip())
        if self.indent is not None and dont_indent == False:
            line = line[self.indent:]
        self.lines += [line]

class Document:
    def __init__(self, example_name: str) -> None:
        self.blocks = [Block("top")]
        self.example_name = example_name
        self.py_src_path = f"{example_name}/assets/module.py"
        self.cpp_src_path = f"{example_name}/main.cpp"
        self.title = "<untitled>"
        self.ref_log_path = f"tests/refs/{example_name}.log"
        self.url = f"https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/{self.example_name}"

    def _push_line(self, ty: str, line: str, dont_indent: bool=False):
        if self.blocks[-1].ty != ty:
            self.blocks += [Block(ty)]
        self.blocks[-1].push_line(line, dont_indent)

    def push_header(self, line: str):
        m = re.match(r"# Example \d+: (.*)", line.strip())
        if m:
            self.title = m[1]
        self._push_line("header", line)
    def push_text(self, line: str):
        self._push_line("text", line)
    def push_cpp(self, line: str):
        # Ignore opening scope braces. No need to worry about closing scope
        # braces because they won't be visible (shorter than indentation).
        if line.strip() == "{":
            return
        dont_indent = line.strip().startswith('#')
        self._push_line("cpp", line, dont_indent)
    def push_py(self, line: str):
        self._push_line("py", line)

    def trim_blocks(self):
        """Remove trailing empty lines in blocks"""
        for block in self.blocks:
            block.trim()
        i = 0
        while i < len(self.blocks):
            if not self.blocks[i].lines:
                del self.blocks[i]
            else:
                i += 1

    def lines(self):
        out = []
        for block in self.blocks:
            if block.ty == "top":
                pass
            elif block.ty == "header":
                out += block.lines
                out += [""]
            elif block.ty == "text":
                out += block.lines
                out += [""]
            elif block.ty == "cpp":
                out += ["```cpp"]
                out += block.lines
                out += ["```"]
                out += [""]
            elif block.ty == "py":
                out += [
                    "If you build a Taichi AOT module with the following Python script:",
                    "",
                    "```python",
                ]
                out += block.lines
                out += [
                    "```",
                    "",
                ]
            else:
                assert False, "unknown block type"

        if Path(self.ref_log_path).exists():
            out += [
                "The above C++ code may give the following output:",
                "",
                "```plaintext",
            ]
            with open(self.ref_log_path) as f:
                out += [line.strip() for line in f.readlines()]
            out += [
                "```",
                "",
            ]

        out += [f"> Check out this example on Github: [{self.url}]({self.url})"]
        return out

def read_cpp(doc: Document):
    with open(doc.cpp_src_path) as f:
        lines = f.readlines()

    # Ignore anything before the leading text block, except for the '//!'
    # header.
    i = 0
    while i < len(lines):
        line = lines[i]
        line_striped = line.strip()
        if line_striped.startswith("//!"):
            doc.push_header(line_striped[len("//!"):])
        if line_striped.startswith("///"):
            break
        i += 1

    for line in lines[i:]:
        line_striped = line.strip()

        if line_striped.startswith("///"):
            doc.push_text(line_striped[len("///"):])
        else:
            doc.push_cpp(line.rstrip())

def read_py(doc: Document):
    with open(doc.py_src_path) as f:
        lines = f.readlines()

    # Ignore lines before `ti.init`.
    i = 0
    while i < len(lines):
        line = lines[i]
        i += 1
        if "ti.init" in line:
            break

    for line in lines[i:]:
        doc.push_py(line.rstrip())


example_names = sorted(os.listdir("."))
titles = {}
for example_name in example_names:
    md_path = f"mdbook/src/examples/{example_name}.md"
    doc = Document(example_name)
    if not Path(doc.cpp_src_path).exists():
        continue

    read_cpp(doc)
    if Path(doc.py_src_path).exists():
        read_py(doc)

    titles[example_name] = doc.title

    doc.trim_blocks()

    content = '\n'.join(doc.lines())
    with open(md_path, 'w') as f:
        f.write(content)
        f.write('\n\n<sub>This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.</sub>')

with open("mdbook/src/SUMMARY.md", 'w') as f:
    out = [
        "# Summary",
        "",
        "# Taichi AOT by Examples",
        "",
    ]
    for example_name in example_names:
        if example_name in titles:
            out += [
                f"- [{titles[example_name]}](examples/{example_name}.md)"
            ]
    out += [""]
    f.write('\n'.join(out))
