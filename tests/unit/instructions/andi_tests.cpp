#include "instruction_fixture.h"

using AndiTests = InstructionTests;

TEST_F(AndiTests, ComputesResult)
{
    core.registers.WriteGP(1, 0b1100);
    ExecuteExpecting<ANDI>({.opcode = Opcode::I, .funct3 = Funct3::And, .rs1 = 1, .rd = 3, .imm = 0b1010}, 0b1000u);
}

TEST_F(AndiTests, SignExtendedAllOnesImmediateLeavesValueUnchanged)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<ANDI>({.opcode = Opcode::I, .funct3 = Funct3::And, .rs1 = 1, .rd = 3, .imm = 0xFFFFFFFFu}, 0xDEADBEEFu);
}

TEST_F(AndiTests, AppliesSignExtendedNegativeImmediate)
{
    core.registers.WriteGP(1, 0x80000000u);
    ExecuteExpecting<ANDI>({.opcode = Opcode::I, .funct3 = Funct3::And, .rs1 = 1, .rd = 3, .imm = static_cast<uint32_t>(-2048)}, 0x80000000u);
}

TEST_F(AndiTests, ReadsX0AsZero)
{
    ExecuteExpecting<ANDI>({.opcode = Opcode::I, .funct3 = Funct3::And, .rs1 = 0, .rd = 3, .imm = 0xFFFFFFFFu}, 0u);
}

TEST_F(AndiTests, WritesResultWhenDestinationAliasesSource)
{
    core.registers.WriteGP(1, 0xF0F0u);
    ExecuteExpecting<ANDI>({.opcode = Opcode::I, .funct3 = Funct3::And, .rs1 = 1, .rd = 1, .imm = 0x0FF0u}, 0x00F0u);
}

TEST_F(AndiTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0xF0F0u);
    ExecuteExpecting<ANDI>({.opcode = Opcode::I, .funct3 = Funct3::And, .rs1 = 1, .rd = 0, .imm = 0x0FF0u}, 0u);
}
