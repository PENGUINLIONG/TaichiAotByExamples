# Example 10: Texture

Textures are a special kind of memory objects broadly available on GPUs.
Each texture has a format, which determines how many channels it has,
how many bits each channel has, and a dimensionality, which determines
whether it is a 1D, 2D, or 3D texture.

```cpp
ti::Texture tex =
    runtime.allocate_texture2d(8, 8, TI_FORMAT_R32F, TI_NULL_HANDLE);
```

Unlike ND-arrays, texture memory are not linearly laid out and must be
allocated in device memory. So you cannot directly access its data by
memory mapping. You can only write to the texture by kernel launches.

```cpp
ti::Kernel k_write_tex = aot_module.get_kernel("write_tex");
k_write_tex[0] = tex;
k_write_tex.launch();

runtime.wait();
```

In graphics, textures are usually accessed by sampling. Sampling is a
controlled by samplers. Taichi by default uses a linear sampler, which
performs bilinear interpolation on the texture, taking the average of
the four nearest texels to the sample point.

```cpp
ti::Kernel k_sample_tex = aot_module.get_kernel("sample_tex");
ti::NdArray<uint32_t> arr = runtime.allocate_ndarray<uint32_t>({4, 4}, {}, true);
k_sample_tex[0] = arr;
k_sample_tex[1] = tex;
k_sample_tex.launch();
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
```

The above C++ code may give the following output:

```plaintext
5 5 5 5
5 5 5 5
5 5 5 5
5 5 5 5
```

> Check out this example on Github: [https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/10-texture](https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/10-texture)

<sub>This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.</sub>