//! # Example 9: Error Handling
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <taichi/cpp/taichi.hpp>

int main(int argc, const char **argv) {
  /// When your project is complicated enough, or you are targeting multiple
  /// platforms that might not be your development environment, errors could
  /// occur, either by incorrect usage in your code or an implementation defact
  /// in Taichi Runtime.
  ///
  /// Taichi Runtime tries its best to ensure your incorrect usage doesn't
  /// propagate to crash your application. You might want to regularly check if
  /// any error occurred during your previous API calls.
  ti::Error error = ti::get_last_error();

  /// In most cases it reports `TI_ERROR_SUCCESS`, indicating everything is
  /// fine.
  assert(error.error == TI_ERROR_SUCCESS);

  /// But if you missed something, the error code will give you a semantical
  /// error code and a message telling you what exactly gone wrong.
  ti::Runtime runtime(TI_ARCH_MAX_ENUM);
  error = ti::get_last_error();
  std::cout << "error code: " << error.error << std::endl;
  std::cout << "error message: " << error.message << std::endl;

  /// For any APIs that constructs or returns a new object, the returned object
  /// won't be valid.
  std::cout << "runtime is valid? " << (runtime.is_valid() ? "true" : "false")
            << std::endl;

}
