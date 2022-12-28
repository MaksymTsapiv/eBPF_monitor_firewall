cmake_minimum_required(VERSION 3.1)
project(xdp_example)

set(CMAKE_CXX_STANDARD 17)

add_executable(xdp_example main.cpp)
target_include_directories(xdp_example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../libbpf/src)
target_link_libraries(xdp_example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../libbpf/src/libbpf.a)
