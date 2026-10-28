#include "instruction_fixture.h"

using SllTests = InstructionTests;

TEST_F(SllTests, ComputesResult)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SLL>({.opcode = Opcode::R, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 4u);
}

TEST_F(SllTests, ShiftsByZeroWithoutChangingValue)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    core.registers.WriteGP(2, 0);
    ExecuteExpecting<SLL>({.opcode = Opcode::R, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(SllTests, ShiftsIntoSignBit)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 31);
    ExecuteExpecting<SLL>({.opcode = Opcode::R, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0x80000000u);
}

TEST_F(SllTests, UsesOnlyLowFiveBitsOfShiftAmount)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 0x21);
    ExecuteExpecting<SLL>({.opcode = Opcode::R, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 2u);
}

TEST_F(SllTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 5);
    ExecuteExpecting<SLL>({.opcode = Opcode::R, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 0, .rs2 = 2, .rd = 3}, 0u);
}

TEST_F(SllTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<SLL>({.opcode = Opcode::R, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 0, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(SllTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 3);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SLL>({.opcode = Opcode::R, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 1}, 12u);
}

TEST_F(SllTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 3);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SLL>({.opcode = Opcode::R, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 2}, 12u);
}

TEST_F(SllTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SLL>({.opcode = Opcode::R, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 1, .rd = 3}, 2u);
}

TEST_F(SllTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 3);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SLL>({.opcode = Opcode::R, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}
