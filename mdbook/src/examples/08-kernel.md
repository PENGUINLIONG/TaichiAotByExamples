# Example 8: Kernel and Positional Argument

Taichi AOT modules may contain precompiled Taichi kernels. You can extract
the kernels by their names.

For example, we have a kernel called `chessboard` that prints a chessboard
pattern of interleaving zeros and ones to an ND-array.

```cpp
ti::AotModule aot_module =
    runtime.load_aot_module("08-kernel/assets/module.tcm");
ti::Kernel k_chessboard = aot_module.get_kernel("chessboard");
```

To launch the kernel, we first need to assign the positional arguments.
There are two ways to setup kernel arguments.
First, you can assign arguments by their indices. This is the best if
you have many arguments but only few of them are updated frequently.

```cpp
k_chessboard[0] = arr;
```

If the argument list frequently changes, like when you are prototyping
a new algorithm. You might want to clear and sequentially set the list
of argument so you don't have to reorder the indices all the time.

```cpp
k_chessboard.clear_args();
k_chessboard.push_arg(arr);
```

When all the arguments are ready, you can launch the kernel with
`launch()`. Kernel launch is a device command, so it will be pushed to the
default queue of `runtime`.

```cpp
k_chessboard.launch();
```

Remind that, we don't know if a device command has finished execution
unless we explicitly `wait()` upon it.

```cpp
runtime.wait();

std::vector<uint32_t> arr_data(16);
arr.read(arr_data);
for (size_t h = 0; h < 4; ++h) {
  for (size_t w = 0; w < 4; ++w) {
    std::cout << arr_data.at(h * 4 + w) << " ";
  }
  std::cout << std::endl;
}
```

If you build a Taichi AOT module with the following Python script:

```python
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
```

The above C++ code may give the following output:

```plaintext
0 1 0 1
1 0 1 0
0 1 0 1
1 0 1 0
```

> Check out this example on Github: [https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/08-kernel](https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/08-kernel)

<sub>This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.</sub>