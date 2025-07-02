<h2> BLE Custom Service for Nordic nRF53 Series </h2>

This repository contains driver-level code for implementing a custom Bluetooth Low Energy (BLE) service on a Nordic nRF53 series board. It is built using the nRF Connect SDK and includes full configuration and build setup via prj.conf, overlay files, and other necessary project files.

<h3>📁 Repository: ble_custom_service_tut</h3>

<h4>🚀 Project Overview</h4>
This project demonstrates how to define, register, and handle a custom BLE GATT service on an nRF53 device. It serves as a template for anyone looking to build low-level Bluetooth applications using Nordic's Zephyr-based SDK.

<h4>📌 Features:</h4>
    ✅ BLE advertising and connection setup</br>
    ✅ Custom 128-bit UUID-based GATT service and characteristics</br>
    ✅ GATT read/write/notify support</br>
    ✅ Dynamic data handling in characteristics</br>
    ✅ Uses Nordic’s Bluetooth subsystem APIs</br>
    ✅ Configurable via prj.conf and .overlay files</br>

<h4>🧰 Tools & Dependencies</h4>
    Board: Nordic nRF5340 DK</br>
    SDK: nRF Connect SDK (Tested on v2.x.x)</br>
    Toolchain: Zephyr RTOS</br>
    Build System: CMake + west</br>

<h4>📁 Project Structure</h4>
ble_custom_service_tut/</br>
├── src/</br>
│   └── main.c              # Main application entry</br>
├── include/</br>
│   └── custom_service.h    # Header for BLE custom service</br>
├── boards/</br>
│   └── nrf5340dk_nrf5340_cpuapp.overlay # Board-specific overlay</br>
├── prj.conf                # Project configuration</br>
├── CMakeLists.txt          # Build script</br>
└── README.md               # You are here</br>

<h4>📡 How to Test</h4>
    1. Flash the firmware to your nRF53 board.</br>
    2. Open a BLE scanner (e.g., nRF Connect mobile app).</br>
    3. Look for "MyBLEDevice" (or the configured name).</br>
    4. Connect and observe the custom service UUID and characteristics.</br>
    5. Read/write/subscribe to characteristic values.</br>
