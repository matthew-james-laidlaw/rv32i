#include "instruction_fixture.h"

using LbTests = InstructionTests;

TEST_F(LbTests, SignExtendsPositiveByte)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteByte(0x1000u, 0x7Fu);
    ExecuteExpecting<LB>({.opcode = Opcode::Load, .funct3 = Funct3::Lb, .rs1 = 1, .rd = 3}, 0x7Fu);
}

TEST_F(LbTests, SignExtendsNegativeByte)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteByte(0x1000u, 0x80u);
    ExecuteExpecting<LB>({.opcode = Opcode::Load, .funct3 = Funct3::Lb, .rs1 = 1, .rd = 3}, 0xFFFFFF80u);
}

TEST_F(LbTests, LoadsFromBasePlusSignedOffset)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteByte(0x0FFCu, 0xFFu);
    ExecuteExpecting<LB>({.opcode = Opcode::Load, .funct3 = Funct3::Lb, .rs1 = 1, .rd = 3, .imm = static_cast<uint32_t>(-4)}, 0xFFFFFFFFu);
}

TEST_F(LbTests, DiscardsLoadedValueWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 0x1000u);
    core.memory.WriteByte(0x1000u, 0xFFu);
    ExecuteExpecting<LB>({.opcode = Opcode::Load, .funct3 = Funct3::Lb, .rs1 = 1, .rd = 0}, 0u);
}
