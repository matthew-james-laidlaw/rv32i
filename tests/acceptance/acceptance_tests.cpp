#include <gtest/gtest.h>

#include <core.h>

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

constexpr uint32_t RamBase = 0x80000000u;
constexpr size_t RamSize = 0x10000;

#ifndef TEST_DATA_DIR
#error "TEST_DATA_DIR is not defined"
#endif

// Address of the `tohost` mailbox, from `nm` on the ELF. A test reports its result by writing here.
constexpr uint32_t ToHost = 0x80001000u;
constexpr uint32_t MaxSteps = 100000;

class AcceptanceTests : public testing::TestWithParam<std::string> {};

TEST_P(AcceptanceTests, Rv32ui)
{
    auto core = Core(RamSize, RamBase);

    auto infile = std::ifstream(std::filesystem::path(TEST_DATA_DIR) / ("rv32ui-p-" + GetParam() + ".bin"),
                                std::ios::binary);
    ASSERT_TRUE(infile.is_open());
    auto program = std::vector<uint8_t>((std::istreambuf_iterator<char>(infile)),
                                         std::istreambuf_iterator<char>());
    core.Load(program);

    EXPECT_EQ(core.registers.ReadPC(), RamBase);

    uint32_t steps = 0;
    while (core.memory.ReadWord(ToHost) == 0 && steps < MaxSteps)
    {
        core.Step();
        ++steps;
    }

    auto result = core.memory.ReadWord(ToHost);
    ASSERT_NE(result, 0u) << "timed out after " << steps << " steps, pc=0x" << std::hex << core.registers.ReadPC();
    EXPECT_EQ(result, 1u) << "failed test case " << (result >> 1);
}

INSTANTIATE_TEST_SUITE_P(Rv32ui, AcceptanceTests,
    testing::Values(
        "add",
        "addi",
        "and",
        "andi",
        "auipc",
        "beq",
        "bge",
        "bgeu",
        "blt",
        "bltu",
        "bne",
        "jal",
        "jalr",
        "lb",
        "lbu",
        "lh",
        "lhu",
        "lui",
        "lw",
        "or",
        "ori",
        "sb",
        "sh",
        "simple",
        "sll",
        "slli",
        "slt",
        "slti",
        "sltiu",
        "sltu",
        "sra",
        "srai",
        "srl",
        "srli",
        "sub",
        "sw",
        "xor",
        "xori"),
    [](const testing::TestParamInfo<std::string>& info) { return info.param; });
