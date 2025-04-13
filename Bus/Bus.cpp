#include "Bus.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace micromodel {

void Bus::attach(std::shared_ptr<IBusDevice> device) {
    devices.push_back(device);
}

uint8_t Bus::read(uint16_t address) {
    for (const auto& device : devices) {
        if (device->handles(address)) {
            
            return device->read(address);
        }
    }
    std::ostringstream oss;
    oss << "Bus read error at 0x" << std::hex << address;
    throw std::runtime_error(oss.str());
}

void Bus::write(uint16_t address, uint8_t value) {
    std::cout << "[BUS] Write: checking " << devices.size() << " devices\n";

    for (const auto& device : devices) {
        if (device->handles(address)) {
            std::cout << "[BUS] Write to 0x" << std::hex << address << " = " << (int)value << "\n";
            device->write(address, value);
            return;
        }
    }

    std::cerr << "[BUS] Write failure at 0x" << std::hex << address << " = " << (int)value << "\n";
    throw std::runtime_error("No device handled bus write.");
}


}
