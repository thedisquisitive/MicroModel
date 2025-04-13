#pragma once
#include <cstdint>

namespace micromodel {

class IBusDevice {
public:
    virtual ~IBusDevice() = default;

    virtual bool handles(uint16_t address) const = 0;
    virtual uint8_t read(uint16_t address) = 0;
    virtual void write(uint16_t address, uint8_t value) = 0;
};

}
