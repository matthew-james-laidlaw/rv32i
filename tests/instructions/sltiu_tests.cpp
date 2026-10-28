#include "instruction_fixture.h"

using SltiuTests = InstructionTests;

TEST_F(SltiuTests, ComputesResult)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SLTIU>({.opcode = Opcode::I, .funct3 = Funct3::Sltu, .rs1 = 1, .rd = 3, .imm = 2}, 1u);
}

TEST_F(SltiuTests, ComparesUnsignedRegisterAgainstSignExtendedNegativeImmediate)
{
    core.registers.WriteGP(1, 0xFFFFFFFEu);
    ExecuteExpecting<SLTIU>({.opcode = Opcode::I, .funct3 = Funct3::Sltu, .rs1 = 1, .rd = 3, .imm = static_cast<uint32_t>(-1)}, 1u);
}

TEST_F(SltiuTests, ComparesOneAsLessThanSignExtendedNegativeImmediate)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SLTIU>({.opcode = Opcode::I, .funct3 = Funct3::Sltu, .rs1 = 1, .rd = 3, .imm = static_cast<uint32_t>(-1)}, 1u);
}

TEST_F(SltiuTests, ComparesEqualValuesAsNotLessThan)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    ExecuteExpecting<SLTIU>({.opcode = Opcode::I, .funct3 = Funct3::Sltu, .rs1 = 1, .rd = 3, .imm = static_cast<uint32_t>(-1)}, 0u);
}

TEST_F(SltiuTests, ReadsX0AsZero)
{
    ExecuteExpecting<SLTIU>({.opcode = Opcode::I, .funct3 = Funct3::Sltu, .rs1 = 0, .rd = 3, .imm = 1}, 1u);
}

TEST_F(SltiuTests, WritesResultWhenDestinationAliasesSource)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SLTIU>({.opcode = Opcode::I, .funct3 = Funct3::Sltu, .rs1 = 1, .rd = 1, .imm = 2}, 1u);
}

TEST_F(SltiuTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 1);
    ExecuteExpecting<SLTIU>({.opcode = Opcode::I, .funct3 = Funct3::Sltu, .rs1 = 1, .rd = 0, .imm = 2}, 0u);
}
