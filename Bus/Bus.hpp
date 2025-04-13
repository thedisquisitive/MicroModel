#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include "IBusDevice.hpp"

namespace micromodel {

class Bus {
public:
    void attach(std::shared_ptr<IBusDevice> device);

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);

private:
    std::vector<std::shared_ptr<IBusDevice>> devices;
};

}
