#include "CPU_4004.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cassert>

namespace micromodel {

CPU_4004::CPU_4004() {
    reset();
}

void CPU_4004::attach_bus(std::shared_ptr<Bus> systemBus) {
    bus = systemBus;
}

void CPU_4004::reset() {
    pc = 0x000;
    sp = 0;
    acc = 0;
    carry = false;
    registers.fill(0);
    call_stack.fill(0);
    isRunning = false;
}

void CPU_4004::tick() {
    // Not used yet
}

void CPU_4004::step() {
    if (!bus) throw std::runtime_error("CPU not attached to a bus.");
    uint8_t opcode = fetch_byte();
    std::cout << ">>> Fetched opcode: 0x" << std::hex << (int)opcode << " at PC=" << std::hex << (pc - 1) << "\n";
    execute_instruction(opcode);
}

uint8_t CPU_4004::fetch_byte() {
    return bus->read(pc++);
}

void CPU_4004::execute_instruction(uint8_t opcode) {
    std::cout << "Executing opcode: 0x" << std::hex << static_cast<int>(opcode) << "\n";

    if (opcode == 0x00) {
        std::cout << "NOP\n";
        return;
    }

    if (opcode == 0xFF) { // HLT -- fantasy command, the 4004 did not have a HLT function
        Stop();
        isRunning = false;
        std::cout << "HLT - HALT OPERATIONS\n";
        return;
    }

    if ((opcode & 0xF0) == 0x20) {
        uint8_t reg = opcode & 0x0F;
        registers[reg] = (registers[reg] + 1) & 0x0F;
        std::cout << "INC R" << (int)reg << " = " << (int)registers[reg] << "\n";
        return;
    }

    if ((opcode & 0xF0) == 0xF0) {
        uint8_t reg = opcode & 0x0F;
        uint8_t imm = fetch_byte();
        registers[reg] = imm;
        std::cout << "LDM R" << (int)reg << ", 0x" << std::hex << (int)imm << "\n";
        return;
    }

    if ((opcode & 0xF0) == 0xE0) {
        if (sp == 0) throw std::runtime_error("BBL: Stack underflow");
        pc = pop_stack();
        acc = opcode & 0x0F;
        std::cout << "BBL 0x" << std::hex << std::uppercase
                  << static_cast<int>(acc) << " - returning to 0x"
                  << std::setw(3) << std::setfill('0') << pc
                  << std::dec << "\n";
        return;
    }

    // LD Rx → ACC
    if ((opcode & 0xF0) == 0x90) {
        uint8_t r = opcode & 0x0F;
        acc = registers[r];
        std::cout << "LD R" << (int)r << " → ACC = " << (int)acc << "\n";
        return;
    }

    if (opcode == 0xE8) {
        assert(bus != nullptr);
        std::cout << "[CPU] WRR start\n";
    
        if (!bus) {
            std::cerr << "[WRR] Bus is null!\n";
            throw std::runtime_error("WRR: No bus attached");
        }
    
        try {
            bus->write(0xF000, acc);
            std::cout << "[CPU] WRR done: 0xF000 = " << (int)acc << " ('" 
                      << static_cast<char>(acc) << "')\n";
        } catch (const std::exception& ex) {
            std::cerr << "[WRR] Exception during bus write: " << ex.what() << "\n";
        }
    
        return;
    }

    if ((opcode & 0xF0) == 0x40) {
        uint8_t target = opcode & 0x0F;
        uint16_t returnAddr = pc; // Return point is *after* this CALL
        push_stack(returnAddr);
    
        pc = target * 8;
        std::cout << "CALL 0x" << std::hex << (int)(target * 8)
                  << " ← pushed return 0x" << returnAddr << "\n";
        return;
    }
    
    

    
    

    std::ostringstream oss;
    oss << "Unimplemented opcode: 0x" << std::hex << static_cast<int>(opcode);
    throw std::runtime_error(oss.str());
}

// Stack
void CPU_4004::push_stack(uint16_t address) {
    if (sp >= 3) throw std::runtime_error("Stack overflow");
    call_stack[sp++] = address;
}

uint16_t CPU_4004::pop_stack() {
    if (sp == 0) throw std::runtime_error("Stack underflow");
    return call_stack[--sp];
}

// Test/debug access
uint8_t CPU_4004::get_register(uint8_t index) const {
    return registers[index];
}
uint8_t CPU_4004::get_accumulator() const { return acc; }
uint16_t CPU_4004::get_program_counter() const { return pc; }
uint8_t CPU_4004::get_stack_pointer() const { return sp; }

}
