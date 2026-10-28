#include "instruction_fixture.h"

using AuipcTests = InstructionTests;

TEST_F(AuipcTests, AddsUpperImmediateToInstructionAddress)
{
    ExecuteExpecting<AUIPC>({.opcode = Opcode::Auipc, .rd = 3, .imm = 0x1000u, .pc = 0x200u}, 0x1200u);
}

TEST_F(AuipcTests, WrapsOnAddressOverflow)
{
    ExecuteExpecting<AUIPC>({.opcode = Opcode::Auipc, .rd = 3, .imm = 0x1000u, .pc = 0xFFFFF800u}, 0x800u);
}

TEST_F(AuipcTests, WritesResultWhenDestinationIsX0)
{
    ExecuteExpecting<AUIPC>({.opcode = Opcode::Auipc, .rd = 0, .imm = 0x1000u, .pc = 0x200u}, 0u);
}
