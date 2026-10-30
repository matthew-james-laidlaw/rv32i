#include "instruction_fixture.h"

using AndTests = InstructionTests;

TEST_F(AndTests, ComputesResult)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<AND>({.opcode = Opcode::R, .funct3 = Funct3::And, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0b1000u);
}

TEST_F(AndTests, ComputesResultAcrossAll32Bits)
{
    core.registers.WriteGP(1, 0xF0F0F0F0u);
    core.registers.WriteGP(2, 0xFF00FF00u);
    ExecuteExpecting<AND>({.opcode = Opcode::R, .funct3 = Funct3::And, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xF000F000u);
}

TEST_F(AndTests, AllOnesOperandLeavesOtherOperandUnchanged)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpecting<AND>({.opcode = Opcode::R, .funct3 = Funct3::And, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(AndTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 0xDEADBEEFu);
    ExecuteExpecting<AND>({.opcode = Opcode::R, .funct3 = Funct3::And, .funct7 = Funct7::Base, .rs1 = 0, .rs2 = 2, .rd = 3}, 0u);
}

TEST_F(AndTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<AND>({.opcode = Opcode::R, .funct3 = Funct3::And, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 0, .rd = 3}, 0u);
}

TEST_F(AndTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<AND>({.opcode = Opcode::R, .funct3 = Funct3::And, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 1}, 0b1000u);
}

TEST_F(AndTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<AND>({.opcode = Opcode::R, .funct3 = Funct3::And, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 2}, 0b1000u);
}

TEST_F(AndTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<AND>({.opcode = Opcode::R, .funct3 = Funct3::And, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 1, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(AndTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<AND>({.opcode = Opcode::R, .funct3 = Funct3::And, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}
