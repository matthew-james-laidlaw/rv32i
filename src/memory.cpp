#include <memory.h>

#include <format>
#include <stdexcept>

Memory::Memory()
    : m_memory(0x10000, 0) // default to 64KB of memory
{}

auto Memory::ReadByte(uint32_t address) -> uint8_t
{
    if (address >= m_memory.size())
    {
        throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
    }
    return m_memory[address];
}

auto Memory::ReadHalfWord(uint32_t address) -> uint16_t
{
    if (address >= m_memory.size() || m_memory.size() - address < sizeof(uint16_t))
    {
        throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
    }
    return static_cast<uint16_t>(m_memory[address]) | (static_cast<uint16_t>(m_memory[address + 1]) << 8);
}

auto Memory::ReadWord(uint32_t address) -> uint32_t
{
    if (address >= m_memory.size() || m_memory.size() - address < sizeof(uint32_t))
    {
        throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
    }
    return static_cast<uint32_t>(m_memory[address]) |
            (static_cast<uint32_t>(m_memory[address + 1]) << 8) |
            (static_cast<uint32_t>(m_memory[address + 2]) << 16) |
            (static_cast<uint32_t>(m_memory[address + 3]) << 24);
}

auto Memory::WriteByte(uint32_t address, uint8_t value) -> void
{
    if (address >= m_memory.size())
    {
        throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
    }
    m_memory[address] = value;
}

auto Memory::WriteHalfWord(uint32_t address, uint16_t value) -> void
{
    if (address >= m_memory.size() || m_memory.size() - address < sizeof(uint16_t))
    {
        throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
    }
    m_memory[address] = static_cast<uint8_t>(value & 0xFF);
    m_memory[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
}

auto Memory::WriteWord(uint32_t address, uint32_t value) -> void
{
    if (address >= m_memory.size() || m_memory.size() - address < sizeof(uint32_t))
    {
        throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
    }
    m_memory[address] = static_cast<uint8_t>(value & 0xFF);
    m_memory[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    m_memory[address + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
    m_memory[address + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);
}
