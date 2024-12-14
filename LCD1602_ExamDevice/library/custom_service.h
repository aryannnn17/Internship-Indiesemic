/*
 * Copyright (c) 2024 Indiesemic Pvt Ltd.
 */

#ifndef BT_CUSTOM_SERVICE_H_
#define BT_CUSTOM_SERVICE_H_

/**
 * @file
 * @defgroup Custom GATT Service
 * @{
 * @brief Custom Service GATT Service API.
 */

#include <zephyr/types.h>
#include <zephyr/bluetooth/conn.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief UUID of the Custom Service. **/
#define BT_UUID_CUSTOM_SERVICE_VAL \
	BT_UUID_128_ENCODE(0x45757068, 0x4861, 0x7273, 0x6820, 0x592e204d616e)

#define BT_UUID_CUSTOM_CHARACTERISTIC_VAL \
	BT_UUID_128_ENCODE(0x45757069, 0x4861, 0x7273, 0x6820, 0x592e204d616e)

#define BT_UUID_CUSTOM_SERVICE BT_UUID_DECLARE_128(BT_UUID_CUSTOM_SERVICE_VAL)
#define BT_UUID_CUSTOM_CHARACTERISTIC BT_UUID_DECLARE_128(BT_UUID_CUSTOM_CHARACTERISTIC_VAL)

/** @brief Custom Service send status. */
enum bt_custom_service_send_status
{
	/** Send notification enabled. */
	BT_CUSTOM_SERVICE_SEND_STATUS_ENABLED,
	/** Send notification disabled. */
	BT_CUSTOM_SERVICE_SEND_STATUS_DISABLED,
};

/** @brief Pointers to the callback functions for service events. */
struct bt_custom_service_cb
{
	/** @brief Data received callback.
	 *
	 * The data has been received as a write request on the Custom Service
	 * Characteristic.
	 *
	 * @param[in] conn  Pointer to connection object that has received data.
	 * @param[in] data  Received data.
	 * @param[in] len   Length of received data.
	 */
	void (*received)(struct bt_conn *conn,
						const uint8_t *const data, uint16_t len);

	/** @brief Data sent callback.
	 *
	 * The data has been sent as a notification and written on the Custom Service
	 * Characteristic.
	 *
	 * @param[in] conn Pointer to connection object, or NULL if sent to all
	 *                 connected peers.
	 */
	void (*sent)(struct bt_conn *conn);

	/** @brief Send state callback.
	 *
	 * Indicate the CCCD descriptor status of the Custom Service characteristic.
	 *
	 * @param[in] status Send notification status.
	 */
	void (*send_enabled)(enum bt_custom_service_send_status status);
};

/**@brief Initialize the service.
 *
 * @details This function registers a GATT service with one characteristics.
 *          A remote device that is connected to this service can send data to
 *          the Characteristic. When the remote enables notifications, it is
 *          notified when data is sent to the Characteristic.
 *
 * @param[in] callbacks  Struct with function pointers to callbacks for service
 *                       events. If no callbacks are needed, this parameter can
 *                       be NULL.
 *
 * @retval 0 If initialization is successful.
 *           Otherwise, a negative value is returned.
 */
int bt_custom_service_init(struct bt_custom_service_cb *callbacks);

/**@brief Send data.
 *
 * @details This function sends data to a connected peer, or all connected
 *          peers.
 *
 * @param[in] conn Pointer to connection object, or NULL to send to all
 *                 connected peers.
 * @param[in] data Pointer to a data buffer.
 * @param[in] len  Length of the data in the buffer.
 *
 * @retval 0 If the data is sent.
 *           Otherwise, a negative value is returned.
 */
int bt_custom_service_send(struct bt_conn *conn, const uint8_t *data, uint16_t len);

#ifdef __cplusplus
}
#endif

/**
 *@}
 */

#endif /* BT_CUSTOM_SERVICE_H_ */
