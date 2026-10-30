#include "instruction_fixture.h"

using LhTests = InstructionTests;

TEST_F(LhTests, SignExtendsPositiveHalfword)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteHalfWord(0x1000u, 0x7FFFu);
    ExecuteExpecting<LH>({.opcode = Opcode::Load, .funct3 = Funct3::Lh, .rs1 = 1, .rd = 3}, 0x7FFFu);
}

TEST_F(LhTests, SignExtendsNegativeHalfword)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteHalfWord(0x1000u, 0x8000u);
    ExecuteExpecting<LH>({.opcode = Opcode::Load, .funct3 = Funct3::Lh, .rs1 = 1, .rd = 3}, 0xFFFF8000u);
}

TEST_F(LhTests, LoadsFromBasePlusSignedOffset)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteHalfWord(0x0FFCu, 0x1234u);
    ExecuteExpecting<LH>({.opcode = Opcode::Load, .funct3 = Funct3::Lh, .rs1 = 1, .rd = 3, .imm = static_cast<uint32_t>(-4)}, 0x1234u);
}

TEST_F(LhTests, DiscardsLoadedValueWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteHalfWord(0x1000u, 0x1234u);
    ExecuteExpecting<LH>({.opcode = Opcode::Load, .funct3 = Funct3::Lh, .rs1 = 1, .rd = 0}, 0u);
}
