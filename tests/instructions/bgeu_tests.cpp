#include "instruction_fixture.h"

using BgeuTests = InstructionTests;

TEST_F(BgeuTests, BranchesWhenFirstOperandIsUnsignedGreater)
{
    core.registers.WriteGP(1, 6);
    core.registers.WriteGP(2, 5);
    ExecuteExpectingPC<BGEU>({.opcode = Opcode::B, .funct3 = Funct3::Bgeu, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x108u);
}

TEST_F(BgeuTests, BranchesWhenUnsignedOperandsAreEqual)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpectingPC<BGEU>({.opcode = Opcode::B, .funct3 = Funct3::Bgeu, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x108u);
}

TEST_F(BgeuTests, DistinguishesUnsignedFromSignedComparison)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 1);
    ExecuteExpectingPC<BGEU>({.opcode = Opcode::B, .funct3 = Funct3::Bgeu, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x108u);
}
