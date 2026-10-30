#include "instruction_fixture.h"

using SltiTests = InstructionTests;

TEST_F(SltiTests, ComputesResult)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SLTI>({.opcode = Opcode::I, .funct3 = Funct3::Slt, .rs1 = 1, .rd = 3, .imm = 2}, 1u);
}

TEST_F(SltiTests, ComparesNegativeRegisterValueAsLessThanPositiveImmediate)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    ExecuteExpecting<SLTI>({.opcode = Opcode::I, .funct3 = Funct3::Slt, .rs1 = 1, .rd = 3, .imm = 1}, 1u);
}

TEST_F(SltiTests, ComparesPositiveRegisterValueAsNotLessThanNegativeImmediate)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SLTI>({.opcode = Opcode::I, .funct3 = Funct3::Slt, .rs1 = 1, .rd = 3, .imm = static_cast<uint32_t>(-1)}, 0u);
}

TEST_F(SltiTests, ComparesEqualValuesAsNotLessThan)
{
    core.registers.WriteGP(1, 0x80000000u);
    ExecuteExpecting<SLTI>({.opcode = Opcode::I, .funct3 = Funct3::Slt, .rs1 = 1, .rd = 3, .imm = 0x80000000u}, 0u);
}

TEST_F(SltiTests, ReadsX0AsZero)
{
    ExecuteExpecting<SLTI>({.opcode = Opcode::I, .funct3 = Funct3::Slt, .rs1 = 0, .rd = 3, .imm = 1}, 1u);
}

TEST_F(SltiTests, WritesResultWhenDestinationAliasesSource)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    ExecuteExpecting<SLTI>({.opcode = Opcode::I, .funct3 = Funct3::Slt, .rs1 = 1, .rd = 1, .imm = 1}, 1u);
}

TEST_F(SltiTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    ExecuteExpecting<SLTI>({.opcode = Opcode::I, .funct3 = Funct3::Slt, .rs1 = 1, .rd = 0, .imm = 1}, 0u);
}
