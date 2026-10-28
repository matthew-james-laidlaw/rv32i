#include <memory.h>

#include <format>
#include <stdexcept>

Memory::Memory(size_t memory_size, uint32_t base)
    : m_memory(memory_size, 0)
    , m_base(base)
{}

auto Memory::Base() const -> uint32_t
{
    return m_base;
}

// Translates a guest address into an index into m_memory, throwing if `length` bytes don't fit.
auto Memory::Translate(uint32_t address, size_t length) const -> size_t
{
    auto offset = static_cast<uint32_t>(address - m_base);
    if (offset >= m_memory.size() || m_memory.size() - offset < length)
    {
        throw std::runtime_error(std::format("out of bounds memory access at address 0x{:08X}", address));
    }
    return offset;
}

auto Memory::ReadByte(uint32_t address) -> uint8_t
{
    auto index = Translate(address, 1);
    return m_memory[index];
}

auto Memory::ReadHalfWord(uint32_t address) -> uint16_t
{
    auto index = Translate(address, sizeof(uint16_t));
    return static_cast<uint16_t>(m_memory[index]) | (static_cast<uint16_t>(m_memory[index + 1]) << 8);
}

auto Memory::ReadWord(uint32_t address) -> uint32_t
{
    auto index = Translate(address, sizeof(uint32_t));
    return static_cast<uint32_t>(m_memory[index]) |
            (static_cast<uint32_t>(m_memory[index + 1]) << 8) |
            (static_cast<uint32_t>(m_memory[index + 2]) << 16) |
            (static_cast<uint32_t>(m_memory[index + 3]) << 24);
}

auto Memory::WriteByte(uint32_t address, uint8_t value) -> void
{
    auto index = Translate(address, 1);
    m_memory[index] = value;
}

auto Memory::WriteHalfWord(uint32_t address, uint16_t value) -> void
{
    auto index = Translate(address, sizeof(uint16_t));
    m_memory[index] = static_cast<uint8_t>(value & 0xFF);
    m_memory[index + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
}

auto Memory::WriteWord(uint32_t address, uint32_t value) -> void
{
    auto index = Translate(address, sizeof(uint32_t));
    m_memory[index] = static_cast<uint8_t>(value & 0xFF);
    m_memory[index + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    m_memory[index + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
    m_memory[index + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);
}
