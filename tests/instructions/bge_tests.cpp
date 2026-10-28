#include "instruction_fixture.h"

using BgeTests = InstructionTests;

TEST_F(BgeTests, BranchesWhenFirstOperandIsGreater)
{
    core.registers.WriteGP(1, 6);
    core.registers.WriteGP(2, 5);
    ExecuteExpectingPC<BGE>({.opcode = Opcode::B, .funct3 = Funct3::Bge, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x108u);
}

TEST_F(BgeTests, BranchesWhenSignedOperandsAreEqual)
{
    core.registers.WriteGP(1, 0x80000000u);
    core.registers.WriteGP(2, 0x80000000u);
    ExecuteExpectingPC<BGE>({.opcode = Opcode::B, .funct3 = Funct3::Bge, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x108u);
}

TEST_F(BgeTests, ComparesOperandsAsSigned)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 1);
    core.registers.WritePC(0x100u);
    ExecuteExpectingPC<BGE>({.opcode = Opcode::B, .funct3 = Funct3::Bge, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x100u);
}
