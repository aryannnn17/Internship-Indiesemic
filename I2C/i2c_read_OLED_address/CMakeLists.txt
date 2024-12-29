cmake_minimum_required(VERSION 3.20.0)
set(SHIELD ssd1306_128x64)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(i2c_read_OLED_address)

target_sources(app PRIVATE src/main.c)
