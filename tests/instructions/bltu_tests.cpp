#include "instruction_fixture.h"

using BltuTests = InstructionTests;

TEST_F(BltuTests, BranchesWhenFirstOperandIsUnsignedLess)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpectingPC<BLTU>({.opcode = Opcode::B, .funct3 = Funct3::Bltu, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x108u);
}

TEST_F(BltuTests, DistinguishesUnsignedFromSignedComparison)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 1);
    core.registers.WritePC(0x100u);
    ExecuteExpectingPC<BLTU>({.opcode = Opcode::B, .funct3 = Funct3::Bltu, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x100u);
}

TEST_F(BltuTests, DoesNotBranchWhenOperandsAreEqual)
{
    core.registers.WriteGP(1, 9);
    core.registers.WriteGP(2, 9);
    core.registers.WritePC(0x100u);
    ExecuteExpectingPC<BLTU>({.opcode = Opcode::B, .funct3 = Funct3::Bltu, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x100u);
}
