#include "SerialDevice.hpp"

namespace micromodel {

    SerialDevice::SerialDevice(uint16_t address)
    : ioAddress(address) {
    std::cout << "[SerialDevice] Constructed\n";
}

SerialDevice::~SerialDevice() {
    std::cout << "[SerialDevice] Destroyed!\n";  // If you see this... yikes
}

bool SerialDevice::handles(uint16_t address) const {
    std::cout << "[SerialDevice] handles? 0x" << std::hex << address << " == 0x" << ioAddress << "\n";
    return address == ioAddress;
}

uint8_t SerialDevice::read(uint16_t) {
    return 0; // Could be expanded later for input
}

void SerialDevice::write(uint16_t, uint8_t value) {
    std::cout << "[Serial] " << static_cast<char>(value) << std::endl;
}

}
