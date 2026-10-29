#pragma once

#include <array>
#include <cstdint>

namespace Csr
{
    inline constexpr uint32_t Mtvec  = 0x305;
    inline constexpr uint32_t Mepc   = 0x341;
    inline constexpr uint32_t Mcause = 0x342;
}

namespace TrapCause
{
    inline constexpr uint32_t Breakpoint        = 3;
    inline constexpr uint32_t EcallFromMMode    = 11;
}

class Csrs
{
private:

    std::array<uint32_t, 4096> m_csrs{};

public:

    auto Read(uint32_t address) const -> uint32_t
    {
        return m_csrs[address & 0xFFF];
    }

    auto Write(uint32_t address, uint32_t value) -> void
    {
        m_csrs[address & 0xFFF] = value;
    }

};
