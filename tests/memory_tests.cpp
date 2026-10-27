#include <gtest/gtest.h>

#include <memory.h>

TEST(MemoryTest, ReadWriteByte)
{
    Memory memory;
    memory.WriteByte(0x0000, 0x12);
    EXPECT_EQ(memory.ReadByte(0x0000), 0x12);
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
