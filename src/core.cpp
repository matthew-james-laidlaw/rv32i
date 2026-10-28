#include <core.h>
#include <instruction.h>

#include <stdexcept>

auto Core::Step() -> void
{
    auto instruction_word = Fetch();
    if (instruction_word == 0u)
    {
        throw std::runtime_error("Failed to fetch instruction");
    }

    auto instruction = Decode(instruction_word);
    if (!instruction)
    {
        throw std::runtime_error("Failed to decode instruction");
    }

    auto previous_pc = registers.ReadPC();
    Execute(instruction);
    registers.WriteGP(0, 0);
    if (registers.ReadPC() == previous_pc)
    {
        registers.WritePC(previous_pc + 4);
    }
}

auto Core::Run(uint32_t cycles) -> void
{
    for (uint32_t i = 0; i < cycles; ++i)
    {
        Step();
    }
}

auto Core::Load(std::vector<uint8_t> program) -> void
{
    for (size_t i = 0; i < program.size(); ++i)
    {
        memory.WriteByte(i, program[i]);
    }
}

auto Core::GetMemory() -> Memory&
{
    return memory;
}

auto Core::GetRegisters() -> Registers&
{
    return registers;
}

auto Core::Fetch() -> uint32_t
{
    return memory.ReadWord(registers.ReadPC());
}

auto Core::Decode(uint32_t instruction) -> std::unique_ptr<Instruction>
{
    auto fmt = DecodeFormat(instruction, registers.ReadPC());
    switch (fmt.opcode)
    {
        case 0x13: // I-type
            switch (fmt.funct3)
            {
                case 0x0:
                    return std::make_unique<ADDI>(fmt);
                case 0x1:
                    if (fmt.funct7 == 0x00)
                        return std::make_unique<SLLI>(fmt);
                    break;
                case 0x2:
                    return std::make_unique<SLTI>(fmt);
                case 0x3:
                    return std::make_unique<SLTIU>(fmt);
                case 0x4:
                    return std::make_unique<XORI>(fmt);
                case 0x5:
                    if (fmt.funct7 == 0x00)
                        return std::make_unique<SRLI>(fmt);
                    else if (fmt.funct7 == 0x20)
                        return std::make_unique<SRAI>(fmt);
                    break;
                case 0x6:
                    return std::make_unique<ORI>(fmt);
                case 0x7:
                    return std::make_unique<ANDI>(fmt);
            }
            break;
        case 0x17:
            return std::make_unique<AUIPC>(fmt);
        case 0x33: // R-type
            switch (fmt.funct3)
            {
                case 0x0:
                    if (fmt.funct7 == 0x00)
                        return std::make_unique<ADD>(fmt);
                    else if (fmt.funct7 == 0x20)
                        return std::make_unique<SUB>(fmt);
                    break;
                case 0x1:
                    return std::make_unique<SLL>(fmt);
                case 0x2:
                    return std::make_unique<SLT>(fmt);
                case 0x3:
                    return std::make_unique<SLTU>(fmt);
                case 0x4:
                    return std::make_unique<XOR>(fmt);
                case 0x5:
                    if (fmt.funct7 == 0x00)
                        return std::make_unique<SRL>(fmt);
                    else if (fmt.funct7 == 0x20)
                        return std::make_unique<SRA>(fmt);
                    break;
                case 0x6:
                    return std::make_unique<OR>(fmt);
                case 0x7:
                    return std::make_unique<AND>(fmt);
            }
            break;
        case 0x37:
            return std::make_unique<LUI>(fmt);
        case 0x03: // Load instructions
            switch (fmt.funct3)
            {
                case 0x0:
                    return std::make_unique<LB>(fmt);
                case 0x1:
                    return std::make_unique<LH>(fmt);
                case 0x2:
                    return std::make_unique<LW>(fmt);
                case 0x4:
                    return std::make_unique<LBU>(fmt);
                case 0x5:
                    return std::make_unique<LHU>(fmt);
            }
            break;
        case 0x23: // Store instructions
            switch (fmt.funct3)
            {
                case 0x0:
                    return std::make_unique<SB>(fmt);
                case 0x1:
                    return std::make_unique<SH>(fmt);
                case 0x2:
                    return std::make_unique<SW>(fmt);
            }
            break;
        case 0x63: // Branch instructions
            switch (fmt.funct3)
            {
                case 0x0:
                    return std::make_unique<BEQ>(fmt);
                case 0x1:
                    return std::make_unique<BNE>(fmt);
                case 0x4:
                    return std::make_unique<BLT>(fmt);
                case 0x5:
                    return std::make_unique<BGE>(fmt);
                case 0x6:
                    return std::make_unique<BLTU>(fmt);
                case 0x7:
                    return std::make_unique<BGEU>(fmt);
            }
            break;
        case 0x67: // JALR
            if (fmt.funct3 == 0x0)
                return std::make_unique<JALR>(fmt);
            break;
        case 0x6F: // JAL
            return std::make_unique<JAL>(fmt);
        case 0x0F: // FENCE
            return std::make_unique<FENCE>(fmt);
        case 0x73: // SYSTEM
            if (instruction == 0x00000073u)
                return std::make_unique<ECALL>(fmt);
            if (instruction == 0x00100073u)
                return std::make_unique<EBREAK>(fmt);
            break;
    }
    return nullptr;
}

