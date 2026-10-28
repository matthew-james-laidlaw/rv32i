#pragma once

#include <cstdint>
#include <vector>

class Memory
{
private:

    std::vector<uint8_t> m_memory;
    uint32_t m_base;  // guest address of the first byte

    auto Translate(uint32_t address, size_t length) const -> size_t;

public:

    Memory(size_t memory_size = 0x10000, uint32_t base = 0);

    auto Base() const -> uint32_t;

    auto ReadByte(uint32_t address) -> uint8_t;
    auto ReadHalfWord(uint32_t address) -> uint16_t;
    auto ReadWord(uint32_t address) -> uint32_t;

    auto WriteByte(uint32_t address, uint8_t value) -> void;
    auto WriteHalfWord(uint32_t address, uint16_t value) -> void;
    auto WriteWord(uint32_t address, uint32_t value) -> void;

};
