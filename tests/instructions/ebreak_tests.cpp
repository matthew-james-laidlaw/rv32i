#include "instruction_fixture.h"

using EbreakTests = InstructionTests;

TEST_F(EbreakTests, LeavesRegistersAndPCUnchangedInCurrentImplementation)
{
    ExecuteUnchanged<EBREAK>({.opcode = Opcode::System, .imm = 1});
}
