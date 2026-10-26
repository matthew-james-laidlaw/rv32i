#include "instruction.h"

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

auto main() -> int
{
	return 0;
}
