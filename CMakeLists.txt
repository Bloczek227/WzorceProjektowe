cmake_minimum_required(VERSION 3.24)
project(wp_proj)

set(CMAKE_CXX_STANDARD 20)

add_executable(AhriExample Examples/AhriExample.cpp)
add_executable(VelKozExample Examples/VelKozExample.cpp)
add_executable(wp_proj main.cpp)
