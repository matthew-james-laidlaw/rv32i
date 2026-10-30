#include "instruction_fixture.h"

using LhuTests = InstructionTests;

TEST_F(LhuTests, ZeroExtendsHalfwordWithSignBitSet)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteHalfWord(0x1000u, 0xFFFFu);
    ExecuteExpecting<LHU>({.opcode = Opcode::Load, .funct3 = Funct3::Lhu, .rs1 = 1, .rd = 3}, 0xFFFFu);
}

TEST_F(LhuTests, LoadsFromBasePlusOffset)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteHalfWord(0x1004u, 0x8000u);
    ExecuteExpecting<LHU>({.opcode = Opcode::Load, .funct3 = Funct3::Lhu, .rs1 = 1, .rd = 3, .imm = 4}, 0x8000u);
}

TEST_F(LhuTests, WritesResultWhenDestinationAliasesBaseRegister)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteHalfWord(0x1000u, 0xFFFFu);
    ExecuteExpecting<LHU>({.opcode = Opcode::Load, .funct3 = Funct3::Lhu, .rs1 = 1, .rd = 1}, 0xFFFFu);
}

TEST_F(LhuTests, DiscardsLoadedValueWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteHalfWord(0x1000u, 0xFFFFu);
    ExecuteExpecting<LHU>({.opcode = Opcode::Load, .funct3 = Funct3::Lhu, .rs1 = 1, .rd = 0}, 0u);
}
