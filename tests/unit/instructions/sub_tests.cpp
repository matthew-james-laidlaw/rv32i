#include "instruction_fixture.h"

using SubTests = InstructionTests;

TEST_F(SubTests, ComputesResult)
{
    core.registers.WriteGP(1, 3);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 1u);
}

TEST_F(SubTests, ComputesResultForNegativeOperands)
{
    core.registers.WriteGP(1, static_cast<uint32_t>(-1));
    core.registers.WriteGP(2, static_cast<uint32_t>(-2));
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 1u);
}

TEST_F(SubTests, ComputesResultForMixedSignOperands)
{
    core.registers.WriteGP(1, 5);
    core.registers.WriteGP(2, static_cast<uint32_t>(-3));
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 8u);
}

TEST_F(SubTests, WrapsOnUnsignedOverflow)
{
    core.registers.WriteGP(1, 0);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xFFFFFFFFu);
}

TEST_F(SubTests, WrapsOnSignedOverflow)
{
    core.registers.WriteGP(1, 0x80000000u);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 0x7FFFFFFFu);
}

TEST_F(SubTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 7);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 0, .rs2 = 2, .rd = 3}, static_cast<uint32_t>(-7));
}

TEST_F(SubTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 9);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 0, .rd = 3}, 9u);
}

TEST_F(SubTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 10);
    core.registers.WriteGP(2, 4);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 1}, 6u);
}

TEST_F(SubTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 10);
    core.registers.WriteGP(2, 4);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 2}, 6u);
}

TEST_F(SubTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 0x80000001u);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 1, .rd = 3}, 0u);
}

TEST_F(SubTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 6);
    core.registers.WriteGP(2, 4);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}
