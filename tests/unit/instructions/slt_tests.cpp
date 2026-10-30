#include "instruction_fixture.h"

using SltTests = InstructionTests;

TEST_F(SltTests, ComputesResult)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SLT>({.opcode = Opcode::R, .funct3 = Funct3::Slt, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 1u);
}

TEST_F(SltTests, ComparesNegativeValueAsLessThanPositiveValue)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SLT>({.opcode = Opcode::R, .funct3 = Funct3::Slt, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 1u);
}

TEST_F(SltTests, ComparesPositiveValueAsNotLessThanNegativeValue)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpecting<SLT>({.opcode = Opcode::R, .funct3 = Funct3::Slt, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0u);
}

TEST_F(SltTests, ComparesEqualValuesAsNotLessThan)
{
    core.registers.WriteGP(1, 0x80000000u);
    core.registers.WriteGP(2, 0x80000000u);
    ExecuteExpecting<SLT>({.opcode = Opcode::R, .funct3 = Funct3::Slt, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0u);
}

TEST_F(SltTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SLT>({.opcode = Opcode::R, .funct3 = Funct3::Slt, .funct7 = Funct7::Base, .rs1 = 0, .rs2 = 2, .rd = 3}, 1u);
}

TEST_F(SltTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SLT>({.opcode = Opcode::R, .funct3 = Funct3::Slt, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 0, .rd = 3}, 0u);
}

TEST_F(SltTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SLT>({.opcode = Opcode::R, .funct3 = Funct3::Slt, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 1}, 1u);
}

TEST_F(SltTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SLT>({.opcode = Opcode::R, .funct3 = Funct3::Slt, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 2}, 1u);
}

TEST_F(SltTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 0x80000000u);
    ExecuteExpecting<SLT>({.opcode = Opcode::R, .funct3 = Funct3::Slt, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 1, .rd = 3}, 0u);
}

TEST_F(SltTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SLT>({.opcode = Opcode::R, .funct3 = Funct3::Slt, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}
