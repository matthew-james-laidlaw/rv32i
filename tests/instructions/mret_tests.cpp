#include "instruction_fixture.h"

using MretTests = InstructionTests;

TEST_F(MretTests, JumpsToMepc)
{
    core.csrs.Write(Csr::Mepc, 0x1234);
    ExecuteExpectingPC<MRET>({.opcode = Opcode::System, .imm = 0x302}, 0x1234);
}
