#pragma once
#include "IBusDevice.hpp"
#include <cstdint>
#include <iostream>

namespace micromodel {

class SerialDevice : public IBusDevice {
public:
    SerialDevice(uint16_t address);
    ~SerialDevice();

    bool handles(uint16_t address) const override;
    uint8_t read(uint16_t address) override;     // Optional
    void write(uint16_t address, uint8_t value) override;

private:
    uint16_t ioAddress;
};

}
