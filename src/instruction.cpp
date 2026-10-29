#include <core.h>
#include <instruction.h>

Instruction::Instruction(Format const& format)
    : m_format(format)
{}

ADD::ADD(Format const& format)
    : Instruction(format)
{}

auto ADD::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) + core.registers.ReadGP(m_format.rs2));
}

ADDI::ADDI(Format const& format)
    : Instruction(format)
{}

auto ADDI::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) + m_format.imm);
}

SUB::SUB(Format const& format)
    : Instruction(format)
{}

auto SUB::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) - core.registers.ReadGP(m_format.rs2));
}

LUI::LUI(Format const& format)
    : Instruction(format)
{}

auto LUI::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, m_format.imm);
}

AUIPC::AUIPC(Format const& format)
    : Instruction(format)
{}

auto AUIPC::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, m_format.imm + m_format.pc);
}

AND::AND(Format const& format)
    : Instruction(format)
{}

auto AND::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) & core.registers.ReadGP(m_format.rs2));
}

ANDI::ANDI(Format const& format)
    : Instruction(format)
{}

auto ANDI::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) & m_format.imm);
}

OR::OR(Format const& format)
    : Instruction(format)
{}

auto OR::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) | core.registers.ReadGP(m_format.rs2));
}

ORI::ORI(Format const& format)
    : Instruction(format)
{}

auto ORI::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) | m_format.imm);
}

XOR::XOR(Format const& format)
    : Instruction(format)
{}

auto XOR::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) ^ core.registers.ReadGP(m_format.rs2));
}

XORI::XORI(Format const& format)
    : Instruction(format)
{}

auto XORI::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) ^ m_format.imm);
}

SLL::SLL(Format const& format)
    : Instruction(format)
{}

auto SLL::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) << (core.registers.ReadGP(m_format.rs2) & 0x1Fu));
}

SLLI::SLLI(Format const& format)
    : Instruction(format)
{}

auto SLLI::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) << m_format.imm);
}

SRL::SRL(Format const& format)
    : Instruction(format)
{}

auto SRL::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) >> (core.registers.ReadGP(m_format.rs2) & 0x1Fu));
}

SRLI::SRLI(Format const& format)
    : Instruction(format)
{}

auto SRLI::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) >> m_format.imm);
}

SRA::SRA(Format const& format)
    : Instruction(format)
{}

auto SRA::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, static_cast<int32_t>(core.registers.ReadGP(m_format.rs1)) >> (core.registers.ReadGP(m_format.rs2) & 0x1Fu));
}

SRAI::SRAI(Format const& format)
    : Instruction(format)
{}

auto SRAI::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, static_cast<int32_t>(core.registers.ReadGP(m_format.rs1)) >> m_format.imm);
}

SLT::SLT(Format const& format)
    : Instruction(format)
{}

auto SLT::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, static_cast<int32_t>(core.registers.ReadGP(m_format.rs1)) < static_cast<int32_t>(core.registers.ReadGP(m_format.rs2)) ? 1 : 0);
}

SLTI::SLTI(Format const& format)
    : Instruction(format)
{}

auto SLTI::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, static_cast<int32_t>(core.registers.ReadGP(m_format.rs1)) < static_cast<int32_t>(m_format.imm) ? 1 : 0);
}

SLTU::SLTU(Format const& format)
    : Instruction(format)
{}

auto SLTU::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) < core.registers.ReadGP(m_format.rs2) ? 1 : 0);
}

SLTIU::SLTIU(Format const& format)
    : Instruction(format)
{}

auto SLTIU::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.registers.ReadGP(m_format.rs1) < m_format.imm ? 1 : 0);
}

LB::LB(Format const& format)
    : Instruction(format)
{}

auto LB::Execute(Core& core) -> void
{
    auto value = core.memory.ReadByte(core.registers.ReadGP(m_format.rs1) + m_format.imm);
    core.registers.WriteGP(m_format.rd, (value & 0x80u) != 0 ? value | 0xFFFFFF00u : value);
}

LH::LH(Format const& format)
    : Instruction(format)
{}

auto LH::Execute(Core& core) -> void
{
    auto value = core.memory.ReadHalfWord(core.registers.ReadGP(m_format.rs1) + m_format.imm);
    core.registers.WriteGP(m_format.rd, (value & 0x8000u) != 0 ? value | 0xFFFF0000u : value);
}

LW::LW(Format const& format)
    : Instruction(format)
{}

auto LW::Execute(Core& core) -> void
{
    auto data = core.memory.ReadWord(core.registers.ReadGP(m_format.rs1) + m_format.imm);
    core.registers.WriteGP(m_format.rd, data);
}

LBU::LBU(Format const& format)
    : Instruction(format)
{}

auto LBU::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, core.memory.ReadByte(core.registers.ReadGP(m_format.rs1) + m_format.imm));
}

LHU::LHU(Format const& format)
    : Instruction(format)
{}

auto LHU::Execute(Core& core) -> void
{
    auto value = core.memory.ReadHalfWord(core.registers.ReadGP(m_format.rs1) + m_format.imm);
    core.registers.WriteGP(m_format.rd, static_cast<uint32_t>(value));
}

SB::SB(Format const& format)
    : Instruction(format)
{}

auto SB::Execute(Core& core) -> void
{
    auto value = static_cast<uint8_t>(core.registers.ReadGP(m_format.rs2) & 0xFF);
    core.memory.WriteByte(core.registers.ReadGP(m_format.rs1) + m_format.imm, value);
}

SH::SH(Format const& format)
    : Instruction(format)
{}

