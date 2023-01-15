import taichi as ti
from pathlib import Path
from platform import system

module_path = str(Path(__file__).parent.joinpath("module.tcm"))

ti.init(ti.metal if system() == "Darwin" else ti.vulkan)

@ti.kernel
def chessboard(arr: ti.types.ndarray(dtype=ti.u32, ndim=2)):
    for i, j in arr:
        arr[i, j] = (i % 2) ^ (j % 2)

arr = ti.ndarray(ti.u32, (4, 4))
chessboard(arr)
print(arr.to_numpy())

module = ti.aot.Module()
module.add_kernel(chessboard, template_args={ "arr": arr })
module.archive(module_path)
