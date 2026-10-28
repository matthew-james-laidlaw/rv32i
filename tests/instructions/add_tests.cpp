#include "instruction_fixture.h"

using AddTests = InstructionTests;

TEST_F(AddTests, ComputesResult)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 3u);
}

TEST_F(AddTests, ComputesResultForNegativeOperands)
{
    core.registers.WriteGP(1, static_cast<uint32_t>(-1));
    core.registers.WriteGP(2, static_cast<uint32_t>(-2));
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, static_cast<uint32_t>(-3));
}

TEST_F(AddTests, ComputesResultForMixedSignOperands)
{
    core.registers.WriteGP(1, 5);
    core.registers.WriteGP(2, static_cast<uint32_t>(-3));
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 2u);
}

TEST_F(AddTests, WrapsOnUnsignedOverflow)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0u);
}

TEST_F(AddTests, WrapsOnSignedOverflow)
{
    core.registers.WriteGP(1, 0x7FFFFFFFu);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0x80000000u);
}

TEST_F(AddTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 7);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 0, .rs2 = 2, .rd = 3}, 7u);
}

TEST_F(AddTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 9);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 0, .rd = 3}, 9u);
}

TEST_F(AddTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 4);
    core.registers.WriteGP(2, 6);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 1}, 10u);
}

TEST_F(AddTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 4);
    core.registers.WriteGP(2, 6);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 2}, 10u);
}

TEST_F(AddTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 0x80000001u);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 1, .rd = 3}, 2u);
}

TEST_F(AddTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 4);
    core.registers.WriteGP(2, 6);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}
