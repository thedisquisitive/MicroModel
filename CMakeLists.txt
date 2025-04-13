cmake_minimum_required(VERSION 3.15)
project(Micromodel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Subdirectories
add_subdirectory(Bus)
add_subdirectory(Memory)
add_subdirectory(CPU)
add_subdirectory(MicroVM)
add_subdirectory(IO)
add_subdirectory(tests)

# Main program (optional, remove if you're just using tests)
add_executable(micromodel main.cpp)
target_link_libraries(micromodel
    micromodel_vm
    micromodel_cpu
    micromodel_memory
    micromodel_bus
    micromodel_io
)

# Tests
enable_testing()

add_test(NAME all_tests COMMAND micromodel_tests)
