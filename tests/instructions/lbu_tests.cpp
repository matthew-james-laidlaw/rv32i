#include "instruction_fixture.h"

using LbuTests = InstructionTests;

TEST_F(LbuTests, ZeroExtendsByteWithSignBitSet)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteByte(0x1000u, 0xFFu);
    ExecuteExpecting<LBU>({.opcode = Opcode::Load, .funct3 = Funct3::Lbu, .rs1 = 1, .rd = 3}, 0xFFu);
}

TEST_F(LbuTests, LoadsFromBasePlusOffset)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteByte(0x1004u, 0x80u);
    ExecuteExpecting<LBU>({.opcode = Opcode::Load, .funct3 = Funct3::Lbu, .rs1 = 1, .rd = 3, .imm = 4}, 0x80u);
}

TEST_F(LbuTests, WritesResultWhenDestinationAliasesBaseRegister)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteByte(0x1000u, 0xFFu);
    ExecuteExpecting<LBU>({.opcode = Opcode::Load, .funct3 = Funct3::Lbu, .rs1 = 1, .rd = 1}, 0xFFu);
}

TEST_F(LbuTests, DiscardsLoadedValueWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteByte(0x1000u, 0xFFu);
    ExecuteExpecting<LBU>({.opcode = Opcode::Load, .funct3 = Funct3::Lbu, .rs1 = 1, .rd = 0}, 0u);
}
