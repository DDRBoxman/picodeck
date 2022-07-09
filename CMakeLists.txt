cmake_minimum_required(VERSION 3.13)

include(pico-sdk/pico_sdk_init.cmake)

project(picodeck)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(picodeck
    src/main.c
    src/usb_descriptors.c
    RTT/SEGGER_RTT.c
)

pico_generate_pio_header(picodeck ${CMAKE_CURRENT_LIST_DIR}/src/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

# Make sure TinyUSB can find tusb_config.h
target_include_directories(picodeck PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/RTT
        ${CMAKE_CURRENT_LIST_DIR}/generated)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(picodeck pico_stdlib hardware_pio tinyusb_device tinyusb_board)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(picodeck)
