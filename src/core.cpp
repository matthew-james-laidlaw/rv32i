#include <core.h>
#include <instruction.h>

auto Core::Run(uint32_t cycles) -> void
{
    for (uint32_t i = 0; i < cycles; ++i)
    {
        auto bytes = Fetch();
        auto instruction = Decode(bytes);
        Execute(instruction);
    }
}

auto Core::Load(std::vector<uint8_t> program) -> void
{
    for (size_t i = 0; i < program.size(); ++i)
    {
        memory.WriteByte(i, program[i]);
    }
}

auto Core::Fetch() -> uint32_t
{
    return memory.ReadWord(pc);
}

auto Core::Decode(uint32_t instruction) -> std::unique_ptr<Instruction>
{
    auto fmt = DecodeFormat(instruction, pc);
    switch (fmt.opcode)
    {
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
        case 0x13: // I-type
            switch (fmt.funct3)
            {
                case 0x0:
                    return std::make_unique<ADDI>(fmt);
                case 0x2:
                    return std::make_unique<SLTI>(fmt);
                case 0x3:
                    return std::make_unique<SLTIU>(fmt);
                case 0x4:
                    return std::make_unique<XORI>(fmt);
                case 0x6:
                    return std::make_unique<ORI>(fmt);
                case 0x7:
                    return std::make_unique<ANDI>(fmt);
            }
            break;
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
    }
    return nullptr;
}

auto Core::Execute(std::unique_ptr<Instruction>& instruction) -> void
{
    instruction->Execute(*this);
}

auto Core::DecodeFormat(uint32_t instruction, uint32_t pc) -> Format
{
    Format fmt;
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
            fmt.imm = static_cast<int32_t>(static_cast<int16_t>((instruction >> 20) & 0xFFF));
            break;
        case 0x23:
            fmt.imm = static_cast<int32_t>(static_cast<int16_t>(((instruction >> 25) << 5) | ((instruction >> 7) & 0x1F)));
            break;
        default:
            fmt.imm = 0;
            break;
    }

    return fmt;
}
