#pragma once

#include "Bus.hpp"
#include "ICPUDevice.hpp"
#include "IBusDevice.hpp"
#include <memory>
#include <vector>

namespace micromodel {

class MicroVM {
public:
    MicroVM();

    void add_device(std::shared_ptr<IBusDevice> device);
    void set_cpu(std::shared_ptr<ICPUDevice> cpu);

    void reset();
    void step();
    void tick();

    std::shared_ptr<Bus> get_bus();

private:
    std::shared_ptr<Bus> bus;
    std::shared_ptr<ICPUDevice> cpu;
    std::vector<std::shared_ptr<IBusDevice>> devices;
};

}
