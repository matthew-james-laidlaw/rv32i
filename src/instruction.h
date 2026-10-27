#pragma once

#include <core.h>
#include <format.h>
#include <memory.h>

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

	Instruction(Format const& format)
		: m_format(format)
	{}

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

	ADD(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] + core.x[m_format.rs2];
	}

};

class ADDI : public Instruction
{
public:

	ADDI(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] + m_format.imm;
	}

};

class SUB : public Instruction
{
public:

	SUB(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] - core.x[m_format.rs2];
	}

};

class LUI : public Instruction
{
public:

	LUI(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = m_format.imm;
	}

};

class AUIPC : public Instruction
{
public:

	AUIPC(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = m_format.imm + m_format.pc;
	}

};

/** @par Logical Instructions
 * 
 *  These instructions perform logical operations on the general purpose registers.
 * 
 */

class AND : public Instruction
{
public:

	AND(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] & core.x[m_format.rs2];
	}

};

class ANDI : public Instruction
{
public:

	ANDI(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] & m_format.imm;
	}

};

class OR : public Instruction
{
public:

	OR(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] | core.x[m_format.rs2];
	}

};

class ORI : public Instruction
{
public:

	ORI(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] | m_format.imm;
	}

};

class XOR : public Instruction
{
public:

	XOR(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] ^ core.x[m_format.rs2];
	}

};

class XORI : public Instruction
{
public:

	XORI(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] ^ m_format.imm;
	}

};

/** @par Shift Instructions
 * 
 *  These instructions perform shift operations on the general purpose registers.
 * 
 */

class SLL : public Instruction
{
public:

	SLL(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] << core.x[m_format.rs2];
	}

};

class SLLI : public Instruction
{
public:

	SLLI(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] << m_format.imm;
	}

};

class SRL : public Instruction
{
public:

	SRL(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] >> core.x[m_format.rs2];
	}

};

class SRLI : public Instruction
{
public:

	SRLI(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] >> m_format.imm;
	}

};

class SRA : public Instruction
{
public:

	SRA(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = static_cast<int32_t>(core.x[m_format.rs1]) >> core.x[m_format.rs2];
	}

};

class SRAI : public Instruction
{
public:

	SRAI(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = static_cast<int32_t>(core.x[m_format.rs1]) >> m_format.imm;
	}

};

/** @par Comparison Instructions
 * 
 *  These instructions perform comparison operations on the general purpose registers.
 * 
 */

class SLT : public Instruction
{
public:

	SLT(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = static_cast<int32_t>(core.x[m_format.rs1]) < static_cast<int32_t>(core.x[m_format.rs2]) ? 1 : 0;
	}

};

class SLTI : public Instruction
{
public:

	SLTI(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = static_cast<int32_t>(core.x[m_format.rs1]) < static_cast<int32_t>(m_format.imm) ? 1 : 0;
	}

};

class SLTU : public Instruction
{
public:

	SLTU(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] < core.x[m_format.rs2] ? 1 : 0;
	}

};

class SLTIU : public Instruction
{
public:

	SLTIU(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.x[m_format.rs1] < m_format.imm ? 1 : 0;
	}

};

/** @par Load Instructions
 *
 *  These instructions perform load operations from memory to the general purpose registers.
 *
 */

class LB : public Instruction
{
public:

	LB(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		auto data = core.memory.Read(core.x[m_format.rs1] + m_format.imm, 1);
		auto value = static_cast<uint32_t>(data[0]);
		core.x[m_format.rd] = (value & 0x80u) != 0 ? value | 0xFFFFFF00u : value;
	}

};

class LH : public Instruction
{
public:

	LH(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		auto data = core.memory.Read(core.x[m_format.rs1] + m_format.imm, 2);
		auto value = static_cast<uint32_t>(data[0]) | (static_cast<uint32_t>(data[1]) << 8);
		core.x[m_format.rd] = (value & 0x8000u) != 0 ? value | 0xFFFF0000u : value;
	}

};

class LW : public Instruction
{
public:

	LW(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		auto data = core.memory.Read(core.x[m_format.rs1] + m_format.imm, 4);
		core.x[m_format.rd] = static_cast<uint32_t>(data[0])
			| (static_cast<uint32_t>(data[1]) << 8)
			| (static_cast<uint32_t>(data[2]) << 16)
			| (static_cast<uint32_t>(data[3]) << 24);
	}

};

class LBU : public Instruction
{
public:

	LBU(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		core.x[m_format.rd] = core.memory.Read(core.x[m_format.rs1] + m_format.imm, 1)[0];
	}

};

class LHU : public Instruction
{
public:

	LHU(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		auto data = core.memory.Read(core.x[m_format.rs1] + m_format.imm, 2);
		core.x[m_format.rd] = static_cast<uint32_t>(data[0])
			| (static_cast<uint32_t>(data[1]) << 8);
	}

};

/** @par Store Instructions
 *
 *  These instructions perform store operations from the general purpose registers to memory.
 *
 */

class SB : public Instruction
{
public:

	SB(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		auto value = static_cast<uint8_t>(core.x[m_format.rs2] & 0xFF);
		core.memory.Write(core.x[m_format.rs1] + m_format.imm, {value});
	}

};

class SH : public Instruction
{
public:

	SH(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		auto value = static_cast<uint16_t>(core.x[m_format.rs2] & 0xFFFF);
		core.memory.Write(core.x[m_format.rs1] + m_format.imm, {static_cast<uint8_t>(value & 0xFF), static_cast<uint8_t>((value >> 8) & 0xFF)});
	}

};

class SW : public Instruction
{
public:

	SW(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		auto value = core.x[m_format.rs2];
		core.memory.Write(core.x[m_format.rs1] + m_format.imm, {
			static_cast<uint8_t>(value & 0xFF),
			static_cast<uint8_t>((value >> 8) & 0xFF),
			static_cast<uint8_t>((value >> 16) & 0xFF),
			static_cast<uint8_t>((value >> 24) & 0xFF)
		});
	}

};

/** @par Branch Instructions
 *
 *  These instructions perform branch operations based on the values in the general purpose registers.
 *
 */

class BEQ : public Instruction
{
public:

	BEQ(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		if (core.x[m_format.rs1] == core.x[m_format.rs2])
		{
			core.pc = m_format.pc + m_format.imm;
		}
	}

};

class BNE : public Instruction
{
public:

	BNE(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		if (core.x[m_format.rs1] != core.x[m_format.rs2])
		{
			core.pc = m_format.pc + m_format.imm;
		}
	}

};

class BLT : public Instruction
{
public:

	BLT(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		if (static_cast<int32_t>(core.x[m_format.rs1]) < static_cast<int32_t>(core.x[m_format.rs2]))
		{
			core.pc = m_format.pc + m_format.imm;
		}
	}

};

class BGE : public Instruction
{
public:

	BGE(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		if (static_cast<int32_t>(core.x[m_format.rs1]) >= static_cast<int32_t>(core.x[m_format.rs2]))
		{
			core.pc = m_format.pc + m_format.imm;
		}
	}

};

class BLTU : public Instruction
{
public:

	BLTU(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		if (core.x[m_format.rs1] < core.x[m_format.rs2])
		{
			core.pc = m_format.pc + m_format.imm;
		}
	}

};

class BGEU : public Instruction
{
public:

	BGEU(Format const& format)
		: Instruction(format)
	{}

	auto Execute(Core& core) -> void override
	{
		if (core.x[m_format.rs1] >= core.x[m_format.rs2])
		{
			core.pc = m_format.pc + m_format.imm;
		}
	}

};
