#include "instruction_fixture.h"

using SltuTests = InstructionTests;

TEST_F(SltuTests, ComputesResult)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SLTU>({.opcode = Opcode::R, .funct3 = Funct3::Sltu, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 1u);
}

TEST_F(SltuTests, ComparesZeroAsLessThanUnsignedMaximum)
{
    core.registers.WriteGP(1, 0);
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpecting<SLTU>({.opcode = Opcode::R, .funct3 = Funct3::Sltu, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 1u);
}

TEST_F(SltuTests, ComparesUnsignedMaximumAsNotLessThanOne)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SLTU>({.opcode = Opcode::R, .funct3 = Funct3::Sltu, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0u);
}

TEST_F(SltuTests, ComparesEqualValuesAsNotLessThan)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpecting<SLTU>({.opcode = Opcode::R, .funct3 = Funct3::Sltu, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0u);
}

TEST_F(SltuTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpecting<SLTU>({.opcode = Opcode::R, .funct3 = Funct3::Sltu, .funct7 = Funct7::Base, .rs1 = 0, .rs2 = 2, .rd = 3}, 1u);
}

TEST_F(SltuTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SLTU>({.opcode = Opcode::R, .funct3 = Funct3::Sltu, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 0, .rd = 3}, 0u);
}

TEST_F(SltuTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 0);
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpecting<SLTU>({.opcode = Opcode::R, .funct3 = Funct3::Sltu, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 1}, 1u);
}

TEST_F(SltuTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 0);
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpecting<SLTU>({.opcode = Opcode::R, .funct3 = Funct3::Sltu, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 2}, 1u);
}

TEST_F(SltuTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 0x80000000u);
    ExecuteExpecting<SLTU>({.opcode = Opcode::R, .funct3 = Funct3::Sltu, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 1, .rd = 3}, 0u);
}

TEST_F(SltuTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0);
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpecting<SLTU>({.opcode = Opcode::R, .funct3 = Funct3::Sltu, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}
