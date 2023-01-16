# Taichi AOT by Examples

Learn Taichi AOT deployment with examples.

This book is available online at [https://liong.work/taichi-aot-by-examples.github.io/](https://liong.work/taichi-aot-by-examples.github.io/).

## Build and run the examples

To run the examples, you can either build all of them at once in the repository
root:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Or build each one of them:

```bash
cd 01-version # Note that we step into an example here.
mkdir build && cd build
cmake ..
cmake --build .
```

But either way, please run the examples with repository root as the working
directly, otherwise some hardcoded pahts might fail.

- [`mdBook`](https://github.com/rust-lang/mdBook)

Please do the following to 

- PowerShell 6.0+ (On *nix platforms too)
- CMake 3.10+
- Python 3.10+

## Testing

Every example has a copy of `stdout` log available in `tests/refs` as reference.
You can run `Test-AllExamples.ps1` to check if the current output matches the
log as expected. Or you can update the logs with
`Test-AllExamples.ps1 -UpdateLogs`.

## Publishing

If any example or referential output has been modified, you can update the
Markdown files in `mdbook/src` with `python scripts/extract-mdbook.py` and
push this book to a Github Pages repository with
`scripts/Publish-GithubPages.ps1`.

## License

Licensed under either of <a href="LICENSE-APACHE">Apache License, Version
2.0</a> or <a href="LICENSE-MIT">MIT license</a> at your option.

In addition, the generated textual content is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.

Unless you explicitly state otherwise, any contribution intentionally submitted
for inclusion in this crate by you, as defined in the Apache-2.0 license, shall
be dual licensed as above, without any additional terms or conditions.
