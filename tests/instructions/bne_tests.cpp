#include "instruction_fixture.h"

using BneTests = InstructionTests;

TEST_F(BneTests, BranchesWhenRegistersDiffer)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 2);
    ExecuteExpectingPC<BNE>({.opcode = Opcode::B, .funct3 = Funct3::Bne, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x108u);
}

TEST_F(BneTests, DoesNotBranchWhenRegistersAreEqual)
{
    core.registers.WriteGP(1, 7);
    core.registers.WriteGP(2, 7);
    core.registers.WritePC(0x100u);
    ExecuteExpectingPC<BNE>({.opcode = Opcode::B, .funct3 = Funct3::Bne, .rs1 = 1, .rs2 = 2, .imm = 8, .pc = 0x100u}, 0x100u);
}
