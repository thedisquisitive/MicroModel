#pragma once
#include "ICPUDevice.hpp"
#include "Bus.hpp"
#include <array>
#include <memory>
#include <cstdint>

namespace micromodel {

class CPU_4004 : public ICPUDevice {
public:
    CPU_4004();

    void attach_bus(std::shared_ptr<Bus> bus) override;
    void step() override;
    void tick() override;
    void reset() override;

    // Helpers for testing/debug
    uint8_t get_register(uint8_t index) const;
    uint8_t get_accumulator() const;
    uint16_t get_program_counter() const;
    uint8_t get_stack_pointer() const;

    void push_stack(uint16_t address);
    uint16_t pop_stack();

    uint8_t fetch_byte();
    void execute_instruction(uint8_t opcode);

private:
    std::shared_ptr<Bus> bus;

    std::array<uint8_t, 16> registers = {};
    std::array<uint16_t, 3> call_stack = {};
    uint8_t sp = 0;

    uint8_t acc = 0;
    bool carry = false;

    uint16_t pc = 0;

    
};

}
