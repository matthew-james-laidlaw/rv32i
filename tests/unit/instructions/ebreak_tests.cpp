#include "instruction_fixture.h"

using EbreakTests = InstructionTests;

TEST_F(EbreakTests, TrapsToMtvecRecordingPcAndCause)
{
    core.registers.WritePC(0x100);
    core.csrs.Write(Csr::Mtvec, 0x2000);

    auto expected_state = TakeSnapshot();
    Execute<EBREAK>({.opcode = Opcode::System, .imm = 1});
    expected_state.pc = 0x2000;

    EXPECT_TRUE(TakeSnapshot() == expected_state);
    EXPECT_EQ(core.csrs.Read(Csr::Mepc), 0x100u);
    EXPECT_EQ(core.csrs.Read(Csr::Mcause), TrapCause::Breakpoint);
}
