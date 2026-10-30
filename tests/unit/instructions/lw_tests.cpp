#include "instruction_fixture.h"

using LwTests = InstructionTests;

TEST_F(LwTests, LoadsFullWord)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteWord(0x1000u, 0x89ABCDEFu);
    ExecuteExpecting<LW>({.opcode = Opcode::Load, .funct3 = Funct3::Lw, .rs1 = 1, .rd = 3}, 0x89ABCDEFu);
}

TEST_F(LwTests, LoadsFromBasePlusOffset)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteWord(0x1008u, 0x12345678u);
    ExecuteExpecting<LW>({.opcode = Opcode::Load, .funct3 = Funct3::Lw, .rs1 = 1, .rd = 3, .imm = 8}, 0x12345678u);
}

TEST_F(LwTests, WritesResultWhenDestinationAliasesBaseRegister)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteWord(0x1000u, 0x12345678u);
    ExecuteExpecting<LW>({.opcode = Opcode::Load, .funct3 = Funct3::Lw, .rs1 = 1, .rd = 1}, 0x12345678u);
}

TEST_F(LwTests, DiscardsLoadedValueWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteWord(0x1000u, 0x12345678u);
    ExecuteExpecting<LW>({.opcode = Opcode::Load, .funct3 = Funct3::Lw, .rs1 = 1, .rd = 0}, 0u);
}
