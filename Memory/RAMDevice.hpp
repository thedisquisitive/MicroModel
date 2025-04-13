#pragma once
#include "IBusDevice.hpp"
#include <vector>
#include <cstdint>

namespace micromodel {

class RAMDevice : public IBusDevice {
public:
    RAMDevice(uint16_t baseAddress, uint16_t size);

    bool handles(uint16_t address) const override;
    uint8_t read(uint16_t address) override;
    void write(uint16_t address, uint8_t value) override;

private:
    uint16_t base;
    uint16_t length;
    std::vector<uint8_t> data;
};

}
