#pragma once

#include <gtest/gtest.h>

#include <core.h>
#include <format.h>
#include <instruction.h>

#include <array>

class InstructionTests : public testing::Test
{
protected:

    // Every register plus the program counter, for before/after comparison.
    struct Snapshot
    {
        std::array<uint32_t, 32> x;
        uint32_t pc;

        auto operator==(Snapshot const&) const -> bool = default;
    };

    Core core;

    // Gives every register a distinct nonzero value (x0 stays zero) so a stray write is detectable.
    auto SetUp() -> void override
    {
        for (uint8_t i = 1; i < 32; ++i)
        {
            core.registers.WriteGP(i, 0x1000u + i);
        }
    }

    auto TakeSnapshot() -> Snapshot
    {
        auto snapshot = Snapshot{};
        for (uint8_t i = 0; i < 32; ++i)
        {
            snapshot.x[i] = core.registers.ReadGP(i);
        }
        snapshot.pc = core.registers.ReadPC();
        return snapshot;
    }

    // Executes instruction T against the fixture's processor core.
    template <typename T>
    auto Execute(Format const& format) -> void
    {
        T(format).Execute(core);
    }

    // Executes instruction T and verifies that format.rd holds `expected` and every other register is unchanged.
    template <typename T>
    auto ExecuteExpecting(Format const& format, uint32_t expected) -> void
    {
        auto expected_state = TakeSnapshot();
        Execute<T>(format);
        expected_state.x[format.rd] = expected;
        EXPECT_TRUE(TakeSnapshot() == expected_state);
    }

};
