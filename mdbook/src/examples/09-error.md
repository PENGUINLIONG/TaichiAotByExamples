# Example 9: Error Handling

When your project is complicated enough, or you are targeting multiple
platforms that might not be your development environment, errors could
occur, either by incorrect usage in your code or an implementation defact
in Taichi Runtime.

Taichi Runtime tries its best to ensure your incorrect usage doesn't
propagate to crash your application. You might want to regularly check if
any error occurred during your previous API calls.

```cpp
ti::Error error = ti::get_last_error();
```

In most cases it reports `TI_ERROR_SUCCESS`, indicating everything is
fine.

```cpp
assert(error.error == TI_ERROR_SUCCESS);
```

But if you missed something, the error code will give you a semantical
error code and a message telling you what exactly gone wrong.

```cpp
ti::Runtime runtime(TI_ARCH_MAX_ENUM);
error = ti::get_last_error();
std::cout << "error code: " << error.error << std::endl;
std::cout << "error message: " << error.message << std::endl;
```

For any APIs that constructs or returns a new object, the returned object
won't be valid.

```cpp
std::cout << "runtime is valid? " << (runtime.is_valid() ? "true" : "false")
          << std::endl;
```

The above C++ code may give the following output:

```plaintext
error code: -1
error message: arch
runtime is valid? false
```

> Check out this example on Github: [https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/09-error](https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/09-error)

<sub>This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.</sub>