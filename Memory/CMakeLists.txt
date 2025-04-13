add_library(micromodel_memory STATIC
    RAMDevice.cpp
)

target_include_directories(micromodel_memory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(micromodel_memory PRIVATE micromodel_bus)
