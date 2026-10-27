#pragma once

#include <format.h>
#include <instruction.h>
#include <memory.h>

#include <cstdint>
#include <memory>

class Core
{
public:

	Memory memory;   // main memory
	uint32_t x[32];  // general purpose registers
	uint32_t pc;     // program counter

	auto Run(uint32_t cycles) -> void;
	auto Load(std::vector<uint8_t> program) -> void;

private:

	auto Fetch() -> uint32_t;
	auto Decode(uint32_t instruction) -> std::unique_ptr<Instruction>;
	auto Execute(std::unique_ptr<Instruction>& instruction) -> void;

	auto DecodeFormat(uint32_t instruction, uint32_t pc) -> Format;

};
