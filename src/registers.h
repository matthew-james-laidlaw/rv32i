#pragma once

#include <cstdint>

class Registers
{
private:

	uint32_t x[32]{};  // general purpose registers
	uint32_t pc{};     // program counter

public:

	auto ReadGP(uint8_t index) -> uint32_t;
	auto WriteGP(uint8_t index, uint32_t value) -> void;

	auto ReadPC() -> uint32_t;
	auto WritePC(uint32_t value) -> void;

};
