cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(Lab2)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(Lab2 Lab2.cpp)
target_link_libraries(Lab2 "${TORCH_LIBRARIES}")
set_property(TARGET Lab2 PROPERTY CXX_STANDARD 14)
