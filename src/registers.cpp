#include <registers.h>

auto Registers::ReadGP(uint8_t index) -> uint32_t
{
    return x[index];
}

auto Registers::WriteGP(uint8_t index, uint32_t value) -> void
{
    if (index != 0)
    {
        x[index] = value;
    }
}

auto Registers::ReadPC() -> uint32_t
{
    return pc;
}

auto Registers::WritePC(uint32_t value) -> void
{
    pc = value;
}
