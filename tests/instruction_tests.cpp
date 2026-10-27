#include <gtest/gtest.h>

#include <core.h>
#include <format.h>
#include <instruction.h>
#include <memory.h>

#include <array>

class InstructionTests : public testing::Test
{
protected:

    // Every register plus the program counter, for before/after comparison.
    struct Snapshot
    {
        std::array<uint32_t, 32> x;
        uint32_t pc;

        auto operator==(Snapshot const&) const -> bool = default;
    };

    Core core;

    // Gives every register a distinct nonzero value (x0 stays zero) so a stray write is detectable.
    auto SetUp() -> void override
    {
        for (uint8_t i = 1; i < 32; ++i)
        {
            core.registers.WriteGP(i, 0x1000u + i);
        }
    }

    auto TakeSnapshot() -> Snapshot
    {
        auto snapshot = Snapshot{};
        for (uint8_t i = 0; i < 32; ++i)
        {
            snapshot.x[i] = core.registers.ReadGP(i);
        }
        snapshot.pc = core.registers.ReadPC();
        return snapshot;
    }

    // Executes instruction T against the fixture's processor core.
    template <typename T>
    auto Execute(Format const& format) -> void
    {
        T(format).Execute(core);
    }

    // Executes instruction T and verifies that format.rd holds `expected` and every other register is unchanged.
    template <typename T>
    auto ExecuteExpecting(Format const& format, uint32_t expected) -> void
    {
        auto expected_state = TakeSnapshot();
        Execute<T>(format);
        expected_state.x[format.rd] = expected;
        EXPECT_TRUE(TakeSnapshot() == expected_state);
    }

};

/* All tests share the same fixture, but each
 * instruction gets its own test suite name. */

using AddTests = InstructionTests;
using SubTests = InstructionTests;

TEST_F(AddTests, ComputesResult)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 3u);
}

TEST_F(AddTests, ComputesResultForNegativeOperands)
{
    core.registers.WriteGP(1, static_cast<uint32_t>(-1));
    core.registers.WriteGP(2, static_cast<uint32_t>(-2));
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, static_cast<uint32_t>(-3));
}

TEST_F(AddTests, ComputesResultForMixedSignOperands)
{
    core.registers.WriteGP(1, 5);
    core.registers.WriteGP(2, static_cast<uint32_t>(-3));
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 2u);
}

TEST_F(AddTests, WrapsOnUnsignedOverflow)
{
    core.registers.WriteGP(1, 0xFFFFFFFFu);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0u);
}

TEST_F(AddTests, WrapsOnSignedOverflow)
{
    core.registers.WriteGP(1, 0x7FFFFFFFu);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3}, 0x80000000u);
}

TEST_F(AddTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 7);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 0, .rs2 = 2, .rd = 3}, 7u);
}

TEST_F(AddTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 9);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 0, .rd = 3}, 9u);
}

TEST_F(AddTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 4);
    core.registers.WriteGP(2, 6);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 1}, 10u);
}

TEST_F(AddTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 4);
    core.registers.WriteGP(2, 6);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 2}, 10u);
}

TEST_F(AddTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 0x80000001u);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 1, .rd = 3}, 2u);
}

TEST_F(AddTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 4);
    core.registers.WriteGP(2, 6);
    ExecuteExpecting<ADD>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}

TEST_F(SubTests, ComputesResult)
{
    core.registers.WriteGP(1, 3);
    core.registers.WriteGP(2, 2);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 1u);
}

TEST_F(SubTests, ComputesResultForNegativeOperands)
{
    core.registers.WriteGP(1, static_cast<uint32_t>(-1));
    core.registers.WriteGP(2, static_cast<uint32_t>(-2));
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 1u);
}

TEST_F(SubTests, ComputesResultForMixedSignOperands)
{
    core.registers.WriteGP(1, 5);
    core.registers.WriteGP(2, static_cast<uint32_t>(-3));
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 8u);
}

TEST_F(SubTests, WrapsOnUnsignedOverflow)
{
    core.registers.WriteGP(1, 0);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 0xFFFFFFFFu);
}

TEST_F(SubTests, WrapsOnSignedOverflow)
{
    core.registers.WriteGP(1, 0x80000000u);
    core.registers.WriteGP(2, 1);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3}, 0x7FFFFFFFu);
}

TEST_F(SubTests, ReadsX0AsZeroForFirstSource)
{
    core.registers.WriteGP(2, 7);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 0, .rs2 = 2, .rd = 3}, static_cast<uint32_t>(-7));
}

TEST_F(SubTests, ReadsX0AsZeroForSecondSource)
{
    core.registers.WriteGP(1, 9);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 0, .rd = 3}, 9u);
}

TEST_F(SubTests, WritesResultWhenDestinationAliasesFirstSource)
{
    core.registers.WriteGP(1, 10);
    core.registers.WriteGP(2, 4);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 1}, 6u);
}

TEST_F(SubTests, WritesResultWhenDestinationAliasesSecondSource)
{
    core.registers.WriteGP(1, 10);
    core.registers.WriteGP(2, 4);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 2}, 6u);
}

TEST_F(SubTests, ReadsSameRegisterForBothSources)
{
    core.registers.WriteGP(1, 0x80000001u);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 1, .rd = 3}, 0u);
}

TEST_F(SubTests, DiscardsResultWhenDestinationIsX0)
{
    core.registers.WriteGP(1, 6);
    core.registers.WriteGP(2, 4);
    ExecuteExpecting<SUB>({.opcode = Opcode::R, .funct3 = Funct3::AddSub, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 0}, 0u);
}

TEST_F(InstructionTests, AND)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    Execute<AND>({.opcode = Opcode::R, .funct3 = Funct3::And, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 0b1000u);
}

TEST_F(InstructionTests, OR)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    Execute<OR>({.opcode = Opcode::R, .funct3 = Funct3::Or, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 0b1110u);
}

TEST_F(InstructionTests, XOR)
{
    core.registers.WriteGP(1, 0b1100);
    core.registers.WriteGP(2, 0b1010);
    Execute<XOR>({.opcode = Opcode::R, .funct3 = Funct3::Xor, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 0b0110u);
}

TEST_F(InstructionTests, SLL)
{
    core.registers.WriteGP(1, 0b0001);
    core.registers.WriteGP(2, 2);
    Execute<SLL>({.opcode = Opcode::R, .funct3 = Funct3::Sll, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 0b0100u);
}

TEST_F(InstructionTests, SRL)
{
    core.registers.WriteGP(1, 0b0100);
    core.registers.WriteGP(2, 2);
    Execute<SRL>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 0b0001u);
}

TEST_F(InstructionTests, SRA)
{
    core.registers.WriteGP(1, 0xFFFFFFFCu);
    core.registers.WriteGP(2, 2);
    Execute<SRA>({.opcode = Opcode::R, .funct3 = Funct3::SrlSra, .funct7 = Funct7::Alternative, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 0xFFFFFFFFu);
}

TEST_F(InstructionTests, SLT)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 2);
    Execute<SLT>({.opcode = Opcode::R, .funct3 = Funct3::Slt, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 1u);
}

TEST_F(InstructionTests, SLTU)
{
    core.registers.WriteGP(1, 1);
    core.registers.WriteGP(2, 2);
    Execute<SLTU>({.opcode = Opcode::R, .funct3 = Funct3::Sltu, .funct7 = Funct7::Base, .rs1 = 1, .rs2 = 2, .rd = 3});
    EXPECT_EQ(core.registers.ReadGP(3), 1u);
}

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
