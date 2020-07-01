cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)

project (peylang)

add_subdirectory(${CMAKE_SOURCE_DIR}/parser)

enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/test)

