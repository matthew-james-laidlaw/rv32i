#include "instruction_fixture.h"

using XorTests = InstructionTests;

TEST_F(XorTests, ComputesResult)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<XOR>({.opcode = Opcode::R, .funct3 = Funct3::Xor, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0b0110u);
}

TEST_F(XorTests, ComputesResultAcrossAll32Bits)
{
    core.registers.WriteGP(1, 0xF0F0F0F0u);
    core.registers.WriteGP(2, 0xFF00FF00u);
    ExecuteExpecting<XOR>({.opcode = Opcode::R, .funct3 = Funct3::Xor, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0x0FF00FF0u);
}

TEST_F(XorTests, AllOnesOperandInvertsOtherOperand)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    core.registers.WriteGP(2, 0xFFFFFFFFu);
    ExecuteExpecting<XOR>({.opcode = Opcode::R, .funct3 = Funct3::Xor, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0x21524110u);
}

TEST_F(XorTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 0xDEADBEEFu);
    ExecuteExpecting<XOR>({.opcode = Opcode::R, .funct3 = Funct3::Xor, .funct7 = Funct7::Base, .rs1 = 0, .rs2 = 2, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(XorTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<XOR>({.opcode = Opcode::R, .funct3 = Funct3::Xor, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 0, .rd = 3}, 0xDEADBEEFu);
}

TEST_F(XorTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<XOR>({.opcode = Opcode::R, .funct3 = Funct3::Xor, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 1}, 0b0110u);
}

TEST_F(XorTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<XOR>({.opcode = Opcode::R, .funct3 = Funct3::Xor, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 2}, 0b0110u);
}

TEST_F(XorTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 0xDEADBEEFu);
    ExecuteExpecting<XOR>({.opcode = Opcode::R, .funct3 = Funct3::Xor, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 1, .rd = 3}, 0u);
}

TEST_F(XorTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    ExecuteExpecting<XOR>({.opcode = Opcode::R, .funct3 = Funct3::Xor, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}
