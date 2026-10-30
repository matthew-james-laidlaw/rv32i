#include "instruction_fixture.h"

using SbTests = InstructionTests;

TEST_F(SbTests, StoresLowByteOfSource)
{
    core.registers.WriteGP(1, 0x1000u);
    core.registers.WriteGP(2, 0x123456ABu);
    ExecuteUnchanged<SB>({.opcode = Opcode::S, .funct3 = Funct3::Sb, .rs1 = 1, .rs2 = 2});
    EXPECT_EQ(core.memory.ReadByte(0x1000u), 0xABu);
    EXPECT_EQ(core.memory.ReadByte(0x1001u), 0u);
}

TEST_F(SbTests, StoresAtBasePlusOffset)
{
    core.registers.WriteGP(1, 0x1000u);
    core.registers.WriteGP(2, 0xFFu);
    ExecuteUnchanged<SB>({.opcode = Opcode::S, .funct3 = Funct3::Sb, .rs1 = 1, .rs2 = 2, .imm = 3});
    EXPECT_EQ(core.memory.ReadByte(0x1003u), 0xFFu);
    EXPECT_EQ(core.memory.ReadByte(0x1002u), 0u);
    EXPECT_EQ(core.memory.ReadByte(0x1004u), 0u);
}

TEST_F(SbTests, StoresZeroWhenSourceIsX0)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteByte(0x1000u, 0xFFu);
    ExecuteUnchanged<SB>({.opcode = Opcode::S, .funct3 = Funct3::Sb, .rs1 = 1, .rs2 = 0});
    EXPECT_EQ(core.memory.ReadByte(0x1000u), 0u);
}
