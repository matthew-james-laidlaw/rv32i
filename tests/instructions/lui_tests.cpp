#include "instruction_fixture.h"

using LuiTests = InstructionTests;

TEST_F(LuiTests, WritesUpperImmediate)
{
    ExecuteExpecting<LUI>({.opcode = Opcode::U, .rd = 3, .imm = 0x12345000u}, 0x12345000u);
}

TEST_F(LuiTests, WritesImmediateWithSignBitSet)
{
    ExecuteExpecting<LUI>({.opcode = Opcode::U, .rd = 3, .imm = 0xFFFFF000u}, 0xFFFFF000u);
}

TEST_F(LuiTests, WritesResultWhenDestinationIsX0)
{
    ExecuteExpecting<LUI>({.opcode = Opcode::U, .rd = 0, .imm = 0x12345000u}, 0u);
}
