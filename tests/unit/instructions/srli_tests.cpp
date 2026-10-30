#include "instruction_fixture.h"

using SrliTests = InstructionTests;

TEST_F(SrliTests, ComputesResult)
{
    core.registers.WriteGP(1, 4);
    ExecuteExpecting<SRLI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rd = 3, .imm = 2}, 1u);
}

TEST_F(SrliTests, ShiftsByZeroWithoutChangingValue)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<SRLI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rd = 3, .imm = 0}, 0xDEADBEEFu);
}

TEST_F(SrliTests, FillsVacatedBitsWithZero)
{
    core.registers.WriteGP(1, 0x80000000u);
    ExecuteExpecting<SRLI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rd = 3, .imm = 1}, 0x40000000u);
}

TEST_F(SrliTests, UsesMaximumShiftAmount)
{
    core.registers.WriteGP(1, 0x80000000u);
    ExecuteExpecting<SRLI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rd = 3, .imm = 31}, 1u);
}

TEST_F(SrliTests, ReadsX0AsZero)
{
    ExecuteExpecting<SRLI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 0, .rd = 3, .imm = 5}, 0u);
}

TEST_F(SrliTests, WritesResultWhenDestinationAliasesSource)
{
    core.registers.WriteGP(1, 12);
    ExecuteExpecting<SRLI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rd = 1, .imm = 2}, 3u);
}

TEST_F(SrliTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 12);
    ExecuteExpecting<SRLI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rd = 0, .imm = 2}, 0u);
}
