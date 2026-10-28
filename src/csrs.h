#pragma once

#include <array>
#include <cstdint>

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
