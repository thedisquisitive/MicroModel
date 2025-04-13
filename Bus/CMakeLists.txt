add_library(micromodel_bus STATIC
    Bus.cpp
)

target_include_directories(micromodel_bus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
