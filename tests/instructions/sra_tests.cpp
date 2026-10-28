#include "instruction_fixture.h"

using SraTests = InstructionTests;

TEST_F(SraTests, ComputesResult)
{
    core.registers.WriteGP(1, 0xFFFFFFFCu);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xFFFFFFFFu);
}

TEST_F(SraTests, PreservesSignBitWhenShiftingNegativeValue)
{
    core.registers.WriteGP(1, 0x80000000u);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xC0000000u);
}

TEST_F(SraTests, DoesNotFillWithOnesWhenShiftingPositiveValue)
{
    core.registers.WriteGP(1, 0x7FFFFFFCu);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 0x1FFFFFFFu);
}

TEST_F(SraTests, ShiftsByZeroWithoutChangingValue)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    core.registers.WriteGP(2, 0);
    ExecuteExpecting<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(SraTests, UsesOnlyLowFiveBitsOfShiftAmount)
{
    core.registers.WriteGP(1, 0x80000000u);
    core.registers.WriteGP(2, 0x21);
    ExecuteExpecting<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xC0000000u);
}

TEST_F(SraTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 5);
    ExecuteExpecting<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 0, .rs2 = 2, .rd = 3}, 0u);
}

TEST_F(SraTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 0, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(SraTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 0xFFFFFFF0u);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 1}, 0xFFFFFFFCu);
}

TEST_F(SraTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 0xFFFFFFF0u);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 2}, 0xFFFFFFFCu);
}

TEST_F(SraTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    ExecuteExpecting<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 1, .rd = 3}, 0xFFFFFFFFu);
}

TEST_F(SraTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0xFFFFFFF0u);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}
