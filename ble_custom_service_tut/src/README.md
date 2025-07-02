<h2> BLE Custom Service for Nordic nRF53 Series </h2>

This repository contains driver-level code for implementing a custom Bluetooth Low Energy (BLE) service on a Nordic nRF53 series board. It is built using the nRF Connect SDK and includes full configuration and build setup via prj.conf, overlay files, and other necessary project files.

<h3>📁 Repository: ble_custom_service_tut</h3>

<h4>🚀 Project Overview</h4>
This project demonstrates how to define, register, and handle a custom BLE GATT service on an nRF53 device. It serves as a template for anyone looking to build low-level Bluetooth applications using Nordic's Zephyr-based SDK.

<h4>📌 Features:</h4>
    ✅ BLE advertising and connection setup
    ✅ Custom 128-bit UUID-based GATT service and characteristics
    ✅ GATT read/write/notify support
    ✅ Dynamic data handling in characteristics
    ✅ Uses Nordic’s Bluetooth subsystem APIs
    ✅ Configurable via prj.conf and .overlay files

<h4>🧰 Tools & Dependencies</h4>
    Board: Nordic nRF5340 DK
    SDK: nRF Connect SDK (Tested on v2.x.x)
    Toolchain: Zephyr RTOS
    Build System: CMake + west

<h4>📁 Project Structure</h4>
ble_custom_service_tut/
├── src/
│   └── main.c              # Main application entry
├── include/
│   └── custom_service.h    # Header for BLE custom service
├── boards/
│   └── nrf5340dk_nrf5340_cpuapp.overlay # Board-specific overlay
├── prj.conf                # Project configuration
├── CMakeLists.txt          # Build script
└── README.md               # You are here

<h4>📡 How to Test</h4>
    1. Flash the firmware to your nRF53 board.
    2. Open a BLE scanner (e.g., nRF Connect mobile app).
    3. Look for "MyBLEDevice" (or the configured name).
    4. Connect and observe the custom service UUID and characteristics.
    5. Read/write/subscribe to characteristic values.
