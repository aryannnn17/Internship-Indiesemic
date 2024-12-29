cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(GPS_UART)


target_sources(app PRIVATE src/main.c)

target_sources(app PRIVATE src/isc_config/uart.c)
target_sources(app PRIVATE src/isc_config/GPS_config_io.c)
target_sources(app PRIVATE src/isc_config/cmd.c)

target_include_directories(app PRIVATE src/isc_config)

