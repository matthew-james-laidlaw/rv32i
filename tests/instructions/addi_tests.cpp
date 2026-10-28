#include "instruction_fixture.h"

using AddiTests = InstructionTests;

TEST_F(AddiTests, ComputesResult)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<ADDI>({.opcode = Opcode::I, .funct3 = Funct3::AddSub, .rs1 = 1, .rd = 3, .imm = 2}, 3u);
}

TEST_F(AddiTests, AddsSignExtendedNegativeImmediate)
{
    core.registers.WriteGP(1, 5);
    ExecuteExpecting<ADDI>({.opcode = Opcode::I, .funct3 = Funct3::AddSub, .rs1 = 1, .rd = 3, .imm = static_cast<uint32_t>(-3)}, 2u);
}

TEST_F(AddiTests, WrapsOnUnsignedOverflow)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    ExecuteExpecting<ADDI>({.opcode = Opcode::I, .funct3 = Funct3::AddSub, .rs1 = 1, .rd = 3, .imm = 1}, 0u);
}

TEST_F(AddiTests, WrapsOnSignedOverflow)
{
    core.registers.WriteGP(1, 0x7FFFFFFFu);
    ExecuteExpecting<ADDI>({.opcode = Opcode::I, .funct3 = Funct3::AddSub, .rs1 = 1, .rd = 3, .imm = 1}, 0x80000000u);
}

TEST_F(AddiTests, ReadsX0AsZero)
{
    ExecuteExpecting<ADDI>({.opcode = Opcode::I, .funct3 = Funct3::AddSub, .rs1 = 0, .rd = 3, .imm = 5}, 5u);
}

TEST_F(AddiTests, WritesResultWhenDestinationAliasesSource)
{
    core.registers.WriteGP(1, 5);
    ExecuteExpecting<ADDI>({.opcode = Opcode::I, .funct3 = Funct3::AddSub, .rs1 = 1, .rd = 1, .imm = 3}, 8u);
}

TEST_F(AddiTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 5);
    ExecuteExpecting<ADDI>({.opcode = Opcode::I, .funct3 = Funct3::AddSub, .rs1 = 1, .rd = 0, .imm = 3}, 0u);
}
