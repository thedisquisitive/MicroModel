#pragma once
#include <memory>

namespace micromodel {

class Bus;

class ICPUDevice {
public:
    virtual ~ICPUDevice() = default;

    virtual void attach_bus(std::shared_ptr<Bus> bus) = 0;
    virtual void step() = 0;
    virtual void tick() {}
    virtual void reset() {}

    bool isRunning = false;

    virtual bool Running() { return isRunning; }
    virtual void Start() { isRunning = true; }
    virtual void Stop() { isRunning = false; }
};

}
