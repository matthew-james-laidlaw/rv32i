#include "instruction_fixture.h"

using SraiTests = InstructionTests;

TEST_F(SraiTests, ComputesResult)
{
    core.registers.WriteGP(1, 0xFFFFFFFCu);
    ExecuteExpecting<SRAI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rd = 3, .imm = 2}, 0xFFFFFFFFu);
}

TEST_F(SraiTests, PreservesSignBitWhenShiftingNegativeValue)
{
    core.registers.WriteGP(1, 0x80000000u);
    ExecuteExpecting<SRAI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rd = 3, .imm = 1}, 0xC0000000u);
}

TEST_F(SraiTests, DoesNotFillWithOnesWhenShiftingPositiveValue)
{
    core.registers.WriteGP(1, 0x7FFFFFFCu);
    ExecuteExpecting<SRAI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rd = 3, .imm = 2}, 0x1FFFFFFFu);
}

TEST_F(SraiTests, UsesMaximumShiftAmount)
{
    core.registers.WriteGP(1, 0x80000000u);
    ExecuteExpecting<SRAI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rd = 3, .imm = 31}, 0xFFFFFFFFu);
}

TEST_F(SraiTests, ReadsX0AsZero)
{
    ExecuteExpecting<SRAI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 0, .rd = 3, .imm = 5}, 0u);
}

TEST_F(SraiTests, WritesResultWhenDestinationAliasesSource)
{
    core.registers.WriteGP(1, 0xFFFFFFF0u);
    ExecuteExpecting<SRAI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rd = 1, .imm = 2}, 0xFFFFFFFCu);
}

TEST_F(SraiTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0xFFFFFFF0u);
    ExecuteExpecting<SRAI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rd = 0, .imm = 2}, 0u);
}
