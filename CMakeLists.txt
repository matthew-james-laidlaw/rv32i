cmake_minimum_required(VERSION 3.28.3)
project(RV32I LANGUAGES CXX)

include(cmake/cpm_fetch_dependencies.cmake)

add_library(emulator
    src/core.cpp
    src/instruction.cpp
    src/memory.cpp
    src/registers.cpp
)
target_include_directories(emulator PUBLIC src)
target_compile_features(emulator PUBLIC cxx_std_23)

add_executable(instruction_tests
    tests/core_tests.cpp
    tests/instructions/add_tests.cpp
    tests/instructions/addi_tests.cpp
    tests/instructions/auipc_tests.cpp
    tests/instructions/and_tests.cpp
    tests/instructions/andi_tests.cpp
    tests/instructions/beq_tests.cpp
    tests/instructions/bge_tests.cpp
    tests/instructions/bgeu_tests.cpp
    tests/instructions/blt_tests.cpp
    tests/instructions/bltu_tests.cpp
    tests/instructions/bne_tests.cpp
    tests/instructions/ebreak_tests.cpp
    tests/instructions/ecall_tests.cpp
    tests/instructions/fence_tests.cpp
    tests/instructions/jal_tests.cpp
    tests/instructions/jalr_tests.cpp
    tests/instructions/lb_tests.cpp
    tests/instructions/lbu_tests.cpp
    tests/instructions/lh_tests.cpp
    tests/instructions/lhu_tests.cpp
    tests/instructions/lui_tests.cpp
    tests/instructions/lw_tests.cpp
    tests/instructions/or_tests.cpp
    tests/instructions/ori_tests.cpp
    tests/instructions/sb_tests.cpp
    tests/instructions/sh_tests.cpp
    tests/instructions/sll_tests.cpp
    tests/instructions/slli_tests.cpp
    tests/instructions/slt_tests.cpp
    tests/instructions/sltu_tests.cpp
    tests/instructions/slti_tests.cpp
    tests/instructions/sltiu_tests.cpp
    tests/instructions/sra_tests.cpp
    tests/instructions/srai_tests.cpp
    tests/instructions/srl_tests.cpp
    tests/instructions/srli_tests.cpp
    tests/instructions/sub_tests.cpp
    tests/instructions/sw_tests.cpp
    tests/instructions/xori_tests.cpp
    tests/instructions/xor_tests.cpp
    tests/memory_tests.cpp
    tests/registers_tests.cpp
)
target_include_directories(instruction_tests PRIVATE tests)
target_link_libraries(instruction_tests emulator GTest::gtest_main)

include(GoogleTest)
enable_testing()
gtest_discover_tests(instruction_tests)
