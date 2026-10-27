#pragma once

#include "core.h"
#include "format.h"

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
