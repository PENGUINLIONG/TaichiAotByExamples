/// # Example 2: Enumerate available runtime archs
#include <cstdint>
#include <iostream>
#include <taichi/cpp/taichi.hpp>

int main(int argc, const char **argv) {
  std::vector<TiArch> archs = ti::get_available_archs();

  std::cout << "the following archs are suppoted:" << std::endl;
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
