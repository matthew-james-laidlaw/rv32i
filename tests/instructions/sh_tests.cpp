#include "instruction_fixture.h"

using ShTests = InstructionTests;

TEST_F(ShTests, StoresLowHalfwordOfSource)
{
    core.registers.WriteGP(1, 0x1000u);
    core.registers.WriteGP(2, 0x12345678u);
    ExecuteUnchanged<SH>({.opcode = Opcode::S, .funct3 = Funct3::Sh, .rs1 = 1, .rs2 = 2});
    EXPECT_EQ(core.memory.ReadHalfWord(0x1000u), 0x5678u);
    EXPECT_EQ(core.memory.ReadByte(0x1002u), 0u);
}

TEST_F(ShTests, StoresAtBasePlusOffset)
{
    core.registers.WriteGP(1, 0x1000u);
    core.registers.WriteGP(2, 0xABCDu);
    ExecuteUnchanged<SH>({.opcode = Opcode::S, .funct3 = Funct3::Sh, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.memory.ReadHalfWord(0x1004u), 0xABCDu);
    EXPECT_EQ(core.memory.ReadByte(0x1003u), 0u);
    EXPECT_EQ(core.memory.ReadByte(0x1006u), 0u);
}

TEST_F(ShTests, StoresZeroWhenSourceIsX0)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteHalfWord(0x1000u, 0xFFFFu);
    ExecuteUnchanged<SH>({.opcode = Opcode::S, .funct3 = Funct3::Sh, .rs1 = 1, .rs2 = 0});
    EXPECT_EQ(core.memory.ReadHalfWord(0x1000u), 0u);
}
