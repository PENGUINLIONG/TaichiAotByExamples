project(TaichiAotByExamples)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(01-version)
add_subdirectory(02-arch)
add_subdirectory(03-runtime)
add_subdirectory(04-memory)
add_subdirectory(05-ndarray)
add_subdirectory(06-device-command)
add_subdirectory(07-aot-module)
add_subdirectory(08-kernel)
add_subdirectory(09-error)
add_subdirectory(10-texture)
