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