auto Core::Execute(std::unique_ptr<Instruction>& instruction) -> void
{
    instruction->Execute(*this);
}

auto Core::DecodeFormat(uint32_t instruction, uint32_t pc) -> Format
{
    Format fmt{};
    fmt.pc = pc;
    fmt.opcode = instruction & 0x7F;
    fmt.rd = (instruction >> 7) & 0x1F;
    fmt.funct3 = (instruction >> 12) & 0x07;
    fmt.rs1 = (instruction >> 15) & 0x1F;
    fmt.rs2 = (instruction >> 20) & 0x1F;
    fmt.funct7 = (instruction >> 25) & 0x7F;

    switch (fmt.opcode)
    {
        case 0x03:
        case 0x13:
        case 0x67: {
            auto imm = static_cast<uint32_t>((instruction >> 20) & 0xFFFu);
            if ((imm & 0x800u) != 0u)
            {
                imm |= 0xFFFFF000u;
            }
            fmt.imm = imm;
            break;
        }
        case 0x23: {
            auto imm = static_cast<uint32_t>((((instruction >> 25) & 0x7Fu) << 5) | ((instruction >> 7) & 0x1Fu));
            if ((imm & 0x800u) != 0u)
            {
                imm |= 0xFFFFF000u;
            }
            fmt.imm = imm;
            break;
        }
        case 0x63: {
            auto imm = static_cast<uint32_t>(((instruction >> 31) << 12) |
                (((instruction >> 7) & 0x1u) << 11) |
                (((instruction >> 25) & 0x3Fu) << 5) |
                (((instruction >> 8) & 0xFu) << 1));
            if ((imm & 0x1000u) != 0u)
            {
                imm |= 0xFFFFE000u;
            }
            fmt.imm = imm;
            break;
        }
        case 0x6F: {
            auto imm = static_cast<uint32_t>(((instruction >> 31) << 20) |
                (((instruction >> 12) & 0xFFu) << 12) |
                (((instruction >> 20) & 0x1u) << 11) |
                (((instruction >> 21) & 0x3FFu) << 1));
            if ((imm & 0x100000u) != 0u)
            {
                imm |= 0xFFE00000u;
            }
            fmt.imm = imm;
            break;
        }
        case 0x17:
        case 0x37:
            fmt.imm = instruction & 0xFFFFF000u;
            break;
        default:
            fmt.imm = 0;
            break;
    }

    return fmt;
}
