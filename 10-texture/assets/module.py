import taichi as ti
from pathlib import Path
from platform import system

module_path = str(Path(__file__).parent.joinpath("module.tcm"))

ti.init(ti.metal if system() == "Darwin" else ti.vulkan)

@ti.kernel
def write_tex(tex: ti.types.rw_texture(2, fmt=ti.Format.r32f)):
    for i, j in tex:
        tex.store(ti.Vector([i, j]), ti.Vector([float((i % 2) ^ (j % 2)), 0.0, 0.0, 0.0]))

@ti.kernel
def sample_tex(arr: ti.types.ndarray(dtype=ti.u32, ndim=2), tex: ti.types.texture(2)):
    for i, j in arr:
        arr[i, j] = int(10 * tex.sample_lod(ti.Vector([(i + 0.5) / 4, (j + 0.5) / 4]), 0).x)

module = ti.aot.Module()
module.add_kernel(write_tex)
module.add_kernel(sample_tex)
module.archive(module_path)
