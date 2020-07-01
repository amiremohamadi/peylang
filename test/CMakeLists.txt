cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)

set(test_sources ${CMAKE_CURRENT_SOURCE_DIR}/tests_run.cc)
add_executable(tests ${test_sources})

target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR})
target_link_libraries(tests scanner)

add_test(NAME tests COMMAND tests)
configure_file(sample_file.tu ${CMAKE_CURRENT_BINARY_DIR}/sample_file.tu COPYONLY)

