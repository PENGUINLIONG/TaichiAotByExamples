import taichi as ti
from pathlib import Path
from platform import system

module_path = str(Path(__file__).parent.joinpath("module.tcm"))

ti.init(ti.metal if system() == "Darwin" else ti.vulkan)

module = ti.aot.Module()
module.archive(module_path)
