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

TEST(InstructionTests, AND)
{
    auto fmt_and = Format{
        .opcode = 0x33,
        .funct3 = 7,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 2,
        .rd = 3,
        .imm = 0,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0b1100;
    core.x[2] = 0b1010;
    auto* instr = new AND(fmt_and);
    instr->Execute(core);
    EXPECT_EQ(core.x[3], 0b1000);
}

TEST(InstructionTests, ANDI)
{
    auto fmt_andi = Format{
        .opcode = 0x13,
        .funct3 = 7,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 0,
        .rd = 3,
        .imm = 0b1010,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0b1100;
    auto instr = ANDI(fmt_andi);
    instr.Execute(core);
    EXPECT_EQ(core.x[3], 0b1000);
}

TEST(InstructionTests, OR)
{
    auto fmt_or = Format{
        .opcode = 0x33,
        .funct3 = 6,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 2,
        .rd = 3,
        .imm = 0,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0b1100;
    core.x[2] = 0b1010;
    auto* instr = new OR(fmt_or);
    instr->Execute(core);
    EXPECT_EQ(core.x[3], 0b1110);
}

TEST(InstructionTests, ORI)
{
    auto fmt_ori = Format{
        .opcode = 0x13,
        .funct3 = 6,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 0,
        .rd = 3,
        .imm = 0b1010,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0b1100;
    auto instr = ORI(fmt_ori);
    instr.Execute(core);
    EXPECT_EQ(core.x[3], 0b1110);
}

TEST(InstructionTests, XOR)
{
    auto fmt_xor = Format{
        .opcode = 0x33,
        .funct3 = 4,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 2,
        .rd = 3,
        .imm = 0,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0b1100;
    core.x[2] = 0b1010;
    auto* instr = new XOR(fmt_xor);
    instr->Execute(core);
    EXPECT_EQ(core.x[3], 0b0110);
}

TEST(InstructionTests, XORI)
{
    auto fmt_xori = Format{
        .opcode = 0x13,
        .funct3 = 4,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 0,
        .rd = 3,
        .imm = 0b1010,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0b1100;
    auto instr = XORI(fmt_xori);
    instr.Execute(core);
    EXPECT_EQ(core.x[3], 0b0110);
}

TEST(InstructionTests, SLL)
{
    auto fmt_sll = Format{
        .opcode = 0x33,
        .funct3 = 1,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 2,
        .rd = 3,
        .imm = 0,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0b0001;
    core.x[2] = 2;
    auto* instr = new SLL(fmt_sll);
    instr->Execute(core);
    EXPECT_EQ(core.x[3], 0b0100);
}

TEST(InstructionTests, SLLI)
{
    auto fmt_slli = Format{
        .opcode = 0x13,
        .funct3 = 1,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 0,
        .rd = 3,
        .imm = 2,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0b0001;
    auto instr = SLLI(fmt_slli);
    instr.Execute(core);
    EXPECT_EQ(core.x[3], 0b0100);
}

TEST(InstructionTests, SRL)
{
    auto fmt_srl = Format{
        .opcode = 0x33,
        .funct3 = 5,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 2,
        .rd = 3,
        .imm = 0,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0b0100;
    core.x[2] = 2;
    auto* instr = new SRL(fmt_srl);
    instr->Execute(core);
    EXPECT_EQ(core.x[3], 0b0001);
}

TEST(InstructionTests, SRLI)
{
    auto fmt_srli = Format{
        .opcode = 0x13,
        .funct3 = 5,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 0,
        .rd = 3,
        .imm = 2,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0b0100;
    auto instr = SRLI(fmt_srli);
    instr.Execute(core);
    EXPECT_EQ(core.x[3], 0b0001);
}

TEST(InstructionTests, SRA)
{
    auto fmt_sra = Format{
        .opcode = 0x33,
        .funct3 = 5,
        .funct7 = 0x20,
        .rs1 = 1,
        .rs2 = 2,
        .rd = 3,
        .imm = 0,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0xFFFFFFFCu;
    core.x[2] = 2;
    auto* instr = new SRA(fmt_sra);
    instr->Execute(core);
    EXPECT_EQ(core.x[3], 0xFFFFFFFFu);
}

TEST(InstructionTests, SRAI)
{
    auto fmt_srai = Format{
        .opcode = 0x13,
        .funct3 = 5,
        .funct7 = 0x20,
        .rs1 = 1,
        .rs2 = 0,
        .rd = 3,
        .imm = 2,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 0xFFFFFFFCu;
    auto instr = SRAI(fmt_srai);
    instr.Execute(core);
    EXPECT_EQ(core.x[3], 0xFFFFFFFFu);
}

TEST(InstructionTests, SLT)
{
    auto fmt_slt = Format{
        .opcode = 0x33,
        .funct3 = 2,
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
    auto* instr = new SLT(fmt_slt);
    instr->Execute(core);
    EXPECT_EQ(core.x[3], 1);
}

TEST(InstructionTests, SLTI)
{
    auto fmt_slti = Format{
        .opcode = 0x13,
        .funct3 = 2,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 0,
        .rd = 3,
        .imm = 2,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 1;
    auto instr = SLTI(fmt_slti);
    instr.Execute(core);
    EXPECT_EQ(core.x[3], 1);
}

TEST(InstructionTests, SLTU)
{
    auto fmt_sltu = Format{
        .opcode = 0x33,
        .funct3 = 3,
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
    auto* instr = new SLTU(fmt_sltu);
    instr->Execute(core);
    EXPECT_EQ(core.x[3], 1);
}

TEST(InstructionTests, SLTIU)
{
    auto fmt_sltiu = Format{
        .opcode = 0x13,
        .funct3 = 3,
        .funct7 = 0,
        .rs1 = 1,
        .rs2 = 0,
        .rd = 3,
        .imm = 2,
        .pc = 0
    };

    auto core = Core();
    core.x[1] = 1;
    auto instr = SLTIU(fmt_sltiu);
    instr.Execute(core);
    EXPECT_EQ(core.x[3], 1);
}
