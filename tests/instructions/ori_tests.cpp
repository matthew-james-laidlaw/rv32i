#include "instruction_fixture.h"

using OriTests = InstructionTests;

TEST_F(OriTests, ComputesResult)
{
    core.registers.WriteGP(1, 0b1100);
    ExecuteExpecting<ORI>({.opcode = Opcode::I, .funct3 = Funct3::Or, .rs1 = 1, .rd = 3, .imm = 0b1010}, 0b1110u);
}

TEST_F(OriTests, SignExtendedNegativeImmediateSetsUpperBits)
{
    core.registers.WriteGP(1, 0x123u);
    ExecuteExpecting<ORI>({.opcode = Opcode::I, .funct3 = Funct3::Or, .rs1 = 1, .rd = 3, .imm = static_cast<uint32_t>(-2048)}, 0xFFFFF923u);
}

TEST_F(OriTests, ZeroImmediateLeavesValueUnchanged)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<ORI>({.opcode = Opcode::I, .funct3 = Funct3::Or, .rs1 = 1, .rd = 3, .imm = 0}, 0xDEADBEEFu);
}

TEST_F(OriTests, ReadsX0AsZero)
{
    ExecuteExpecting<ORI>({.opcode = Opcode::I, .funct3 = Funct3::Or, .rs1 = 0, .rd = 3, .imm = 5}, 5u);
}

TEST_F(OriTests, WritesResultWhenDestinationAliasesSource)
{
    core.registers.WriteGP(1, 0xF000u);
    ExecuteExpecting<ORI>({.opcode = Opcode::I, .funct3 = Funct3::Or, .rs1 = 1, .rd = 1, .imm = 0x00F0u}, 0xF0F0u);
}

TEST_F(OriTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0xF000u);
    ExecuteExpecting<ORI>({.opcode = Opcode::I, .funct3 = Funct3::Or, .rs1 = 1, .rd = 0, .imm = 0x00F0u}, 0u);
}
