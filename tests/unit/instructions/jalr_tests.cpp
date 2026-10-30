#include "instruction_fixture.h"

using JalrTests = InstructionTests;

TEST_F(JalrTests, JumpsToBasePlusOffsetAndWritesLink)
{
    core.registers.WritePC(0x200u);
    core.registers.WriteGP(1, 0x1000u);
    ExecuteExpectingTransfer<JALR>({.opcode = Opcode::Jalr, .funct3 = 0, .rs1 = 1, .rd = 2, .imm = 4}, 0x204u, 0x1004u);
}

TEST_F(JalrTests, ClearsLeastSignificantBitOfTarget)
{
    core.registers.WriteGP(1, 0x1001u);
    ExecuteExpectingTransfer<JALR>({.opcode = Opcode::Jalr, .funct3 = 0, .rs1 = 1, .rd = 2}, 4u, 0x1000u);
}

TEST_F(JalrTests, SupportsNegativeOffset)
{
    core.registers.WriteGP(1, 0x1000u);
    ExecuteExpectingTransfer<JALR>({.opcode = Opcode::Jalr, .funct3 = 0, .rs1 = 1, .rd = 2, .imm = static_cast<uint32_t>(-4)}, 4u, 0xFFCu);
}

TEST_F(JalrTests, DiscardsLinkWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0x1000u);
    ExecuteExpectingTransfer<JALR>({.opcode = Opcode::Jalr, .funct3 = 0, .rs1 = 1, .rd = 0}, 0u, 0x1000u);
}

TEST_F(JalrTests, ReadsBaseBeforeWritingAliasedDestination)
{
    core.registers.WriteGP(1, 0x1000u);
    ExecuteExpectingTransfer<JALR>({.opcode = Opcode::Jalr, .funct3 = 0, .rs1 = 1, .rd = 1, .imm = 4}, 4u, 0x1004u);
}
