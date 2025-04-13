#include "MicroVM.hpp"

namespace micromodel {

MicroVM::MicroVM() {
    bus = std::make_shared<Bus>();
}

void MicroVM::add_device(std::shared_ptr<IBusDevice> device) {
    devices.push_back(device);
    bus->attach(device);
}

void MicroVM::set_cpu(std::shared_ptr<ICPUDevice> c) {
    cpu = c;
    cpu->attach_bus(bus);
}

void MicroVM::reset() {
    if (cpu) cpu->reset();
}

void MicroVM::step() {
    if (cpu) cpu->step();
}

void MicroVM::tick() {
    if (cpu) cpu->tick();
}

std::shared_ptr<Bus> MicroVM::get_bus() {
    return bus;
}

}
