#include "instruction_fixture.h"

using FenceTests = InstructionTests;

TEST_F(FenceTests, LeavesRegistersAndPCUnchanged)
{
    ExecuteUnchanged<FENCE>({.opcode = Opcode::MiscMem});
}
