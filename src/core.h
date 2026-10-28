#pragma once

#include <csrs.h>
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
	Csrs csrs;            // control and status registers

	Core(size_t memory_size = 0x10000);

	auto Step() -> void;
	auto Run(uint32_t cycles) -> void;

	auto Load(std::vector<uint8_t> const& program, size_t offset = 0) -> void;

	auto GetMemory() -> Memory&;
	auto GetRegisters() -> Registers&;

private:

	auto Fetch() -> uint32_t;
	auto Decode(uint32_t instruction) -> std::unique_ptr<Instruction>;
	auto Execute(std::unique_ptr<Instruction>& instruction) -> void;

	auto DecodeFormat(uint32_t instruction, uint32_t pc) -> Format;

};
