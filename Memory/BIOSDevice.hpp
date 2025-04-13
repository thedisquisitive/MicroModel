#pragma once
#include "IBusDevice.hpp"
#include <vector>
#include <cstdint>

namespace micromodel {

class BIOSDevice : public IBusDevice {
public:
    BIOSDevice(uint16_t baseAddress, const std::vector<uint8_t>& data);

    bool handles(uint16_t address) const override;
    uint8_t read(uint16_t address) override;
    void write(uint16_t, uint8_t) override {} // ROM: do nothing

private:
    uint16_t base;
    std::vector<uint8_t> rom;
};

}
