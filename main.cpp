#include "MicroVM.hpp"
#include "RAMDevice.hpp"
#include "BIOSDevice.hpp"
#include "CPU_4004.hpp"
#include "SerialDevice.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>

using namespace micromodel;

int main() {
    MicroVM vm;

    auto ram = std::make_shared<RAMDevice>(0x0100, 0x1200); // 256 bytes
    auto cpu = std::make_shared<CPU_4004>();
    auto serial = std::make_shared<SerialDevice>(0xF000); 

    std::vector<uint8_t> bios_rom = {
        0x43,       // CALL 0x18
        0xFF,       // HLT (after return)
    
        // Subroutine at 0x18:
        0x00, 0x00, 0x00, 0x00, // Padding
        0x00, 0x00, 0x00, 0x00, // Padding
        0xF0, 0x4A,             // 0x18: LDM R0, 0x4A
        0x90,                   //       LD R0 → ACC
        0xE8,                   //       WRR
        0xE0                    //       BBL 0x0 → Return
    };
    
    
    auto bios = std::make_shared<BIOSDevice>(0x0000, bios_rom);
    
    vm.add_device(bios);
    vm.add_device(serial);
    //vm.add_device(ram);
    vm.set_cpu(cpu);
    vm.reset();

    std::cout << "BIOS contents:\n";
    for (size_t i = 0; i < bios_rom.size(); ++i) {
        std::cout << "[" << std::setw(4) << std::setfill('0') << std::hex << i << "] "
                << std::setw(2) << std::hex << (int)bios_rom[i] << "\n";
    }
    
    auto bus = vm.get_bus();
    bus->write(0xF000, 0x41);  // Should go to serial and print 'A'

    std::cout << "Starting VM...\n\n";
    cpu->Start();
    while (cpu->Running()) {
        cpu->step();
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
