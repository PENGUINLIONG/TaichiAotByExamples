# Example 4: Memory Allocation

Allocate a piece of memory on device. Device memory is usually local to
the compute device and is not accessible from the CPU.

```cpp
ti::Memory device_memory = runtime.allocate_memory(4 * sizeof(uint32_t));
```

Host accessible memory can be accessed from the CPU but on-device memory
traffic during kernel launches could be much slower.

```cpp
ti::Memory host_accessible_memory =
    runtime.allocate_memory(4 * sizeof(uint32_t), /*host_access=*/true);
```

You can map the device memory to get a host visible pointer to the memory
content.

```cpp
void *mapped = host_accessible_memory.map();
for (uint32_t i = 0; i < 4; ++i) {
  ((uint32_t*)mapped)[i] = i;
}
```

After host memory access, don't forget to unmap the memory. Some platforms
don't allow the CPU and the GPU to access the same piece of memory at the
same time and it can lead to a crash.

```cpp
host_accessible_memory.unmap();
```

You can also use `read()` and `write()` for convenience.

```cpp
std::vector<uint32_t> readback_data(4);
host_accessible_memory.read(readback_data.data(),
                            readback_data.size() * sizeof(uint32_t));

std::cout << "readback data has the following values:";
for (uint32_t x : readback_data) {
  std::cout << " " << x;
}
std::cout << std::endl;
```

Please note that Taichi Runtime doesn't check on memory mapping. Attempts
to map non-host-accessible memory can lead to unrecoverable program
termination (usually a segfault). So please *do not* map any device only
memory. The same rule applies to `read()` and `write()` methods too.

```cpp
//void *a_null_ptr = device_memory.map();
```

The above C++ code may give the following output:

```plaintext
readback data has the following values: 0 1 2 3
```

> Check out this example on Github: [https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/04-memory](https://github.com/PENGUINLIONG/TaichiAotByExamples/tree/main/04-memory)

<sub>This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.</sub>