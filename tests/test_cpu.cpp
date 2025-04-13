
#include "catch_amalgamated.hpp"
#include "CPU_4004.hpp"
#include "Bus.hpp"
#include "RAMDevice.hpp"
#include "SerialDevice.hpp"
#include <iomanip>

using namespace micromodel;

inline void print_cpu_state(const micromodel::CPU_4004& cpu) {
    std::cout << "\n=== CPU STATE ===\n";

    for (int i = 0; i < 16; ++i) {
        std::cout << "R" << std::hex << std::uppercase << std::setw(1) << i
                  << ": 0x" << std::setw(2) << std::setfill('0')
                  << static_cast<int>(cpu.get_register(i)) << "\n";
    }

    std::cout << "ACC: 0x" << std::setw(2) << std::setfill('0')
              << static_cast<int>(cpu.get_accumulator()) << "\n";

    std::cout << "PC : 0x" << std::setw(3) << std::setfill('0')
              << std::hex << cpu.get_program_counter() << "\n";

    std::cout << "SP : 0x" << std::hex << static_cast<int>(cpu.get_stack_pointer()) << "\n";
    std::cout << "==================\n";
}


TEST_CASE("CPU executes CALL and BBL", "[cpu]") {
    auto bus = std::make_shared<Bus>();
    auto ram = std::make_shared<RAMDevice>(0x0000, 0x0100);
    auto serial = std::make_shared<SerialDevice>(0xF000);
    bus->attach(ram);
    bus->attach(serial);

    std::vector<uint8_t> rom = {
        0x43,       // 0x00: CALL 0x18
        0xFF,       // 0x01: HLT
    
        // Padding to 0x18 (24 bytes total)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    
        // 0x18: subroutine
        0xF0, 0x4A, // LDM R0, 0x4A
        0x90,       // LD R0 → ACC
        0xE8,       // WRR
        0xEA        // BBL 0x0 → Return to 0x01
    };
    

    for (size_t i = 0; i < rom.size(); ++i) {
        ram->write(static_cast<uint16_t>(i), rom[i]);
    }

    CPU_4004 cpu;
    cpu.attach_bus(bus);
    cpu.Start();

    while (cpu.Running()) {
        cpu.step();
    }

    REQUIRE(cpu.get_accumulator() == 0x08);
    print_cpu_state(cpu);
}

