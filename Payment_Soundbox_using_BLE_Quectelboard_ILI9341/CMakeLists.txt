cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(soundbox_project)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/custom.c)
target_sources(app PRIVATE src/tft_driver.c)
