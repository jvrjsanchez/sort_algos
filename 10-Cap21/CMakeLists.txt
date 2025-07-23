cmake_minimum_required(VERSION 3.1)

project(
    Projeto8 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -g")

add_executable(dsatreino 
    src/dsatreino.cpp
    src/dsamodelo.hpp
    src/dsadataset.hpp
)
target_compile_definitions(dsatreino PUBLIC NDEBUG)

add_executable(dsatesteunitario 
    src/dsatesteunitario.cpp
    src/dsamodelo.hpp
)