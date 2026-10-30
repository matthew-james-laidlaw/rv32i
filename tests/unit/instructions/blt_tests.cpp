#include "instruction_fixture.h"

using BltTests = InstructionTests;

TEST_F(BltTests, BranchesWhenFirstOperandIsLess)
{
    core.registers.WriteGP(1, 5);
    core.registers.WriteGP(2, 6);
    ExecuteExpectingPC<BLT>({.opcode = Opcode::B, .funct3 = Funct3::Blt, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x108u);
}

TEST_F(BltTests, ComparesOperandsAsSigned)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 1);
    ExecuteExpectingPC<BLT>({.opcode = Opcode::B, .funct3 = Funct3::Blt, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x108u);
}

TEST_F(BltTests, DoesNotBranchWhenOperandsAreEqual)
{
    core.registers.WriteGP(1, 0x80000000u);
    core.registers.WriteGP(2, 0x80000000u);
    core.registers.WritePC(0x100u);
    ExecuteExpectingPC<BLT>({.opcode = Opcode::B, .funct3 = Funct3::Blt, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x100u);
}
