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
}
