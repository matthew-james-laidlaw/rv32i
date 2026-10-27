#pragma once

#include <format.h>
#include <instruction.h>
#include <memory.h>
#include <registers.h>

#include <cstdint>
#include <memory>

class Core
{
public:

	Memory memory;        // main memory
	Registers registers;  // register file

	auto Run(uint32_t cycles) -> void;
	auto Load(std::vector<uint8_t> program) -> void;

	auto GetMemory() -> Memory&;
	auto GetRegisters() -> Registers&;

private:

	auto Fetch() -> uint32_t;
	auto Decode(uint32_t instruction) -> std::unique_ptr<Instruction>;
	auto Execute(std::unique_ptr<Instruction>& instruction) -> void;

	auto DecodeFormat(uint32_t instruction, uint32_t pc) -> Format;

};
