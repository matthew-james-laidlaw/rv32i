#pragma once

#include <cstdint>

// major opcodes
namespace Opcode
{
	inline constexpr uint8_t B       = 0x63;  // branch (B-type)
	inline constexpr uint8_t I       = 0x13;  // register-immediate (I-type)
	inline constexpr uint8_t J       = 0x6F;  // jump (J-type)
	inline constexpr uint8_t R       = 0x33;  // register-register (R-type)
	inline constexpr uint8_t S       = 0x23;  // store (S-type)
	inline constexpr uint8_t U       = 0x37;  // upper immediate (U-type)

	inline constexpr uint8_t Load    = 0x03;  // lb, lh, lw, lbu, lhu (I-type)
	inline constexpr uint8_t Jalr    = 0x67;  // indirect jump and link (I-type)
	inline constexpr uint8_t Auipc   = 0x17;  // add upper immediate to pc (U-type)
	inline constexpr uint8_t MiscMem = 0x0F;  // fence
	inline constexpr uint8_t System  = 0x73;  // ecall, ebreak
}

// funct3 identifiers
namespace Funct3
{
	// arithmetic and logical operations
	inline constexpr uint8_t AddSub = 0x0;
	inline constexpr uint8_t Sll    = 0x1;
	inline constexpr uint8_t Slt    = 0x2;
	inline constexpr uint8_t Sltu   = 0x3;
	inline constexpr uint8_t Xor    = 0x4;
	inline constexpr uint8_t SrlSra = 0x5;
	inline constexpr uint8_t Or     = 0x6;
	inline constexpr uint8_t And    = 0x7;

	// loads
	inline constexpr uint8_t Lb     = 0x0;
	inline constexpr uint8_t Lh     = 0x1;
	inline constexpr uint8_t Lw     = 0x2;
	inline constexpr uint8_t Lbu    = 0x4;
	inline constexpr uint8_t Lhu    = 0x5;

	// stores
	inline constexpr uint8_t Sb     = 0x0;
	inline constexpr uint8_t Sh     = 0x1;
	inline constexpr uint8_t Sw     = 0x2;

	// branches
	inline constexpr uint8_t Beq    = 0x0;
	inline constexpr uint8_t Bne    = 0x1;
	inline constexpr uint8_t Blt    = 0x4;
	inline constexpr uint8_t Bge    = 0x5;
	inline constexpr uint8_t Bltu   = 0x6;
	inline constexpr uint8_t Bgeu   = 0x7;
}

// funct7 identifiers
namespace Funct7
{
	inline constexpr uint8_t Base        = 0x00;  // ADD, SRL
	inline constexpr uint8_t Alternative = 0x20;  // SUB, SRA
}

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
