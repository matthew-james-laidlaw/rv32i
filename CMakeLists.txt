cmake_minimum_required(VERSION 3.28.3)
project(RV32I LANGUAGES CXX)

include(cmake/cpm_fetch_dependencies.cmake)

add_library(emulator INTERFACE)
target_include_directories(emulator INTERFACE src)
target_compile_features(emulator INTERFACE cxx_std_23)

add_executable(instruction_tests
    tests/instruction_tests.cpp
    tests/memory_tests.cpp
)
target_link_libraries(instruction_tests emulator GTest::gtest_main)

include(GoogleTest)
enable_testing()
gtest_discover_tests(instruction_tests)
