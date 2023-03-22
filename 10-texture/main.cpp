//! # Example 10: Texture
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <taichi/cpp/taichi.hpp>

int main(int argc, const char **argv) {
  ti::Runtime runtime(ti::get_available_archs().front());
  ti::AotModule aot_module =
      runtime.load_aot_module("10-texture/assets/module.tcm");

  /// Textures are a special kind of memory objects broadly available on GPUs.
  /// Each texture has a format, which determines how many channels it has,
  /// how many bits each channel has, and a dimensionality, which determines
  /// whether it is a 1D, 2D, or 3D texture.
  ti::Texture tex =
      runtime.allocate_texture2d(8, 8, TI_FORMAT_R32F, TI_NULL_HANDLE);

  /// Unlike ND-arrays, texture memory are not linearly laid out and must be
  /// allocated in device memory. So you cannot directly access its data by
  /// memory mapping. You can only write to the texture by kernel launches.
  ti::Kernel k_write_tex = aot_module.get_kernel("write_tex");
  k_write_tex[0] = tex;
  k_write_tex.launch();

  runtime.wait();

  /// In graphics, textures are usually accessed by sampling. Sampling is a
  /// controlled by samplers. Taichi by default uses a linear sampler, which
  /// performs bilinear interpolation on the texture, taking the average of
  /// the four nearest texels to the sample point.
  ti::Kernel k_sample_tex = aot_module.get_kernel("sample_tex");
  ti::NdArray<uint32_t> arr = runtime.allocate_ndarray<uint32_t>({4, 4}, {}, true);
  k_sample_tex[0] = arr;
  k_sample_tex[1] = tex;
  k_sample_tex.launch();

  /// Remind that, we don't know if a device command has finished execution
  /// unless we explicitly `wait()` upon it.
  runtime.wait();

  std::vector<uint32_t> arr_data(16);
  arr.read(arr_data);
  for (size_t h = 0; h < 4; ++h) {
    for (size_t w = 0; w < 4; ++w) {
      std::cout << arr_data.at(h * 4 + w) << " ";
    }
    std::cout << std::endl;
  }

}
