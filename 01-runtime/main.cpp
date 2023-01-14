/// # Example 1: Get Taichi Runtime version
///
/// 
#include <cstdint>
#include <iostream>
#include <taichi/cpp/taichi.hpp>
#include <taichi/taichi_core.h>

int main(int argc, const char** argv) {
  uint32_t version = ti_get_version();
  uint32_t major = version / 1000000;
  uint32_t minor = (version / 1000) % 1000;
  uint32_t patch = version % 1000;

  std::cout << "hello, this is taichi runtime " << major << "." << minor << "."
            << patch << "!" << std::endl;
  std::cout << "the following archs are suppoted:" << std::endl;

  std::vector<TiArch> archs = ti::get_available_archs();
  for (TiArch arch : archs) {
    switch (arch) {
    case TI_ARCH_VULKAN:
      std::cout << "- vulkan" << std::endl;
      break;
    case TI_ARCH_METAL:
      std::cout << "- metal" << std::endl;
      break;
    case TI_ARCH_X64:
      std::cout << "- x64" << std::endl;
      break;
    case TI_ARCH_ARM64:
      std::cout << "- arm64" << std::endl;
      break;
    case TI_ARCH_CUDA:
      std::cout << "- cuda" << std::endl;
      break;
    default:
      break;
    }
  }
}
