#include "instruction_fixture.h"

using BeqTests = InstructionTests;

TEST_F(BeqTests, BranchesWhenRegistersAreEqual)
{
    core.registers.WriteGP(1, 0x12345678u);
    core.registers.WriteGP(2, 0x12345678u);
    ExecuteExpectingPC<BEQ>({.opcode = Opcode::B, .funct3 = Funct3::Beq, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x108u);
}

TEST_F(BeqTests, DoesNotBranchWhenRegistersDiffer)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 2);
    core.registers.WritePC(0x100u);
    ExecuteExpectingPC<BEQ>({.opcode = Opcode::B, .funct3 = Funct3::Beq, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x100u);
}

TEST_F(BeqTests, BranchesWithNegativeOffset)
{
    core.registers.WriteGP(1, 7);
    core.registers.WriteGP(2, 7);
    ExecuteExpectingPC<BEQ>({.opcode = Opcode::B, .funct3 = Funct3::Beq, .rs1 = 1, .rs2 = 2, .imm = static_cast<uint32_t>(-8), .pc = 0x100u}, 0xF8u);
}
