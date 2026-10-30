#include "instruction_fixture.h"

using SwTests = InstructionTests;

TEST_F(SwTests, StoresFullWord)
{
    core.registers.WriteGP(1, 0x1000u);
    core.registers.WriteGP(2, 0x89ABCDEFu);
    ExecuteUnchanged<SW>({.opcode = Opcode::S, .funct3 = Funct3::Sw, .rs1 = 1, .rs2 = 2});
    EXPECT_EQ(core.memory.ReadWord(0x1000u), 0x89ABCDEFu);
    EXPECT_EQ(core.memory.ReadByte(0x1004u), 0u);
}

TEST_F(SwTests, StoresAtBasePlusOffset)
{
    core.registers.WriteGP(1, 0x1000u);
    core.registers.WriteGP(2, 0x12345678u);
    ExecuteUnchanged<SW>({.opcode = Opcode::S, .funct3 = Funct3::Sw, .rs1 = 1, .rs2 = 2, .imm = 8});
    EXPECT_EQ(core.memory.ReadWord(0x1008u), 0x12345678u);
    EXPECT_EQ(core.memory.ReadByte(0x1007u), 0u);
    EXPECT_EQ(core.memory.ReadByte(0x100Cu), 0u);
}

TEST_F(SwTests, StoresZeroWhenSourceIsX0)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteWord(0x1000u, 0xFFFFFFFFu);
    ExecuteUnchanged<SW>({.opcode = Opcode::S, .funct3 = Funct3::Sw, .rs1 = 1, .rs2 = 0});
    EXPECT_EQ(core.memory.ReadWord(0x1000u), 0u);
}