auto SH::Execute(Core& core) -> void
{
    auto value = static_cast<uint16_t>(core.registers.ReadGP(m_format.rs2) & 0xFFFF);
    core.memory.WriteHalfWord(core.registers.ReadGP(m_format.rs1) + m_format.imm, value);
}

SW::SW(Format const& format)
    : Instruction(format)
{}

auto SW::Execute(Core& core) -> void
{
    auto value = core.registers.ReadGP(m_format.rs2);
    core.memory.WriteWord(core.registers.ReadGP(m_format.rs1) + m_format.imm, value);
}

BEQ::BEQ(Format const& format)
    : Instruction(format)
{}

auto BEQ::Execute(Core& core) -> void
{
    if (core.registers.ReadGP(m_format.rs1) == core.registers.ReadGP(m_format.rs2))
    {
        core.registers.WritePC(m_format.pc + m_format.imm);
    }
}

BNE::BNE(Format const& format)
    : Instruction(format)
{}

auto BNE::Execute(Core& core) -> void
{
    if (core.registers.ReadGP(m_format.rs1) != core.registers.ReadGP(m_format.rs2))
    {
        core.registers.WritePC(m_format.pc + m_format.imm);
    }
}

BLT::BLT(Format const& format)
    : Instruction(format)
{}

auto BLT::Execute(Core& core) -> void
{
    if (static_cast<int32_t>(core.registers.ReadGP(m_format.rs1)) < static_cast<int32_t>(core.registers.ReadGP(m_format.rs2)))
    {
        core.registers.WritePC(m_format.pc + m_format.imm);
    }
}

BGE::BGE(Format const& format)
    : Instruction(format)
{}

auto BGE::Execute(Core& core) -> void
{
    if (static_cast<int32_t>(core.registers.ReadGP(m_format.rs1)) >= static_cast<int32_t>(core.registers.ReadGP(m_format.rs2)))
    {
        core.registers.WritePC(m_format.pc + m_format.imm);
    }
}

BLTU::BLTU(Format const& format)
    : Instruction(format)
{}

auto BLTU::Execute(Core& core) -> void
{
    if (core.registers.ReadGP(m_format.rs1) < core.registers.ReadGP(m_format.rs2))
    {
        core.registers.WritePC(m_format.pc + m_format.imm);
    }
}

BGEU::BGEU(Format const& format)
    : Instruction(format)
{}

auto BGEU::Execute(Core& core) -> void
{
    if (core.registers.ReadGP(m_format.rs1) >= core.registers.ReadGP(m_format.rs2))
    {
        core.registers.WritePC(m_format.pc + m_format.imm);
    }
}

JAL::JAL(Format const& format)
    : Instruction(format)
{}

auto JAL::Execute(Core& core) -> void
{
    core.registers.WriteGP(m_format.rd, m_format.pc + 4);
    core.registers.WritePC(m_format.pc + m_format.imm);
}

JALR::JALR(Format const& format)
    : Instruction(format)
{}

auto JALR::Execute(Core& core) -> void
{
    auto temp = core.registers.ReadPC() + 4;
    core.registers.WritePC((core.registers.ReadGP(m_format.rs1) + m_format.imm) & ~1u);
    core.registers.WriteGP(m_format.rd, temp);
}

FENCE::FENCE(Format const& format)
    : Instruction(format)
{}

auto FENCE::Execute(Core& core) -> void
{
    // not implemented, no-op
}

ECALL::ECALL(Format const& format)
    : Instruction(format)
{}

// Enters the machine-mode trap handler: records the faulting pc and cause, then jumps to mtvec.
static auto TakeTrap(Core& core, uint32_t cause) -> void
{
    core.csrs.Write(Csr::Mepc, core.registers.ReadPC());
    core.csrs.Write(Csr::Mcause, cause);
    core.registers.WritePC(core.csrs.Read(Csr::Mtvec));
}

auto ECALL::Execute(Core& core) -> void
{
    TakeTrap(core, TrapCause::EcallFromMMode);
}

EBREAK::EBREAK(Format const& format)
    : Instruction(format)
{}

auto EBREAK::Execute(Core& core) -> void
{
    TakeTrap(core, TrapCause::Breakpoint);
}

MRET::MRET(Format const& format)
    : Instruction(format)
{}

auto MRET::Execute(Core& core) -> void
{
    core.registers.WritePC(core.csrs.Read(Csr::Mepc));
}

CSRRW::CSRRW(Format const& format)
    : Instruction(format)
{}

auto CSRRW::Execute(Core& core) -> void
{
    auto old_value = core.csrs.Read(m_format.imm);
    if (m_format.rs1 != 0)
    {
        core.csrs.Write(m_format.imm, core.registers.ReadGP(m_format.rs1));
    }
    core.registers.WriteGP(m_format.rd, old_value);
}

CSRRS::CSRRS(Format const& format)
    : Instruction(format)
{}

auto CSRRS::Execute(Core& core) -> void
{
    auto old_value = core.csrs.Read(m_format.imm);
    if (m_format.rs1 != 0)
    {
        core.csrs.Write(m_format.imm, old_value | core.registers.ReadGP(m_format.rs1));
    }
    core.registers.WriteGP(m_format.rd, old_value);
}

CSRRWI::CSRRWI(Format const& format)
    : Instruction(format)
{}

auto CSRRWI::Execute(Core& core) -> void
{
    auto old_value = core.csrs.Read(m_format.imm);
    core.csrs.Write(m_format.imm, m_format.rs1);
    core.registers.WriteGP(m_format.rd, old_value);
}
