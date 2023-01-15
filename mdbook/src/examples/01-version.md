# Example 1: Versioning

Welcome to *Taichi AOT by Examples*. This is a step-by-step tutorial to
help you master everything about Taichi program deployment with
ahead-of-time (AOT) compilation and the Taichi Runtime C-API. Because
there are already lots of documentation about writing Taichi programs in
Python, we will focus on the integration of Taichi Runtime and
AOT-compiled kernels in your *native* applications.

To start with, let's make a simplest API call to ensure the Taichi Runtime
is in. We can check the currently install Taichi Runtime version with
`get_version`.

```cpp
ti::Version version = ti::get_version();
```

Taichi Runtime version is synchronized with the Python package, and it's
recommended to use AOT modules and the runtime library from the same
Taichi version.

```cpp
std::cout << "hello, this is taichi runtime " << version.major() << "."
          << version.minor() << "." << version.patch() << "!" << std::endl;
```

The above C++ code may give the following output:

```plaintext
hello, this is taichi runtime 1.5.0!
```

> Check out this example on Github: [https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/01-version](https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/01-version)