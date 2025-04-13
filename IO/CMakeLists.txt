add_library(micromodel_io STATIC
    SerialDevice.cpp
)

target_include_directories(micromodel_io PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(micromodel_io PRIVATE micromodel_bus)
