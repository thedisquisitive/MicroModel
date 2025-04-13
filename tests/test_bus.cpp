#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "Bus.hpp"
#include "RAMDevice.hpp"

using namespace micromodel;

TEST_CASE("Bus read/write to RAM", "[bus]") {
    auto bus = std::make_shared<Bus>();
    auto ram = std::make_shared<RAMDevice>(0x0000, 0x0100);
    bus->attach(ram);

    bus->write(0x0010, 0xAB);
    REQUIRE(bus->read(0x0010) == 0xAB);
}

TEST_CASE("Bus throws on unmapped address", "[bus]") {
    auto bus = std::make_shared<Bus>();
    REQUIRE_THROWS_AS(bus->read(0x1234), std::runtime_error);
}
