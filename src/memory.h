#pragma once

#include <cstdint>
#include <format>
#include <stdexcept>
#include <vector>

class Memory
{
private:

    std::vector<uint8_t> m_memory;

public:

    Memory()
        : m_memory(0x10000, 0) // default to 64KB of memory
    {}

    auto ReadByte(uint32_t address) -> uint8_t
    {
        if (address >= m_memory.size())
        {
            throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
        }
        return m_memory[address];
    }

    auto ReadHalfWord(uint32_t address) -> uint16_t
    {
        if (address + 1 >= m_memory.size())
        {
            throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
        }
        return static_cast<uint16_t>(m_memory[address]) | (static_cast<uint16_t>(m_memory[address + 1]) << 8);
    }

    auto ReadWord(uint32_t address) -> uint32_t
    {
        if (address + 3 >= m_memory.size())
        {
            throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
        }
        return static_cast<uint32_t>(m_memory[address]) |
               (static_cast<uint32_t>(m_memory[address + 1]) << 8) |
               (static_cast<uint32_t>(m_memory[address + 2]) << 16) |
               (static_cast<uint32_t>(m_memory[address + 3]) << 24);
    }

    auto WriteByte(uint32_t address, uint8_t value) -> void
    {
        if (address >= m_memory.size())
        {
            throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
        }
        m_memory[address] = value;
    }

    auto WriteHalfWord(uint32_t address, uint16_t value) -> void
    {
        if (address + 1 >= m_memory.size())
        {
            throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
        }
        m_memory[address] = static_cast<uint8_t>(value & 0xFF);
        m_memory[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    }

    auto WriteWord(uint32_t address, uint32_t value) -> void
    {
        if (address + 3 >= m_memory.size())
        {
            throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
        }
        m_memory[address] = static_cast<uint8_t>(value & 0xFF);
        m_memory[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
        m_memory[address + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
        m_memory[address + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);
    }

};
