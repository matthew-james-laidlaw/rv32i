#pragma once

#include <cstdint>

namespace ABI
{
	static constexpr uint8_t ZERO = 0;
	static constexpr uint8_t RA = 1;  // return address
	static constexpr uint8_t SP = 2;  // stack pointer
	static constexpr uint8_t GP = 3;  // global pointer
	static constexpr uint8_t TP = 4;  // thread pointer
	static constexpr uint8_t T0 = 5;  // temporary register 0
	static constexpr uint8_t T1 = 6;  // temporary register 1
	static constexpr uint8_t T2 = 7;  // temporary register 2
	static constexpr uint8_t S0 = 8;  // saved register 0
	static constexpr uint8_t S1 = 9;  // saved register 1
	static constexpr uint8_t A0 = 10; // function argument 0
	static constexpr uint8_t A1 = 11; // function argument 1
	static constexpr uint8_t A2 = 12; // function argument 2
	static constexpr uint8_t A3 = 13; // function argument 3
	static constexpr uint8_t A4 = 14; // function argument 4
	static constexpr uint8_t A5 = 15; // function argument 5
	static constexpr uint8_t A6 = 16; // function argument 6
	static constexpr uint8_t A7 = 17; // function argument 7
	static constexpr uint8_t S2 = 18; // saved register 2
	static constexpr uint8_t S3 = 19; // saved register 3
	static constexpr uint8_t S4 = 20; // saved register 4
	static constexpr uint8_t S5 = 21; // saved register 5
	static constexpr uint8_t S6 = 22; // saved register 6
	static constexpr uint8_t S7 = 23; // saved register 7
	static constexpr uint8_t S8 = 24; // saved register 8
	static constexpr uint8_t S9 = 25; // saved register 9
	static constexpr uint8_t S10 = 26; // saved register 10
	static constexpr uint8_t S11 = 27; // saved register 11
	static constexpr uint8_t T3 = 28; // temporary register 3
	static constexpr uint8_t T4 = 29; // temporary register 4
	static constexpr uint8_t T5 = 30; // temporary register 5
	static constexpr uint8_t T6 = 31; // temporary register 6
}

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
