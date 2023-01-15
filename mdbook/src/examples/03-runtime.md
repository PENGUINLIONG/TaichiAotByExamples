# Example 3: Runtime Instance

`ti::Runtime` is an instance context of the Taichi Runtime. It is
responsible of device memory allocation, memory transfer, device state
tracking and Taichi kernel launches.

You can create a runtime instance targeting a specific API backend like
this.

```cpp
#ifdef __APPLE__
ti::Runtime runtime(TI_ARCH_METAL);
#else
ti::Runtime runtime(TI_ARCH_VULKAN);
#endif
std::cout << "created runtime" << std::endl;
```

If your working environment has multiple GPUs installed, you can choose
which one to use with its device index. By default, Taichi selects the
most powerful compute device according to an internal algorithm.

```cpp
#ifdef __APPLE__
ti::Runtime runtime(TI_ARCH_METAL, 0);
#else
ti::Runtime runtime(TI_ARCH_VULKAN, 0);
#endif
std::cout << "created runtime with device #0" << std::endl;
```

The above C++ code may give the following output:

```plaintext
created runtime
created runtime with device #0
```

> Check out this example on Github: [https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/03-runtime](https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/03-runtime)

<sub>This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.</sub>