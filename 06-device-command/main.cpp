/// # Example 6: Device command and synchronization
#include <cassert>
#include <cstdint>
#include <iostream>
#include <taichi/cpp/taichi.hpp>

int main(int argc, const char **argv) {
  /// Taichi Runtime C-API interface functions not only have host-side
  /// procedures like memory allocation and mapping, there are also device
  /// commands like kernel launches and memory copy. In this example we will
  /// demonstrate the concept of device commands and the correct usage of them,
  /// with an example of device-to-device memory copy.
  ti::Runtime runtime(TI_SOURCE_TYPE_SPIRV_BIT);
  ti::NdArray<float> src = runtime.allocate_ndarray<float>({4}, {}, true);
  ti::NdArray<float> dst = runtime.allocate_ndarray<float>({4}, {}, true);
  src.write({1.0f, 2.0f, 3.0f, 4.0f});

  /// Enqueue memory copy command to `runtime`'s default queue; copy the
  /// underlying data of ND-array `src` to `dst`.
  src.slice().copy_to(dst.slice());

  /// Without synchronization we have no idea what's in `dst` right now. In this
  /// case, `dst` is very likely to be filled with zero or random uninitialized
  /// data.
  {
    std::vector<float> data(4);
    dst.read(data);

    std::cout << "floats in `dst`:" << std::endl;
    for (float x : data) {
      std::cout << x << " ";
    }
    std::cout << std::endl;
  }

  /// Note that the compute device might not immediately receive your device
  /// commands so the computation could be deferred. It's recommended to call
  /// `flush()` first to send all enqueued device commands to the device and
  /// start execution. However, this is not necessary.
  runtime.flush();

  /// To guarantee all previously enqueued device commands have finished
  /// execution. We have to wait on the runtime's default queue until it's done.
  ///
  /// It might block your CPU thread for a significant length of time. Again,
  /// it's recommended to call `flush()` first to asynchronize GPU and CPU task.
  /// So that you can do something else on the CPU while the GPU is busy
  /// calculating.
  runtime.wait();

  /// After synchronization, we can be sure that the data in `src` has been
  /// copied to `dst`.
  {
    std::vector<float> data(4);
    dst.read(data);

    std::cout << "floats in `dst`:" << std::endl;
    for (float x : data) {
      std::cout << x << " ";
    }
    std::cout << std::endl;
  }
}
