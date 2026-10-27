#include <gtest/gtest.h>

#include <core.h>

TEST(CoreTests, SimpleProgram)
{
    auto program = std::vector<uint8_t>
    {
        // Address  Instruction          Machine Code
        // -------  -----------          ------------
        // 0x00     addi t0, x0, 10      00a00293
        0x93, 0x02, 0xa0, 0x00,

        // 0x04     addi t1, x0, 0       00000313
        0x13, 0x03, 0x00, 0x00,

        // 0x08     addi t2, x0, 1       00100393
        0x93, 0x03, 0x10, 0x00,

        // 0x0C     addi t3, x0, 0       00000e13
        0x13, 0x0e, 0x00, 0x00,

        // 0x10     bge t3, t0, done     005e5c63
        0x63, 0x5c, 0x5e, 0x00,

        // 0x14     add t4, t1, x0       00030eb3
        0xb3, 0x0e, 0x03, 0x00,

        // 0x18     add t1, t2, x0       00038333
        0x33, 0x83, 0x03, 0x00,

        // 0x1C     add t2, t4, t2       007e83b3
        0xb3, 0x83, 0x7e, 0x00,

        // 0x20     addi t3, t3, 1       001e0e13
        0x13, 0x0e, 0x1e, 0x00,

        // 0x24     jal x0, loop         fedff06f
        0x6f, 0xf0, 0xdf, 0xfe,
    };

    auto core = Core();
    core.Load(program);

    core.Run(65u);

    EXPECT_EQ(core.registers.ReadGP(6), 55u);
}
