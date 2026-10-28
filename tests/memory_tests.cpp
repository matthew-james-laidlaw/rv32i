#include <gtest/gtest.h>

#include <memory.h>

#include <limits>
#include <stdexcept>

TEST(MemoryTest, ReadWriteByte)
{
    Memory memory;
    memory.WriteByte(0x0000, 0x12);
    EXPECT_EQ(memory.ReadByte(0x0000), 0x12);
}

TEST(MemoryTest, MemoryStartsZeroedOut)
{
    Memory memory;

    for (uint32_t address = 0; address < 0x10000; ++address)
    {
        EXPECT_EQ(memory.ReadByte(address), 0u);
    }

    for (uint32_t address = 0; address < 0x10000 - 1; ++address)
    {
        EXPECT_EQ(memory.ReadHalfWord(address), 0u);
    }

    for (uint32_t address = 0; address < 0x10000 - 3; ++address)
    {
        EXPECT_EQ(memory.ReadWord(address), 0u);
    }
}

TEST(MemoryTest, ReadWriteHalfWord)
{
    Memory memory;
    memory.WriteHalfWord(0x0000, 0x1234);
    EXPECT_EQ(memory.ReadHalfWord(0x0000), 0x1234);
}

TEST(MemoryTest, ReadWriteWord)
{
    Memory memory;
    memory.WriteWord(0x0000, 0x12345678);
    EXPECT_EQ(memory.ReadWord(0x0000), 0x12345678);
}

TEST(MemoryTest, MultiByteValuesUseLittleEndianByteOrder)
{
    Memory memory;
    memory.WriteWord(0x0000, 0x12345678u);

    EXPECT_EQ(memory.ReadByte(0x0000), 0x78u);
    EXPECT_EQ(memory.ReadByte(0x0001), 0x56u);
    EXPECT_EQ(memory.ReadByte(0x0002), 0x34u);
    EXPECT_EQ(memory.ReadByte(0x0003), 0x12u);
    EXPECT_EQ(memory.ReadHalfWord(0x0000), 0x5678u);
    EXPECT_EQ(memory.ReadHalfWord(0x0002), 0x1234u);
}

TEST(MemoryTest, WritesAtDifferentAddressesDoNotOverlap)
{
    Memory memory;
    memory.WriteByte(0x0000, 0x11u);
    memory.WriteHalfWord(0x0002, 0x3322u);
    memory.WriteWord(0x0004, 0x77665544u);

    EXPECT_EQ(memory.ReadByte(0x0000), 0x11u);
    EXPECT_EQ(memory.ReadByte(0x0001), 0u);
    EXPECT_EQ(memory.ReadHalfWord(0x0002), 0x3322u);
    EXPECT_EQ(memory.ReadWord(0x0004), 0x77665544u);
}

TEST(MemoryTest, ReadsAndWritesAtLastValidAddresses)
{
    Memory byte_memory;
    Memory halfword_memory;
    Memory word_memory;

    byte_memory.WriteByte(0xFFFFu, 0xABu);
    halfword_memory.WriteHalfWord(0xFFFEu, 0xCDEFu);
    word_memory.WriteWord(0xFFFCu, 0x12345678u);

    EXPECT_EQ(byte_memory.ReadByte(0xFFFFu), 0xABu);
    EXPECT_EQ(halfword_memory.ReadHalfWord(0xFFFEu), 0xCDEFu);
    EXPECT_EQ(word_memory.ReadWord(0xFFFCu), 0x12345678u);
}

TEST(MemoryTest, ReadsAndWritesPastEndThrow)
{
    Memory memory;

    EXPECT_THROW(memory.ReadByte(0x10000u), std::runtime_error);
    EXPECT_THROW(memory.ReadHalfWord(0xFFFFu), std::runtime_error);
    EXPECT_THROW(memory.ReadWord(0xFFFDu), std::runtime_error);
    EXPECT_THROW(memory.WriteByte(0x10000u, 0u), std::runtime_error);
    EXPECT_THROW(memory.WriteHalfWord(0xFFFFu, 0u), std::runtime_error);
    EXPECT_THROW(memory.WriteWord(0xFFFDu, 0u), std::runtime_error);
}

TEST(MemoryTest, AddressOverflowDoesNotWrapIntoValidMemory)
{
    Memory memory;
    constexpr auto max_address = std::numeric_limits<uint32_t>::max();

    EXPECT_THROW(memory.ReadHalfWord(max_address), std::runtime_error);
    EXPECT_THROW(memory.ReadWord(max_address - 1), std::runtime_error);
    EXPECT_THROW(memory.ReadWord(max_address - 2), std::runtime_error);
    EXPECT_THROW(memory.WriteHalfWord(max_address, 0u), std::runtime_error);
    EXPECT_THROW(memory.WriteWord(max_address - 1, 0u), std::runtime_error);
    EXPECT_THROW(memory.WriteWord(max_address - 2, 0u), std::runtime_error);
}
