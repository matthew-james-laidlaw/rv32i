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

    auto Read(uint32_t address, size_t size_in_bytes) -> std::vector<uint8_t>
    {
        if (address + size_in_bytes > m_memory.size())
        {
            throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X} for size {} bytes", address, size_in_bytes));
        }
        return std::vector<uint8_t>(m_memory.begin() + address, m_memory.begin() + address + size_in_bytes);
    }

    auto Write(uint32_t address, const std::vector<uint8_t>& data) -> void
    {
        if (address + data.size() > m_memory.size())
        {
            throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X} for size {} bytes", address, data.size()));
        }
        std::copy(data.begin(), data.end(), m_memory.begin() + address);
    }

};
