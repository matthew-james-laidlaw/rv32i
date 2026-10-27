#pragma once

#include "core.h"
#include "format.h"

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
