#include "instruction_fixture.h"

#include <memory.h>

TEST_F(InstructionTests, ADDI)
{
    core.registers.WriteGP(1, 1);
    Execute<ADDI>({.opcode = Opcode::I, .funct3 = Funct3::AddSub, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.registers.ReadGP(3), 3u);
}

TEST_F(InstructionTests, ANDI)
{
    core.registers.WriteGP(1, 0b1100);
    Execute<ANDI>({.opcode = Opcode::I, .funct3 = Funct3::And, .rs1 = 1, .rd = 3, .imm = 0b1010});
    EXPECT_EQ(core.registers.ReadGP(3), 0b1000u);
}

TEST_F(InstructionTests, ORI)
{
    core.registers.WriteGP(1, 0b1100);
    Execute<ORI>({.opcode = Opcode::I, .funct3 = Funct3::Or, .rs1 = 1, .rd = 3, .imm = 0b1010});
    EXPECT_EQ(core.registers.ReadGP(3), 0b1110u);
}

TEST_F(InstructionTests, XORI)
{
    core.registers.WriteGP(1, 0b1100);
    Execute<XORI>({.opcode = Opcode::I, .funct3 = Funct3::Xor, .rs1 = 1, .rd = 3, .imm = 0b1010});
    EXPECT_EQ(core.registers.ReadGP(3), 0b0110u);
}

TEST_F(InstructionTests, SLLI)
{
    core.registers.WriteGP(1, 0b0001);
    Execute<SLLI>({.opcode = Opcode::I, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.registers.ReadGP(3), 0b0100u);
}

TEST_F(InstructionTests, SRLI)
{
    core.registers.WriteGP(1, 0b0100);
    Execute<SRLI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.registers.ReadGP(3), 0b0001u);
}

TEST_F(InstructionTests, SRAI)
{
    core.registers.WriteGP(1, 0xFFFFFFFCu);
    Execute<SRAI>({.opcode = Opcode::I, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.registers.ReadGP(3), 0xFFFFFFFFu);
}

TEST_F(InstructionTests, SLTI)
{
    core.registers.WriteGP(1, 1);
    Execute<SLTI>({.opcode = Opcode::I, .funct3 = Funct3::Slt, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.registers.ReadGP(3), 1u);
}

TEST_F(InstructionTests, SLTIU)
{
    core.registers.WriteGP(1, 1);
    Execute<SLTIU>({.opcode = Opcode::I, .funct3 = Funct3::Sltu, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.registers.ReadGP(3), 1u);
}

TEST_F(InstructionTests, LUI)
{
    Execute<LUI>({.opcode = Opcode::U, .rd = 3, .imm = 0x12345000});
    EXPECT_EQ(core.registers.ReadGP(3), 0x12345000u);
}

TEST_F(InstructionTests, AUIPC)
{
    Execute<AUIPC>({.opcode = Opcode::Auipc, .rd = 3, .imm = 0x1000, .pc = 0x200});
    EXPECT_EQ(core.registers.ReadGP(3), 0x1200u);
}

TEST_F(InstructionTests, LB)
{
    core.registers.WriteGP(1, 0x1000);
    core.memory.WriteByte(0x1000, 0xFF);
    Execute<LB>({.opcode = Opcode::Load, .funct3 = Funct3::Lb, .rs1 = 1, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 0xFFFFFFFFu);
}

TEST_F(InstructionTests, LH)
{
    core.registers.WriteGP(1, 0x1000);
    core.memory.WriteHalfWord(0x1000, 0x1234);
    Execute<LH>({.opcode = Opcode::Load, .funct3 = Funct3::Lh, .rs1 = 1, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 0x1234u);
}

TEST_F(InstructionTests, LW)
{
    core.registers.WriteGP(1, 0x1000);
    core.memory.WriteWord(0x1000, 0x12345678);
    Execute<LW>({.opcode = Opcode::Load, .funct3 = Funct3::Lw, .rs1 = 1, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 0x12345678u);
}

TEST_F(InstructionTests, LBU)
{
    core.registers.WriteGP(1, 0x1000);
    core.memory.WriteByte(0x1000, 0xFF);
    Execute<LBU>({.opcode = Opcode::Load, .funct3 = Funct3::Lbu, .rs1 = 1, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 0xFFu);
}

TEST_F(InstructionTests, LHU)
{
    core.registers.WriteGP(1, 0x1000);
    core.memory.WriteHalfWord(0x1000, 0x1234);
    Execute<LHU>({.opcode = Opcode::Load, .funct3 = Funct3::Lhu, .rs1 = 1, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 0x1234u);
}

TEST_F(InstructionTests, SB)
{
    core.registers.WriteGP(1, 0x1000);
    core.registers.WriteGP(2, 0xAB);
    Execute<SB>({.opcode = Opcode::S, .funct3 = Funct3::Sb, .rs1 = 1, .rs2 = 2});
    EXPECT_EQ(core.memory.ReadByte(0x1000), 0xABu);
}

TEST_F(InstructionTests, SH)
{
    core.registers.WriteGP(1, 0x1000);
    core.registers.WriteGP(2, 0x1234);
    Execute<SH>({.opcode = Opcode::S, .funct3 = Funct3::Sh, .rs1 = 1, .rs2 = 2});
    EXPECT_EQ(core.memory.ReadHalfWord(0x1000), 0x1234u);
}

TEST_F(InstructionTests, SW)
{
    core.registers.WriteGP(1, 0x1000);
    core.registers.WriteGP(2, 0x12345678);
    Execute<SW>({.opcode = Opcode::S, .funct3 = Funct3::Sw, .rs1 = 1, .rs2 = 2});
    EXPECT_EQ(core.memory.ReadWord(0x1000), 0x12345678u);
}

TEST_F(InstructionTests, BEQ)
{
    core.registers.WriteGP(1, 5);
    core.registers.WriteGP(2, 5);
    Execute<BEQ>({.opcode = Opcode::B, .funct3 = Funct3::Beq, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.registers.ReadPC(), 4u);
}

TEST_F(InstructionTests, BNE)
{
    core.registers.WriteGP(1, 5);
    core.registers.WriteGP(2, 6);
    Execute<BNE>({.opcode = Opcode::B, .funct3 = Funct3::Bne, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.registers.ReadPC(), 4u);
}

TEST_F(InstructionTests, BLT)
{
    core.registers.WriteGP(1, 5);
    core.registers.WriteGP(2, 6);
    Execute<BLT>({.opcode = Opcode::B, .funct3 = Funct3::Blt, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.registers.ReadPC(), 4u);
}

TEST_F(InstructionTests, BGE)
{
    core.registers.WriteGP(1, 6);
    core.registers.WriteGP(2, 5);
    Execute<BGE>({.opcode = Opcode::B, .funct3 = Funct3::Bge, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.registers.ReadPC(), 4u);
}

TEST_F(InstructionTests, BLTU)
{
    core.registers.WriteGP(1, 5);
    core.registers.WriteGP(2, 6);
    Execute<BLTU>({.opcode = Opcode::B, .funct3 = Funct3::Bltu, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.registers.ReadPC(), 4u);
}

TEST_F(InstructionTests, BGEU)
{
    core.registers.WriteGP(1, 6);
    core.registers.WriteGP(2, 5);
    Execute<BGEU>({.opcode = Opcode::B, .funct3 = Funct3::Bgeu, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.registers.ReadPC(), 4u);
}

TEST_F(InstructionTests, JAL_SetsPC)
{
    Execute<JAL>({.opcode = Opcode::J, .rd = 1, .imm = 4});
    EXPECT_EQ(core.registers.ReadPC(), 4u);
}

TEST_F(InstructionTests, JAL_WritesLinkRegister)
{
    Execute<JAL>({.opcode = Opcode::J, .rd = 1, .imm = 4});
    EXPECT_EQ(core.registers.ReadGP(1), 4u);
}

TEST_F(InstructionTests, JALR_SetsPC)
{
    core.registers.WriteGP(1, 0x1000);
    Execute<JALR>({.opcode = Opcode::Jalr, .rs1 = 1, .rd = 2, .imm = 4});
    EXPECT_EQ(core.registers.ReadPC(), 0x1004u);
}

TEST_F(InstructionTests, JALR_WritesLinkRegister)
{
    core.registers.WriteGP(1, 0x1000);
    Execute<JALR>({.opcode = Opcode::Jalr, .rs1 = 1, .rd = 2, .imm = 4});
    EXPECT_EQ(core.registers.ReadGP(2), 4u);
}

TEST_F(InstructionTests, FENCE)
{
    Execute<FENCE>({.opcode = Opcode::MiscMem});
}

TEST_F(InstructionTests, ECALL)
{
    Execute<ECALL>({.opcode = Opcode::System});
}

TEST_F(InstructionTests, EBREAK)
{
    Execute<EBREAK>({.opcode = Opcode::System, .imm = 1});
}
