# Example 6: Device Command

Taichi Runtime C-API interface functions not only have host-side
procedures like memory allocation and mapping, there are also device
commands like kernel launches and memory copy. In this example we will
demonstrate the concept of device commands and the correct usage of them,
with an example of device-to-device memory copy.

```cpp
ti::NdArray<float> src = runtime.allocate_ndarray<float>({4}, {}, true);
ti::NdArray<float> dst = runtime.allocate_ndarray<float>({4}, {}, true);
src.write({1.0f, 2.0f, 3.0f, 4.0f});
```

Enqueue memory copy command to `runtime`'s default queue; copy the
underlying data of ND-array `src` to `dst`.

```cpp
src.slice().copy_to(dst.slice());
```

Without synchronization we have no idea what's in `dst` right now. In this
case, `dst` is very likely to be filled with zero or random uninitialized
data.

```cpp
std::vector<float> data(4);
dst.read(data);

std::cout << "floats in `dst`:" << std::endl;
for (float x : data) {
  std::cout << x << " ";
}
std::cout << std::endl;
```

Note that the compute device might not immediately receive your device
commands so the computation could be deferred. It's recommended to call
`flush()` first to send all enqueued device commands to the device and
start execution. However, this is not necessary.

```cpp
runtime.flush();
```

To guarantee all previously enqueued device commands have finished
execution. We have to wait on the runtime's default queue until it's done.

It might block your CPU thread for a significant length of time. Again,
it's recommended to call `flush()` first to asynchronize GPU and CPU task.
So that you can do something else on the CPU while the GPU is busy
calculating.

```cpp
runtime.wait();
```

After synchronization, we can be sure that the data in `src` has been
copied to `dst`.

```cpp
std::vector<float> data(4);
dst.read(data);

std::cout << "floats in `dst`:" << std::endl;
for (float x : data) {
  std::cout << x << " ";
}
std::cout << std::endl;
```

The above C++ code may give the following output:

```plaintext
floats in `dst`:
0 0 0 0
floats in `dst`:
1 2 3 4
```

> Check out this example on Github: [https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/06-device-command](https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/06-device-command)

<sub>This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.</sub>