# tests/CMakeLists.txt

add_executable(micromodel_tests
    test_bus.cpp
    test_ram.cpp
    test_cpu.cpp
    catch_amalgamated.cpp
    ${CMAKE_SOURCE_DIR}/IO/SerialDevice.cpp 
)

target_include_directories(micromodel_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/Bus
    ${CMAKE_SOURCE_DIR}/Memory
    ${CMAKE_SOURCE_DIR}/CPU
    ${CMAKE_SOURCE_DIR}/Devices
    ${CMAKE_SOURCE_DIR}/IO
    ${CMAKE_SOURCE_DIR}/tests
)

target_link_libraries(micromodel_tests
    micromodel_bus
    micromodel_memory
    micromodel_cpu
)

# Ensure catch2 is found
target_sources(micromodel_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/tests/catch_amalgamated.hpp
)

# Optional: Integrate with CTest
enable_testing()
add_test(NAME all_tests COMMAND micromodel_tests)
