//! # Example 8: Kernel and Positional Argument
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <taichi/cpp/taichi.hpp>

int main(int argc, const char **argv) {
  ti::Runtime runtime(ti::get_available_archs().front());
  ti::NdArray<uint32_t> arr = runtime.allocate_ndarray<uint32_t>({4, 4}, {}, true);

  /// Taichi AOT modules may contain precompiled Taichi kernels. You can extract
  /// the kernels by their names.
  ///
  /// For example, we have a kernel called `chessboard` that prints a chessboard
  /// pattern of interleaving zeros and ones to an ND-array.
  ti::AotModule aot_module =
      runtime.load_aot_module("08-kernel/assets/module.tcm");
  ti::Kernel k_chessboard = aot_module.get_kernel("chessboard");

  /// To launch the kernel, we first need to assign the positional arguments.
  /// There are two ways to setup kernel arguments.
  {
    /// First, you can assign arguments by their indices. This is the best if
    /// you have many arguments but only few of them are updated frequently.
    k_chessboard[0] = arr;
  }

  {
    /// If the argument list frequently changes, like when you are prototyping
    /// a new algorithm. You might want to clear and sequentially set the list
    /// of argument so you don't have to reorder the indices all the time.
    k_chessboard.clear_args();
    k_chessboard.push_arg(arr);
  }

  /// When all the arguments are ready, you can launch the kernel with
  /// `launch()`. Kernel launch is a device command, so it will be pushed to the
  /// default queue of `runtime`.
  k_chessboard.launch();

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
