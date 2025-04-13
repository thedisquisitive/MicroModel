#include "MicroVM.hpp"
#include "RAMDevice.hpp"
#include "CPU_4004.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>

using namespace micromodel;

int main() {
    MicroVM vm;

    auto ram = std::make_shared<RAMDevice>(0x0000, 0x0100); // 256 bytes
    auto cpu = std::make_shared<CPU_4004>();

    vm.add_device(ram);
    vm.set_cpu(cpu);

    vm.reset();

    // Simple ROM program
    // F4 0B    → LDM R4, 0xB
    // 20       → INC R0
    // E7       → BBL 0x7 (return to caller)
    std::vector<uint8_t> rom = {
        0xF4, 0x0B, // LDM R4, 0xB
        0x20,       // INC R0
        0xE7        // BBL 0x7
    };

    // Load ROM into memory
    auto bus = vm.get_bus();
    for (size_t i = 0; i < rom.size(); ++i) {
        bus->write(0x0000 + i, rom[i]);
    }

    // Simulate subroutine call so BBL works
    cpu->push_stack(0x0042);

    std::cout << "Starting VM...\n\n";
    for (int i = 0; i < 3; ++i) {
        vm.step();
    }

    std::cout << "\nVM halted.\n";

    // Display register state
    std::cout << "\nFinal CPU State:\n";
    for (int i = 0; i < 16; ++i) {
        std::cout << "R" << std::setw(2) << std::setfill('0') << i << ": "
                  << std::hex << (int)cpu->get_register(i) << "\n";
    }

    std::cout << "ACC: 0x" << std::hex << (int)cpu->get_accumulator() << "\n";
    std::cout << "PC : 0x" << std::hex << cpu->get_program_counter() << "\n";

    return 0;
}
