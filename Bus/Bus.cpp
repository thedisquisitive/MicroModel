#include "Bus.hpp"
#include <stdexcept>
#include <sstream>

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
    for (const auto& device : devices) {
        if (device->handles(address)) {
            device->write(address, value);
            return;
        }
    }
    std::ostringstream oss;
    oss << "Bus write error at 0x" << std::hex << address;
    throw std::runtime_error(oss.str());
}

}
