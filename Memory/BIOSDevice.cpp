#include "BIOSDevice.hpp"
#include <stdexcept>

namespace micromodel {

BIOSDevice::BIOSDevice(uint16_t baseAddress, const std::vector<uint8_t>& data)
    : base(baseAddress), rom(data) {}

bool BIOSDevice::handles(uint16_t address) const {
    return address >= base && address < base + rom.size();
}

uint8_t BIOSDevice::read(uint16_t address) {
    if (!handles(address)) throw std::out_of_range("BIOS read out of bounds");
    return rom[address - base];
}

}
