# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(binary_clock C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

pico_sdk_init()

add_executable(binary_clock
    src/main.c
    src/shiftreg_595.c
)

target_compile_definitions(binary_clock PRIVATE
    BINARY_CLOCK_LATCH_PIN=14
    BINARY_CLOCK_SHIFT_CLK_PIN=15
    BINARY_CLOCK_DS_PIN=16
)

target_link_libraries(binary_clock pico_stdlib)

pico_enable_stdio_usb(binary_clock 1)
pico_enable_stdio_uart(binary_clock 0)  