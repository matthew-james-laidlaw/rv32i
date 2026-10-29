#include "instruction_fixture.h"

using EcallTests = InstructionTests;

TEST_F(EcallTests, TrapsToMtvecRecordingPcAndCause)
{
    core.registers.WritePC(0x100);
    core.csrs.Write(Csr::Mtvec, 0x2000);

    auto expected_state = TakeSnapshot();
    Execute<ECALL>({.opcode = Opcode::System});
    expected_state.pc = 0x2000;

    EXPECT_TRUE(TakeSnapshot() == expected_state);
    EXPECT_EQ(core.csrs.Read(Csr::Mepc), 0x100u);
    EXPECT_EQ(core.csrs.Read(Csr::Mcause), TrapCause::EcallFromMMode);
}
