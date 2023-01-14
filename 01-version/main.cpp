/// # Example 1: Double check Taichi Runtime version
#include <cstdint>
#include <iostream>
#include <taichi/cpp/taichi.hpp>

int main(int argc, const char **argv) {
  ti::Version version = ti::get_version();
  uint32_t major = version.major();
  uint32_t minor = version.minor();
  uint32_t patch = version.patch();

  std::cout << "hello, this is taichi runtime " << major << "." << minor << "."
            << patch << "!" << std::endl;
}
