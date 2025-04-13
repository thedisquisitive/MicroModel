add_library(micromodel_vm STATIC
    MicroVM.cpp
)

target_include_directories(micromodel_vm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(micromodel_vm
    PRIVATE micromodel_bus
    PRIVATE micromodel_cpu
)
