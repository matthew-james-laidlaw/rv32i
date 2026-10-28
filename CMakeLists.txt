cmake_minimum_required(VERSION 3.28.3)
project(RV32I LANGUAGES CXX)

include(cmake/cpm_fetch_dependencies.cmake)

add_library(emulator
    src/core.cpp
    src/instruction.cpp
    src/registers.cpp
)
target_include_directories(emulator PUBLIC src)
target_compile_features(emulator PUBLIC cxx_std_23)

add_executable(instruction_tests
    tests/core_tests.cpp
    tests/instructions/add_tests.cpp
    tests/instructions/and_tests.cpp
    tests/instructions/instruction_tests.cpp
    tests/instructions/or_tests.cpp
    tests/instructions/sll_tests.cpp
    tests/instructions/slt_tests.cpp
    tests/instructions/sltu_tests.cpp
    tests/instructions/sra_tests.cpp
    tests/instructions/srl_tests.cpp
    tests/instructions/sub_tests.cpp
    tests/instructions/xor_tests.cpp
    tests/memory_tests.cpp
)
target_include_directories(instruction_tests PRIVATE tests)
target_link_libraries(instruction_tests emulator GTest::gtest_main)

include(GoogleTest)
enable_testing()
gtest_discover_tests(instruction_tests)
