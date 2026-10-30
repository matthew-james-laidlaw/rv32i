#include <gtest/gtest.h>

#include <registers.h>

TEST(RegistersTest, GeneralPurposeRegistersStartAtZero)
{
    auto registers = Registers{};

    for (uint8_t index = 0; index < 32; ++index)
    {
        EXPECT_EQ(registers.ReadGP(index), 0u) << "register x" << static_cast<unsigned>(index);
    }
}

TEST(RegistersTest, WritesAndReadsEveryWritableGeneralPurposeRegister)
{
    auto registers = Registers{};

    for (uint8_t index = 1; index < 32; ++index)
    {
        registers.WriteGP(index, 0xA5000000u | index);
    }

    EXPECT_EQ(registers.ReadGP(0), 0u);
    for (uint8_t index = 1; index < 32; ++index)
    {
        EXPECT_EQ(registers.ReadGP(index), 0xA5000000u | index)
            << "register x" << static_cast<unsigned>(index);
    }
}

TEST(RegistersTest, WritesToX0AreIgnored)
{
    auto registers = Registers{};
    registers.WriteGP(0, 0xFFFFFFFFu);

    EXPECT_EQ(registers.ReadGP(0), 0u);
}

TEST(RegistersTest, WritingOneRegisterDoesNotChangeOtherRegisters)
{
    auto registers = Registers{};
    registers.WriteGP(1, 0x12345678u);
    registers.WriteGP(2, 0x87654321u);

    registers.WriteGP(1, 0xABCDEF01u);

    EXPECT_EQ(registers.ReadGP(1), 0xABCDEF01u);
    EXPECT_EQ(registers.ReadGP(2), 0x87654321u);
    EXPECT_EQ(registers.ReadGP(3), 0u);
}

TEST(RegistersTest, ProgramCounterStartsAtZeroAndCanBeReadAndWritten)
{
    auto registers = Registers{};

    EXPECT_EQ(registers.ReadPC(), 0u);
    registers.WritePC(0x12345678u);
    EXPECT_EQ(registers.ReadPC(), 0x12345678u);
    registers.WritePC(0xFFFFFFFFu);
    EXPECT_EQ(registers.ReadPC(), 0xFFFFFFFFu);
}

TEST(RegistersTest, ProgramCounterAndGeneralPurposeRegistersAreIndependent)
{
    auto registers = Registers{};
    registers.WriteGP(5, 0x11223344u);
    registers.WritePC(0x55667788u);

    registers.WriteGP(5, 0xAABBCCDDu);

    EXPECT_EQ(registers.ReadGP(5), 0xAABBCCDDu);
    EXPECT_EQ(registers.ReadPC(), 0x55667788u);
}
