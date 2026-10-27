#pragma once

#include <memory.h>

#include <cstdint>

struct Core
{
	Memory memory;   // main memory
	uint32_t x[32];  // general purpose registers
};
