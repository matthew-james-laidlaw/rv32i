#pragma once

#include <cstdint>
#include <vector>

class Memory
{
private:

    std::vector<uint8_t> m_memory;

public:

    Memory();

    auto ReadByte(uint32_t address) -> uint8_t;
    auto ReadHalfWord(uint32_t address) -> uint16_t;
    auto ReadWord(uint32_t address) -> uint32_t;

    auto WriteByte(uint32_t address, uint8_t value) -> void;
    auto WriteHalfWord(uint32_t address, uint16_t value) -> void;
    auto WriteWord(uint32_t address, uint32_t value) -> void;

};
