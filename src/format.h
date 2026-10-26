#pragma once

#include <cstdint>

struct Format
{
	uint8_t  opcode;  // partially identifies the instruction
	uint8_t  funct3;  // further identifies the instruction
	uint8_t  funct7;  // further identifies the instruction
	uint8_t  rs1;     // input register one
	uint8_t  rs2;     // input register two
	uint8_t  rd;      // destination register
	uint32_t imm;     // a literal value
	uint32_t pc;      // the instruction's address
};
