cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

file(GLOB sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

add_library(scanner ${sources})

