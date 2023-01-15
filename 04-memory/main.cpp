//! # Example 4: Memory Allocation
#include <cassert>
#include <cstdint>
#include <iostream>
#include <taichi/cpp/taichi.hpp>

int main(int argc, const char **argv) {
  ti::Runtime runtime(ti::get_available_archs().front());

  /// Allocate a piece of memory on device. Device memory is usually local to
  /// the compute device and is not accessible from the CPU.
  ti::Memory device_memory = runtime.allocate_memory(4 * sizeof(uint32_t));

  /// Host accessible memory can be accessed from the CPU but on-device memory
  /// traffic during kernel launches could be much slower.
  ti::Memory host_accessible_memory =
      runtime.allocate_memory(4 * sizeof(uint32_t), /*host_access=*/true);

  /// You can map the device memory to get a host visible pointer to the memory
  /// content.
  void *mapped = host_accessible_memory.map();
  for (uint32_t i = 0; i < 4; ++i) {
    ((uint32_t*)mapped)[i] = i;
  }

  /// After host memory access, don't forget to unmap the memory. Some platforms
  /// don't allow the CPU and the GPU to access the same piece of memory at the
  /// same time and it can lead to a crash.
  host_accessible_memory.unmap();

  /// You can also use `read()` and `write()` for convenience.
  std::vector<uint32_t> readback_data(4);
  host_accessible_memory.read(readback_data.data(),
                              readback_data.size() * sizeof(uint32_t));

  std::cout << "readback data has the following values:";
  for (uint32_t x : readback_data) {
    std::cout << " " << x;
  }
  std::cout << std::endl;

  /// Please note that Taichi Runtime doesn't check on memory mapping. Attempts
  /// to map non-host-accessible memory can lead to unrecoverable program
  /// termination (usually a segfault). So please *do not* map any device only
  /// memory. The same rule applies to `read()` and `write()` methods too.
  //void *a_null_ptr = device_memory.map();
}
