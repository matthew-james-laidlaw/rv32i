include(FetchContent)

find_program(RISCV_GCC NAMES riscv64-unknown-elf-gcc riscv32-unknown-elf-gcc riscv64-elf-gcc)
find_program(RISCV_OBJCOPY NAMES riscv64-unknown-elf-objcopy riscv32-unknown-elf-objcopy riscv64-elf-objcopy)

set(RISCV_TESTS_BIN_DIR "${CMAKE_BINARY_DIR}/riscv_tests")

if(NOT RISCV_GCC OR NOT RISCV_OBJCOPY)
    message(FATAL_ERROR "RV32I_BUILD_ACCEPTANCE_TESTS is ON but no RISC-V GCC/objcopy toolchain was found")
endif()

FetchContent_Declare(
    riscv_tests
    GIT_REPOSITORY https://github.com/riscv-software-src/riscv-tests.git
    GIT_TAG master
    GIT_SHALLOW TRUE
    GIT_SUBMODULES_RECURSE TRUE
)
FetchContent_GetProperties(riscv_tests)
if(NOT riscv_tests_POPULATED)
    FetchContent_Populate(riscv_tests)
endif()

file(MAKE_DIRECTORY "${RISCV_TESTS_BIN_DIR}")
file(GLOB RISCV_ISA_SOURCES CONFIGURE_DEPENDS "${riscv_tests_SOURCE_DIR}/isa/rv32ui/*.S")

set(RISCV_TEST_BINS)
foreach(src IN LISTS RISCV_ISA_SOURCES)
    get_filename_component(name "${src}" NAME_WE)
    set(base "${RISCV_TESTS_BIN_DIR}/rv32ui-p-${name}")
    add_custom_command(
        OUTPUT "${base}.bin"
        COMMAND ${RISCV_GCC} -march=rv32i_zicsr_zifencei -mabi=ilp32 -static -mcmodel=medany
                -fvisibility=hidden -nostdlib -nostartfiles
                -I${riscv_tests_SOURCE_DIR}/env/p
                -I${riscv_tests_SOURCE_DIR}/isa/macros/scalar
                -T${riscv_tests_SOURCE_DIR}/env/p/link.ld
                "${src}" -o "${base}"
        COMMAND ${RISCV_OBJCOPY} -O binary "${base}" "${base}.bin"
        DEPENDS "${src}"
        VERBATIM
    )
    list(APPEND RISCV_TEST_BINS "${base}.bin")
endforeach()

add_custom_target(riscv_test_bins ALL DEPENDS ${RISCV_TEST_BINS})
