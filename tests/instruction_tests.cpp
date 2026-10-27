#include <gtest/gtest.h>

#include <core.h>
#include <format.h>
#include <instruction.h>
#include <memory.h>

class InstructionTests : public testing::Test
{
protected:

    Core core;

    // Executes instruction T against the fixture's processor core.
    template <typename T>
    auto Execute(Format const& format) -> void
    {
        T(format).Execute(core);
    }

};

TEST_F(InstructionTests, ADD)
{
    core.x[1] = 1;
    core.x[2] = 2;
    Execute<ADD>({.opcode = 0x33, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.x[3], 3u);
}

TEST_F(InstructionTests, SUB)
{
    core.x[1] = 3;
    core.x[2] = 2;
    Execute<SUB>({.opcode = 0x33, .funct7 = 0x20, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.x[3], 1u);
}

TEST_F(InstructionTests, AND)
{
    core.x[1] = 0b1100;
    core.x[2] = 0b1010;
    Execute<AND>({.opcode = 0x33, .funct3 = 7, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.x[3], 0b1000u);
}

TEST_F(InstructionTests, OR)
{
    core.x[1] = 0b1100;
    core.x[2] = 0b1010;
    Execute<OR>({.opcode = 0x33, .funct3 = 6, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.x[3], 0b1110u);
}

TEST_F(InstructionTests, XOR)
{
    core.x[1] = 0b1100;
    core.x[2] = 0b1010;
    Execute<XOR>({.opcode = 0x33, .funct3 = 4, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.x[3], 0b0110u);
}

TEST_F(InstructionTests, SLL)
{
    core.x[1] = 0b0001;
    core.x[2] = 2;
    Execute<SLL>({.opcode = 0x33, .funct3 = 1, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.x[3], 0b0100u);
}

TEST_F(InstructionTests, SRL)
{
    core.x[1] = 0b0100;
    core.x[2] = 2;
    Execute<SRL>({.opcode = 0x33, .funct3 = 5, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.x[3], 0b0001u);
}

TEST_F(InstructionTests, SRA)
{
    core.x[1] = 0xFFFFFFFCu;
    core.x[2] = 2;
    Execute<SRA>({.opcode = 0x33, .funct3 = 5, .funct7 = 0x20, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.x[3], 0xFFFFFFFFu);
}

TEST_F(InstructionTests, SLT)
{
    core.x[1] = 1;
    core.x[2] = 2;
    Execute<SLT>({.opcode = 0x33, .funct3 = 2, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.x[3], 1u);
}

TEST_F(InstructionTests, SLTU)
{
    core.x[1] = 1;
    core.x[2] = 2;
    Execute<SLTU>({.opcode = 0x33, .funct3 = 3, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.x[3], 1u);
}

TEST_F(InstructionTests, ADDI)
{
    core.x[1] = 1;
    Execute<ADDI>({.opcode = 0x13, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.x[3], 3u);
}

TEST_F(InstructionTests, ANDI)
{
    core.x[1] = 0b1100;
    Execute<ANDI>({.opcode = 0x13, .funct3 = 7, .rs1 = 1, .rd = 3, .imm = 0b1010});
    EXPECT_EQ(core.x[3], 0b1000u);
}

TEST_F(InstructionTests, ORI)
{
    core.x[1] = 0b1100;
    Execute<ORI>({.opcode = 0x13, .funct3 = 6, .rs1 = 1, .rd = 3, .imm = 0b1010});
    EXPECT_EQ(core.x[3], 0b1110u);
}

TEST_F(InstructionTests, XORI)
{
    core.x[1] = 0b1100;
    Execute<XORI>({.opcode = 0x13, .funct3 = 4, .rs1 = 1, .rd = 3, .imm = 0b1010});
    EXPECT_EQ(core.x[3], 0b0110u);
}

TEST_F(InstructionTests, SLLI)
{
    core.x[1] = 0b0001;
    Execute<SLLI>({.opcode = 0x13, .funct3 = 1, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.x[3], 0b0100u);
}

TEST_F(InstructionTests, SRLI)
{
    core.x[1] = 0b0100;
    Execute<SRLI>({.opcode = 0x13, .funct3 = 5, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.x[3], 0b0001u);
}

TEST_F(InstructionTests, SRAI)
{
    core.x[1] = 0xFFFFFFFCu;
    Execute<SRAI>({.opcode = 0x13, .funct3 = 5, .funct7 = 0x20, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.x[3], 0xFFFFFFFFu);
}

TEST_F(InstructionTests, SLTI)
{
    core.x[1] = 1;
    Execute<SLTI>({.opcode = 0x13, .funct3 = 2, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.x[3], 1u);
}

TEST_F(InstructionTests, SLTIU)
{
    core.x[1] = 1;
    Execute<SLTIU>({.opcode = 0x13, .funct3 = 3, .rs1 = 1, .rd = 3, .imm = 2});
    EXPECT_EQ(core.x[3], 1u);
}

TEST_F(InstructionTests, LUI)
{
    Execute<LUI>({.opcode = 0x37, .rd = 3, .imm = 0x12345000});
    EXPECT_EQ(core.x[3], 0x12345000u);
}

TEST_F(InstructionTests, AUIPC)
{
    Execute<AUIPC>({.opcode = 0x17, .rd = 3, .imm = 0x1000, .pc = 0x200});
    EXPECT_EQ(core.x[3], 0x1200u);
}

TEST_F(InstructionTests, LB)
{
    core.x[1] = 0x1000;
    core.memory.WriteByte(0x1000, 0xFF);
    Execute<LB>({.opcode = 0x03, .rs1 = 1, .rd = 3});
    EXPECT_EQ(core.x[3], 0xFFFFFFFFu);
}

TEST_F(InstructionTests, LH)
{
    core.x[1] = 0x1000;
    core.memory.WriteHalfWord(0x1000, 0x1234);
    Execute<LH>({.opcode = 0x03, .funct3 = 1, .rs1 = 1, .rd = 3});
    EXPECT_EQ(core.x[3], 0x1234u);
}

TEST_F(InstructionTests, LW)
{
    core.x[1] = 0x1000;
    core.memory.WriteWord(0x1000, 0x12345678);
    Execute<LW>({.opcode = 0x03, .funct3 = 2, .rs1 = 1, .rd = 3});
    EXPECT_EQ(core.x[3], 0x12345678u);
}

TEST_F(InstructionTests, LBU)
{
    core.x[1] = 0x1000;
    core.memory.WriteByte(0x1000, 0xFF);
    Execute<LBU>({.opcode = 0x03, .funct3 = 4, .rs1 = 1, .rd = 3});
    EXPECT_EQ(core.x[3], 0xFFu);
}

TEST_F(InstructionTests, LHU)
{
    core.x[1] = 0x1000;
    core.memory.WriteHalfWord(0x1000, 0x1234);
    Execute<LHU>({.opcode = 0x03, .funct3 = 5, .rs1 = 1, .rd = 3});
    EXPECT_EQ(core.x[3], 0x1234u);
}

TEST_F(InstructionTests, SB)
{
    core.x[1] = 0x1000;
    core.x[2] = 0xAB;
    Execute<SB>({.opcode = 0x23, .rs1 = 1, .rs2 = 2});
    EXPECT_EQ(core.memory.ReadByte(0x1000), 0xABu);
}

TEST_F(InstructionTests, SH)
{
    core.x[1] = 0x1000;
    core.x[2] = 0x1234;
    Execute<SH>({.opcode = 0x23, .funct3 = 1, .rs1 = 1, .rs2 = 2});
    EXPECT_EQ(core.memory.ReadHalfWord(0x1000), 0x1234u);
}

TEST_F(InstructionTests, SW)
{
    core.x[1] = 0x1000;
    core.x[2] = 0x12345678;
    Execute<SW>({.opcode = 0x23, .funct3 = 2, .rs1 = 1, .rs2 = 2});
    EXPECT_EQ(core.memory.ReadWord(0x1000), 0x12345678u);
}

TEST_F(InstructionTests, BEQ)
{
    core.x[1] = 5;
    core.x[2] = 5;
    Execute<BEQ>({.opcode = 0x63, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.pc, 4u);
}

TEST_F(InstructionTests, BNE)
{
    core.x[1] = 5;
    core.x[2] = 6;
    Execute<BNE>({.opcode = 0x63, .funct3 = 1, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.pc, 4u);
}

TEST_F(InstructionTests, BLT)
{
    core.x[1] = 5;
    core.x[2] = 6;
    Execute<BLT>({.opcode = 0x63, .funct3 = 4, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.pc, 4u);
}

TEST_F(InstructionTests, BGE)
{
    core.x[1] = 6;
    core.x[2] = 5;
    Execute<BGE>({.opcode = 0x63, .funct3 = 5, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.pc, 4u);
}

TEST_F(InstructionTests, BLTU)
{
    core.x[1] = 5;
    core.x[2] = 6;
    Execute<BLTU>({.opcode = 0x63, .funct3 = 6, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.pc, 4u);
}

TEST_F(InstructionTests, BGEU)
{
    core.x[1] = 6;
    core.x[2] = 5;
    Execute<BGEU>({.opcode = 0x63, .funct3 = 7, .rs1 = 1, .rs2 = 2, .imm = 4});
    EXPECT_EQ(core.pc, 4u);
}

TEST_F(InstructionTests, JAL)
{
    Execute<JAL>({.opcode = 0x6F, .rd = 1, .imm = 4});
    EXPECT_EQ(core.pc, 4u);
    EXPECT_EQ(core.x[1], 4u);
}

TEST_F(InstructionTests, JALR)
{
    core.x[1] = 0x1000;
    Execute<JALR>({.opcode = 0x67, .rs1 = 1, .rd = 2, .imm = 4});
    EXPECT_EQ(core.pc, 0x1004u);
    EXPECT_EQ(core.x[2], 4u);
}

TEST_F(InstructionTests, FENCE)
{
    Execute<FENCE>({.opcode = 0x0F});
}

TEST_F(InstructionTests, ECALL)
{
    Execute<ECALL>({.opcode = 0x73});
}

TEST_F(InstructionTests, EBREAK)
{
    Execute<EBREAK>({.opcode = 0x73, .funct7 = 1});
}
