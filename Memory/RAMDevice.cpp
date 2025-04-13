#include "RAMDevice.hpp"
#include <stdexcept>

namespace micromodel {

RAMDevice::RAMDevice(uint16_t baseAddress, uint16_t size)
    : base(baseAddress), length(size), data(size, 0) {}

bool RAMDevice::handles(uint16_t address) const {
    return address >= base && address < base + length;
}

uint8_t RAMDevice::read(uint16_t address) {
    if (!handles(address)) throw std::out_of_range("RAM read out of bounds");
    return data[address - base];
}

void RAMDevice::write(uint16_t address, uint8_t value) {
    if (!handles(address)) throw std::out_of_range("RAM write out of bounds");
    data[address - base] = value;
}

}
