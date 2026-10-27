#include <gtest/gtest.h>

#include <core.h>
#include <format.h>
#include <instruction.h>

TEST(InstructionTests, ADD)
{
    auto fmt_add = Format{
        .opcode = 0x33,
        .funct3 = 0,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 2,
        .rd = 3,
        .imm = 0,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 1;
    core.x[2] = 2;
    auto* instr = new ADD(fmt_add);
    instr->Execute(core);
    EXPECT_EQ(core.x[3], 3);
}

TEST(InstructionTests, ADDI)
{
    auto fmt_addi = Format{
        .opcode = 0x13,
        .funct3 = 0,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 0,
        .rd = 3,
        .imm = 2,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 1;
    auto instr = ADDI(fmt_addi);
    instr.Execute(core);
    EXPECT_EQ(core.x[3], 3);
}

TEST(InstructionTests, SUB)
{
    auto fmt_sub = Format{
        .opcode = 0x33,
        .funct3 = 0,
        .funct7 = 0x20,
        .rs1 = 1,
        .rs2 = 2,
        .rd = 3,
        .imm = 0,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 3;
    core.x[2] = 2;
    auto* instr = new SUB(fmt_sub);
    instr->Execute(core);
    EXPECT_EQ(core.x[3], 1);
}

TEST(InstructionTests, LUI)
{
    auto fmt_lui = Format{
        .opcode = 0x37,
        .funct3 = 0,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 0,
        .rd = 3,
        .imm = 0x12345000,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 3;
    auto instr = LUI(fmt_lui);
    instr.Execute(core);
    EXPECT_EQ(core.x[3], 0x12345000);
}

TEST(InstructionTests, AUIPC)
{
    auto fmt_auipc = Format{
        .opcode = 0x17,
        .funct3 = 0,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 0,
        .rd = 3,
        .imm = 0x1000,
        .pc = 0x200
    };

    auto core = Core();
    auto instr = AUIPC(fmt_auipc);
    instr.Execute(core);
    EXPECT_EQ(core.x[3], 0x1200);
}
