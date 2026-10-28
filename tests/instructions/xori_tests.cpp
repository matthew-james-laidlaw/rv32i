#include "instruction_fixture.h"

using XoriTests = InstructionTests;

TEST_F(XoriTests, ComputesResult)
{
    core.registers.WriteGP(1, 0b1100);
    ExecuteExpecting<XORI>({.opcode = Opcode::I, .funct3 = Funct3::Xor, .rs1 = 1, .rd = 3, .imm = 0b1010}, 0b0110u);
}

TEST_F(XoriTests, SignExtendedAllOnesImmediateInvertsValue)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<XORI>({.opcode = Opcode::I, .funct3 = Funct3::Xor, .rs1 = 1, .rd = 3, .imm = 0xFFFFFFFFu}, 0x21524110u);
}

TEST_F(XoriTests, ZeroImmediateLeavesValueUnchanged)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<XORI>({.opcode = Opcode::I, .funct3 = Funct3::Xor, .rs1 = 1, .rd = 3, .imm = 0}, 0xDEADBEEFu);
}

TEST_F(XoriTests, ReadsX0AsZero)
{
    ExecuteExpecting<XORI>({.opcode = Opcode::I, .funct3 = Funct3::Xor, .rs1 = 0, .rd = 3, .imm = 5}, 5u);
}

TEST_F(XoriTests, WritesResultWhenDestinationAliasesSource)
{
    core.registers.WriteGP(1, 0xF0F0u);
    ExecuteExpecting<XORI>({.opcode = Opcode::I, .funct3 = Funct3::Xor, .rs1 = 1, .rd = 1, .imm = 0x0FF0u}, 0xFF00u);
}

TEST_F(XoriTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0xF0F0u);
    ExecuteExpecting<XORI>({.opcode = Opcode::I, .funct3 = Funct3::Xor, .rs1 = 1, .rd = 0, .imm = 0x0FF0u}, 0u);
}
