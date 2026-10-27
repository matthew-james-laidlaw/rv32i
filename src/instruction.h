#pragma once

#include <format.h>

class Core;

/** @par Instruction
 *
 *  The Instruction class is the base class for all instructions.
 *
 */

class Instruction
{
protected:

    Format m_format;

public:

    explicit Instruction(Format const& format);

    virtual auto Execute(Core& core) -> void = 0;
    virtual ~Instruction() = default;

};

/** @par Arithmetic Instructions
 *
 *  These instructions perform arithmetic operations on the general purpose registers.
 *
 */

class ADD : public Instruction
{
public:
    explicit ADD(Format const& format);
    auto Execute(Core& core) -> void override;
};

class ADDI : public Instruction
{
public:
    explicit ADDI(Format const& format);
    auto Execute(Core& core) -> void override;
};

class SUB : public Instruction
{
public:
    explicit SUB(Format const& format);
    auto Execute(Core& core) -> void override;
};

class LUI : public Instruction
{
public:
    explicit LUI(Format const& format);
    auto Execute(Core& core) -> void override;
};

class AUIPC : public Instruction
{
public:
    explicit AUIPC(Format const& format);
    auto Execute(Core& core) -> void override;
};

/** @par Logical Instructions
 *
 *  These instructions perform logical operations on the general purpose registers.
 *
 */

class AND : public Instruction
{
public:
    explicit AND(Format const& format);
    auto Execute(Core& core) -> void override;
};

class ANDI : public Instruction
{
public:
    explicit ANDI(Format const& format);
    auto Execute(Core& core) -> void override;
};

class OR : public Instruction
{
public:
    explicit OR(Format const& format);
    auto Execute(Core& core) -> void override;
};

class ORI : public Instruction
{
public:
    explicit ORI(Format const& format);
    auto Execute(Core& core) -> void override;
};

class XOR : public Instruction
{
public:
    explicit XOR(Format const& format);
    auto Execute(Core& core) -> void override;
};

class XORI : public Instruction
{
public:
    explicit XORI(Format const& format);
    auto Execute(Core& core) -> void override;
};

/** @par Shift Instructions
 *
 *  These instructions perform shift operations on the general purpose registers.
 *
 */

class SLL : public Instruction
{
public:
    explicit SLL(Format const& format);
    auto Execute(Core& core) -> void override;
};

class SLLI : public Instruction
{
public:
    explicit SLLI(Format const& format);
    auto Execute(Core& core) -> void override;
};

class SRL : public Instruction
{
public:
    explicit SRL(Format const& format);
    auto Execute(Core& core) -> void override;
};

class SRLI : public Instruction
{
public:
    explicit SRLI(Format const& format);
    auto Execute(Core& core) -> void override;
};

class SRA : public Instruction
{
public:
    explicit SRA(Format const& format);
    auto Execute(Core& core) -> void override;
};

class SRAI : public Instruction
{
public:
    explicit SRAI(Format const& format);
    auto Execute(Core& core) -> void override;
};

/** @par Comparison Instructions
 *
 *  These instructions perform comparison operations on the general purpose registers.
 *
 */

class SLT : public Instruction
{
public:
    explicit SLT(Format const& format);
    auto Execute(Core& core) -> void override;
};

class SLTI : public Instruction
{
public:
    explicit SLTI(Format const& format);
    auto Execute(Core& core) -> void override;
};

class SLTU : public Instruction
{
public:
    explicit SLTU(Format const& format);
    auto Execute(Core& core) -> void override;
};

class SLTIU : public Instruction
{
public:
    explicit SLTIU(Format const& format);
    auto Execute(Core& core) -> void override;
};

/** @par Load Instructions
 *
 *  These instructions perform load operations from memory to the general purpose registers.
 *
 */

class LB : public Instruction
{
public:
    explicit LB(Format const& format);
    auto Execute(Core& core) -> void override;
};

class LH : public Instruction
{
public:
    explicit LH(Format const& format);
    auto Execute(Core& core) -> void override;
};

class LW : public Instruction
{
public:
    explicit LW(Format const& format);
    auto Execute(Core& core) -> void override;
};

class LBU : public Instruction
{
public:
    explicit LBU(Format const& format);
    auto Execute(Core& core) -> void override;
};

class LHU : public Instruction
{
public:
    explicit LHU(Format const& format);
    auto Execute(Core& core) -> void override;
};

/** @par Store Instructions
 *
 *  These instructions perform store operations from the general purpose registers to memory.
 *
 */

class SB : public Instruction
{
public:
    explicit SB(Format const& format);
    auto Execute(Core& core) -> void override;
};

class SH : public Instruction
{
public:
    explicit SH(Format const& format);
    auto Execute(Core& core) -> void override;
};

class SW : public Instruction
{
public:
    explicit SW(Format const& format);
    auto Execute(Core& core) -> void override;
};

/** @par Branch Instructions
 *
 *  These instructions perform branch operations based on the values in the general purpose registers.
 *
 */

class BEQ : public Instruction
{
public:
    explicit BEQ(Format const& format);
    auto Execute(Core& core) -> void override;
};

class BNE : public Instruction
{
public:
    explicit BNE(Format const& format);
    auto Execute(Core& core) -> void override;
};

class BLT : public Instruction
{
public:
    explicit BLT(Format const& format);
    auto Execute(Core& core) -> void override;
};

class BGE : public Instruction
{
public:
    explicit BGE(Format const& format);
    auto Execute(Core& core) -> void override;
};

class BLTU : public Instruction
{
public:
    explicit BLTU(Format const& format);
    auto Execute(Core& core) -> void override;
};

class BGEU : public Instruction
{
public:
    explicit BGEU(Format const& format);
    auto Execute(Core& core) -> void override;
};

/** @par Jump Instructions
 *
 *  These instructions perform jump operations, altering the program counter based on the instruction's immediate value.
 *
 */

class JAL : public Instruction
{
public:
    explicit JAL(Format const& format);
    auto Execute(Core& core) -> void override;
};

class JALR : public Instruction
{
public:
    explicit JALR(Format const& format);
    auto Execute(Core& core) -> void override;
};

/** @par Memory Ordering Instructions
 *
 *  These instructions are used for synchronizing memory operations.
 *
 */

class FENCE : public Instruction
{
public:
    explicit FENCE(Format const& format);
    auto Execute(Core& core) -> void override;
};

/** @par System Instructions
 *
 *  These instructions are used for operating system and environment calls. They are used to request services from the operating system or to perform specific system-level operations.
 *
 */

class ECALL : public Instruction
{
public:
    explicit ECALL(Format const& format);
    auto Execute(Core& core) -> void override;
};

class EBREAK : public Instruction
{
public:
    explicit EBREAK(Format const& format);
    auto Execute(Core& core) -> void override;
};
