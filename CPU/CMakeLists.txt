add_library(micromodel_cpu STATIC
    CPU_4004.cpp
)

target_include_directories(micromodel_cpu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(micromodel_cpu PRIVATE micromodel_bus)
