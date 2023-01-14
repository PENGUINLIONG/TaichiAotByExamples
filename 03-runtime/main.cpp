/// # Example 3: Create the right runtime for your workload
#include <cstdint>
#include <iostream>
#include <taichi/cpp/taichi.hpp>
#include <taichi/taichi_core.h>

int main(int argc, const char **argv) {
  /// `ti::Runtime` is an instance context of the Taichi Runtime. It is
  /// responsible of device memory allocation, memory transfer, device state
  /// tracking and Taichi kernel launches.

  {
    /// You can create a runtime instance targeting a specific API backend like
    /// this.
#if __APPLE__
    ti::Runtime runtime(TI_ARCH_METAL);
#else
    ti::Runtime runtime(TI_ARCH_VULKAN);
#endif
    std::cout << "created runtime" << std::endl;
  }

  {
    /// If your working environment has multiple GPUs installed, you can choose
    /// which one to use with its device index. By default, Taichi selects the
    /// most powerful compute device according to an internal algorithm.
#if __APPLE__
    ti::Runtime runtime(TI_ARCH_METAL, 0);
#else
    ti::Runtime runtime(TI_ARCH_VULKAN, 0);
#endif
    std::cout << "created runtime with device #0" << std::endl;
  }

  {
    // Because many Taichi backends share a same AOT program source types. For
    // example, Vulkan and Metal can both consume modules of SPIR-V sources. By
    // creating a runtime with the desired source type, you can ship a same
    // piece of code to a number of platforms.
    ti::Runtime runtime(TI_SOURCE_TYPE_SPIRV_BIT);

    // You can check the created runtime arch via `arch()`.
    std::cout << "requested any runtime compatible with spirv sources, got ";
    switch (runtime.arch()) {
    case TI_ARCH_VULKAN:
      std::cout << "vulkan" << std::endl;
      break;
    case TI_ARCH_METAL:
      std::cout << "metal" << std::endl;
      break;
    case TI_ARCH_OPENGL:
      std::cout << "opengl" << std::endl;
      break;
    case TI_ARCH_GLES:
      std::cout << "gles" << std::endl;
      break;
    default:
      std::cout << "... i don't know what's this" << std::endl;
    }
  }

  {
    // Also, if you have prepared a fallback chain of modules in case some archs
    // are not available, you can combine the source type bits to find an arch
    // that supports at least one of the source types.
    ti::Runtime runtime(TI_SOURCE_TYPE_SPIRV_BIT |
                        TI_SOURCE_TYPE_LLVM_BITCODE_CPU_BIT);
    std::cout << "created runtime with device that supports either spirv or "
                 "cpu llvm bitcode"
              << std::endl;
  }
}
