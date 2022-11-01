cmake_minimum_required(VERSION 3.19)
project(frame_counter)

#set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME frame_counter)

add_executable("${PROJECT_NAME}" main.c)

#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/")
#find_package(LibBpf)
#target_include_directories("${PROJECT_NAME}" PRIVATE ${LIBBPF_INCLUDE_DIR})
#target_link_directories("${PROJECT_NAME}" PRIVATE ${LIBBPF_STATIC_LIBRARIES})

target_include_directories("${PROJECT_NAME}" PRIVATE libbpf/src)
target_link_directories("${PROJECT_NAME}" PRIVATE libbpf/src)
target_link_libraries("${PROJECT_NAME}" PRIVATE bpf)
