cmake_minimum_required(VERSION 3.28.3)
project(RV32I LANGUAGES CXX)

include(cmake/cpm_fetch_dependencies.cmake)

add_library(emulator
    src/core.cpp
    src/instruction.cpp
)
target_include_directories(emulator PUBLIC src)
target_compile_features(emulator PUBLIC cxx_std_23)

add_executable(instruction_tests
    tests/core_tests.cpp
    tests/instruction_tests.cpp
    tests/memory_tests.cpp
)
target_link_libraries(instruction_tests emulator GTest::gtest_main)

include(GoogleTest)
enable_testing()
gtest_discover_tests(instruction_tests)
