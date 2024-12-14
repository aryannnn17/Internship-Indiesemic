/*
 * Copyright (c) 2024 Indiesemic Pvt Ltd.
 */

#ifndef BLE_HANDLER_H_
#define BLE_HANDLER_H_

/**
 * @file
 * @defgroup BLE Handler
 * @{
 * @brief BLE Handler API.
 */

#include <zephyr/bluetooth/conn.h>

#ifdef __cplusplus
extern "C"
{
#endif

// BLE Connected or not State
extern bool ble_connected_state;

// BLE Advertising or not State
extern bool ble_advertising;

/** @brief BLE and Services Initialisation
 * @retval 0 If initialization is successful.
 *           Otherwise, a negative value is returned.
 */
int ble_init();

/** @brief BLE Advertising Start
 * @retval 0 If initialization is successful.
 *           Otherwise, a negative value is returned.
 */
int start_ble();

/** @brief BLE Advertising Start in Pairing Mode
 * @retval 0 If initialization is successful.
 *           Otherwise, a negative value is returned.
 */
int start_ble_pairing();

/** @brief BLE Advertising Stop
 * @retval 0 If initialization is successful.
 *           Otherwise, a negative value is returned.
 */
int stop_ble();

/** @brief BLE Disconnect Remote
 * @retval 0 If initialization is successful.
 *           Otherwise, a negative value is returned.
 */
int ble_disconnect();

/** @brief BLE Remove Pairing
 * @retval 0 If initialization is successful.
 *           Otherwise, a negative value is returned.
 */
int ble_remove_pairing();

#ifdef __cplusplus
}
#endif

/**
 *@}
 */

#endif /* BLE_HANDLER_H_ */
