#include "instruction_fixture.h"

using SrlTests = InstructionTests;

TEST_F(SrlTests, ComputesResult)
{
    core.registers.WriteGP(1, 4);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SRL>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 1u);
}

TEST_F(SrlTests, ShiftsByZeroWithoutChangingValue)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    core.registers.WriteGP(2, 0);
    ExecuteExpecting<SRL>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(SrlTests, FillsVacatedBitsWithZero)
{
    core.registers.WriteGP(1, 0x80000000u);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SRL>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0x40000000u);
}

TEST_F(SrlTests, UsesOnlyLowFiveBitsOfShiftAmount)
{
    core.registers.WriteGP(1, 0x80000000u);
    core.registers.WriteGP(2, 0x21);
    ExecuteExpecting<SRL>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0x40000000u);
}

TEST_F(SrlTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 5);
    ExecuteExpecting<SRL>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 0, .rs2 = 2, .rd = 3}, 0u);
}

TEST_F(SrlTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<SRL>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 0, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(SrlTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 12);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SRL>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 1}, 3u);
}

TEST_F(SrlTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 12);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SRL>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 2}, 3u);
}

TEST_F(SrlTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SRL>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 1, .rd = 3}, 0u);
}

TEST_F(SrlTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 12);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SRL>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}
