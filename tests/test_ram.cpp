
#include "catch_amalgamated.hpp"
#include "RAMDevice.hpp"

using namespace micromodel;

TEST_CASE("RAM read/write", "[ram]") {
    RAMDevice ram(0x0000, 0x0100);

    ram.write(0x0010, 0x5A);
    REQUIRE(ram.read(0x0010) == 0x5A);
}

TEST_CASE("RAM rejects out-of-range access", "[ram]") {
    RAMDevice ram(0x0000, 0x0010);
    REQUIRE_THROWS_AS(ram.write(0x1000, 0x01), std::out_of_range);
}
