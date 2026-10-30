#include "instruction_fixture.h"

using SlliTests = InstructionTests;

TEST_F(SlliTests, ComputesResult)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SLLI>({.opcode = Opcode::I, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rd = 3, .imm = 2}, 4u);
}

TEST_F(SlliTests, ShiftsByZeroWithoutChangingValue)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<SLLI>({.opcode = Opcode::I, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rd = 3, .imm = 0}, 0xDEADBEEFu);
}

TEST_F(SlliTests, UsesMaximumShiftAmount)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SLLI>({.opcode = Opcode::I, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rd = 3, .imm = 31}, 0x80000000u);
}

TEST_F(SlliTests, DiscardsBitsShiftedPastWordWidth)
{
    core.registers.WriteGP(1, 0x80000001u);
    ExecuteExpecting<SLLI>({.opcode = Opcode::I, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rd = 3, .imm = 1}, 2u);
}

TEST_F(SlliTests, ReadsX0AsZero)
{
    ExecuteExpecting<SLLI>({.opcode = Opcode::I, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 0, .rd = 3, .imm = 5}, 0u);
}

TEST_F(SlliTests, WritesResultWhenDestinationAliasesSource)
{
    core.registers.WriteGP(1, 3);
    ExecuteExpecting<SLLI>({.opcode = Opcode::I, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rd = 1, .imm = 2}, 12u);
}

TEST_F(SlliTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 3);
    ExecuteExpecting<SLLI>({.opcode = Opcode::I, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rd = 0, .imm = 2}, 0u);
}
