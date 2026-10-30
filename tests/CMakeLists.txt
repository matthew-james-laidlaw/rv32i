set(EMU_TESTS_TARGET unit_tests)

add_executable(${EMU_TESTS_TARGET}
    core_tests.cpp
    instructions/add_tests.cpp
    instructions/addi_tests.cpp
    instructions/auipc_tests.cpp
    instructions/and_tests.cpp
    instructions/andi_tests.cpp
    instructions/beq_tests.cpp
    instructions/bge_tests.cpp
    instructions/bgeu_tests.cpp
    instructions/blt_tests.cpp
    instructions/bltu_tests.cpp
    instructions/bne_tests.cpp
    instructions/ebreak_tests.cpp
    instructions/ecall_tests.cpp
    instructions/fence_tests.cpp
    instructions/jal_tests.cpp
    instructions/jalr_tests.cpp
    instructions/lb_tests.cpp
    instructions/lbu_tests.cpp
    instructions/lh_tests.cpp
    instructions/lhu_tests.cpp
    instructions/lui_tests.cpp
    instructions/lw_tests.cpp
    instructions/mret_tests.cpp
    instructions/or_tests.cpp
    instructions/ori_tests.cpp
    instructions/sb_tests.cpp
    instructions/sh_tests.cpp
    instructions/sll_tests.cpp
    instructions/slli_tests.cpp
    instructions/slt_tests.cpp
    instructions/sltu_tests.cpp
    instructions/slti_tests.cpp
    instructions/sltiu_tests.cpp
    instructions/sra_tests.cpp
    instructions/srai_tests.cpp
    instructions/srl_tests.cpp
    instructions/srli_tests.cpp
    instructions/sub_tests.cpp
    instructions/sw_tests.cpp
    instructions/xori_tests.cpp
    instructions/xor_tests.cpp
    memory_tests.cpp
    registers_tests.cpp
)

target_include_directories(${EMU_TESTS_TARGET}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${EMU_TESTS_TARGET}
    emucore
    GTest::gtest_main
)

if(BUILD_ACCEPTANCE_TESTS)
    target_sources(${EMU_TESTS_TARGET} PRIVATE acceptance_tests.cpp)
    target_compile_definitions(${EMU_TESTS_TARGET} PRIVATE TEST_DATA_DIR="${RISCV_TESTS_BIN_DIR}")
    add_dependencies(${EMU_TESTS_TARGET} riscv_test_bins)
endif()

# There are many instruction test source files, and compiling them individually
# is slow. Enabling Unity build merges them all into a single compilation unit,
# eliminating per-file compilation overhead.
set_target_properties(${EMU_TESTS_TARGET}
    PROPERTIES
        UNITY_BUILD ON
        UNITY_BUILD_BATCH_SIZE 0
)

include(GoogleTest)
gtest_discover_tests(${EMU_TESTS_TARGET})
