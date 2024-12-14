/*
 * Copyright (c) 2024 Indiesemic Pvt Ltd.
 */

#ifndef BLE_DATA_PROCESS_H_
#define BLE_DATA_PROCESS_H_

/**
 * @file
 * @defgroup BLE Data Processor
 * @{
 * @brief BLE Data Processor API.
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define COMMAND_POS 0x00
#define RESP_COMMAND_POS 0x00
#define RESP_COMMAND_MUL 0x80
#define RESP_DATA_POS   0x01

#define SEND_CRED   0x01
#define SEND_QNA    0x02


int ble_process_received_data(const uint8_t *const data, uint16_t len, uint8_t *resp_data);

#ifdef __cplusplus
}
#endif

/**
 *@}
 */

#endif /* BLE_DATA_PROCESS_H_ */
