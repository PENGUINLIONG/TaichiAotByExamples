/// # Example 7: Load and create AOT modules
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <taichi/cpp/taichi.hpp>

int main(int argc, const char **argv) {
  ti::Runtime runtime(ti::get_available_archs().front());

  /// AOT modules are containers of ahead-of-time compiled Taichi kernels. You
  /// can compile AOT modules with `ti.aot.Module` APIs in Python.
  ///
  /// After compilation, you can load AOT modules from the filesystem directly
  /// like this:
  {
    ti::AotModule aot_module =
        runtime.load_aot_module("07-aot-module/assets/module.tcm");
    std::cout << "loaded aot module from filesystem" << std::endl;
  }

  /// But if you want more control over how the module is loaded, you can
  /// implement the loading logic yourself, and create the AOT module from data
  /// buffer. You can also use tools like
  /// [`bin2c`](https://manpages.ubuntu.com/manpages/bionic/man1/bin2c.1.html)
  /// to embed module data in your source code.
  {
    std::ifstream f("07-aot-module/assets/module.tcm",
                    std::ios::binary | std::ios::in | std::ios::ate);
    std::vector<uint8_t> tcm_data(f.tellg());
    f.seekg(std::ios::beg);
    f.read((char*)tcm_data.data(), tcm_data.size());

    ti::AotModule aot_module = runtime.create_aot_module(tcm_data);
    std::cout << "created aot module from buffer data" << std::endl;
  }
}
