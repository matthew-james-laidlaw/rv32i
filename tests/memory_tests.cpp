#include <gtest/gtest.h>

#include <memory.h>

TEST(MemoryTest, ReadWrite)
{
    Memory memory;

    auto data_to_write = std::vector<uint8_t>{ 0x01, 0x02, 0x03, 0x04 };
    memory.Write(0x0000, data_to_write);

    auto data_read = memory.Read(0x0000, 4);
    EXPECT_EQ(data_read, data_to_write);
}
