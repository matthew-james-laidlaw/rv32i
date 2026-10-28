#include "instruction_fixture.h"

using JalTests = InstructionTests;

TEST_F(JalTests, JumpsToPCPlusOffset)
{
    ExecuteExpectingTransfer<JAL>({.opcode = Opcode::J, .rd = 1, .imm = 12, .pc = 0x100u}, 0x104u, 0x10Cu);
}

TEST_F(JalTests, JumpsWithNegativeOffset)
{
    ExecuteExpectingTransfer<JAL>({.opcode = Opcode::J, .rd = 1, .imm = static_cast<uint32_t>(-8), .pc = 0x100u}, 0x104u, 0xF8u);
}

TEST_F(JalTests, DiscardsLinkWhenDestinationIsX0)
{
    ExecuteExpectingTransfer<JAL>({.opcode = Opcode::J, .rd = 0, .imm = 12, .pc = 0x100u}, 0u, 0x10Cu);
}
