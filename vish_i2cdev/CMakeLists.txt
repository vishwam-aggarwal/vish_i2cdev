add_library( vish_i2cdev
    vish_i2cdev.h
    vish_i2cdev.cpp
    )

target_link_libraries(vish_i2cdev
    pico_stdlib
    hardware_i2c
)

target_include_directories(vish_i2cdev PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")