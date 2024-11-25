
cmake_minimum_required(VERSION 3.20.0)

# 输出编译详细过程
set(CMAKE_VERBOSE_MAKEFILE on)

# C编译器与编译选项
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-g -O0")

# 项目名称
project(cfs)

# 添加子项目
add_subdirectory(./source/)
add_subdirectory(./test)
