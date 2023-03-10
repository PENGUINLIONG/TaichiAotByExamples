//! # Example 2: Taichi Arch
#include <cstdint>
#include <iostream>
#include <taichi/cpp/taichi.hpp>

int main(int argc, const char **argv) {
  /// An arch is an execution backend of Taichi Runtime. Depending on build-time
  /// flags and current platform installation, Taichi Runtime can support one or
  /// more archs. You can use `get_available_archs` to enumerate all the archs
  /// available in the current environment.
  std::vector<TiArch> archs = ti::get_available_archs();

  std::cout << "the following archs are supported:" << std::endl;
  for (TiArch arch : archs) {
    switch (arch) {
    case TI_ARCH_VULKAN:
      std::cout << "- vulkan" << std::endl;
      break;
    case TI_ARCH_METAL:
      std::cout << "- metal" << std::endl;
      break;
    case TI_ARCH_CUDA:
      std::cout << "- cuda" << std::endl;
      break;
    case TI_ARCH_X64:
      std::cout << "- x64" << std::endl;
      break;
    case TI_ARCH_ARM64:
      std::cout << "- arm64" << std::endl;
      break;
    case TI_ARCH_OPENGL:
      std::cout << "- opengl" << std::endl;
      break;
    case TI_ARCH_GLES:
      std::cout << "- gles" << std::endl;
      break;
    default:
      break;
    }
  }
}
