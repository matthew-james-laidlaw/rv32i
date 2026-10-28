#include "instruction_fixture.h"

using EcallTests = InstructionTests;

TEST_F(EcallTests, LeavesRegistersAndPCUnchangedInCurrentImplementation)
{
    ExecuteUnchanged<ECALL>({.opcode = Opcode::System});
}
