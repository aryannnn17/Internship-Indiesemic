cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(LCD_1602)

target_sources(app PRIVATE
    src/main.c
    library/ble_data_process.c
    library/ble_handler.c
    library/custom_service.c
    library/functionality.c
    library/i2c-lcd.c
    library/eeprom_at24.c
    library/keypad_driver.c
)

target_include_directories(app PRIVATE library)