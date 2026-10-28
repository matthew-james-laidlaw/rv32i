#include <gtest/gtest.h>

#include <core.h>

#include <fstream>
#include <filesystem>

constexpr uint32_t RamBase = 0x80000000u;
constexpr size_t RamSize = 0x10000;

#ifndef TEST_DATA_DIR
#error "TEST_DATA_DIR is not defined"
#endif

TEST(AcceptanceTests, ADD)
{
    auto core = Core(RamSize, RamBase);
    
    auto infile = std::ifstream(std::filesystem::path(TEST_DATA_DIR) / "rv32ui-p-add.bin",
                                std::ios::binary);
    auto program = std::vector<uint8_t>((std::istreambuf_iterator<char>(infile)),
                                         std::istreambuf_iterator<char>());
    core.Load(program);

    EXPECT_EQ(core.registers.ReadPC(), RamBase);
    core.Step();
    EXPECT_NE(core.registers.ReadPC(), RamBase);
}
