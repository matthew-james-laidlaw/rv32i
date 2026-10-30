#include "instruction_fixture.h"

using OrTests = InstructionTests;

TEST_F(OrTests, ComputesResult)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<OR>({.opcode = Opcode::R, .funct3 = Funct3::Or, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0b1110u);
}

TEST_F(OrTests, ComputesResultAcrossAll32Bits)
{
    core.registers.WriteGP(1, 0xF0F0F0F0u);
    core.registers.WriteGP(2, 0xFF00FF00u);
    ExecuteExpecting<OR>({.opcode = Opcode::R, .funct3 = Funct3::Or, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xFFF0FFF0u);
}

TEST_F(OrTests, AllOnesOperandYieldsAllOnes)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpecting<OR>({.opcode = Opcode::R, .funct3 = Funct3::Or, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xFFFFFFFFu);
}

TEST_F(OrTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 0xDEADBEEFu);
    ExecuteExpecting<OR>({.opcode = Opcode::R, .funct3 = Funct3::Or, .funct7 = Funct7::Base, .rs1 = 0, .rs2 = 2, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(OrTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<OR>({.opcode = Opcode::R, .funct3 = Funct3::Or, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 0, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(OrTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<OR>({.opcode = Opcode::R, .funct3 = Funct3::Or, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 1}, 0b1110u);
}

TEST_F(OrTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<OR>({.opcode = Opcode::R, .funct3 = Funct3::Or, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 2}, 0b1110u);
}

TEST_F(OrTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<OR>({.opcode = Opcode::R, .funct3 = Funct3::Or, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 1, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(OrTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<OR>({.opcode = Opcode::R, .funct3 = Funct3::Or, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}
