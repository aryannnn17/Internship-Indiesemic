/*
 * Copyright (c) 2024 Indiesemic Pvt Ltd.
 */

#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <stdint.h>
#include "custom_service.h"
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(bt_custom_service, LOG_LEVEL_DBG);

static struct bt_custom_service_cb custom_service_cb;

static void custom_service_ccc_cfg_changed(const struct bt_gatt_attr *attr,
										   uint16_t value)
{
	if (custom_service_cb.send_enabled)
	{
		LOG_DBG("Notification has been turned %s",
				value == BT_GATT_CCC_NOTIFY ? "on" : "off");
		custom_service_cb.send_enabled(value == BT_GATT_CCC_NOTIFY ? BT_CUSTOM_SERVICE_SEND_STATUS_ENABLED : BT_CUSTOM_SERVICE_SEND_STATUS_DISABLED);
	}
}

static ssize_t on_receive(struct bt_conn *conn,
						  const struct bt_gatt_attr *attr,
						  const void *buf,
						  uint16_t len,
						  uint16_t offset,
						  uint8_t flags)
{
	LOG_DBG("Received data, handle %d, conn %p",
			attr->handle, (void *)conn);

	if (custom_service_cb.received)
	{
		custom_service_cb.received(conn, buf, len);
	}
	return len;
}

static void on_sent(struct bt_conn *conn, void *user_data)
{
	ARG_UNUSED(user_data);

	LOG_DBG("Data send, conn %p", (void *)conn);

	if (custom_service_cb.sent)
	{
		custom_service_cb.sent(conn);
	}
}

/* Custom Service Declaration */
BT_GATT_SERVICE_DEFINE(custom_svc,
					   BT_GATT_PRIMARY_SERVICE(BT_UUID_CUSTOM_SERVICE),
					   BT_GATT_CHARACTERISTIC(BT_UUID_CUSTOM_CHARACTERISTIC,
											  BT_GATT_CHRC_WRITE | BT_GATT_CHRC_NOTIFY,
											  BT_GATT_PERM_WRITE_ENCRYPT | BT_GATT_PERM_READ,
											  NULL, on_receive, NULL),
					   BT_GATT_CCC(custom_service_ccc_cfg_changed,
								   BT_GATT_PERM_READ | BT_GATT_PERM_WRITE), );

int bt_custom_service_init(struct bt_custom_service_cb *callbacks)
{
	if (callbacks)
	{
		custom_service_cb.received = callbacks->received;
		custom_service_cb.sent = callbacks->sent;
		custom_service_cb.send_enabled = callbacks->send_enabled;
	}

	return 0;
}

int bt_custom_service_send(struct bt_conn *conn, const uint8_t *data, uint16_t len)
{
	struct bt_gatt_notify_params params = {0};
	const struct bt_gatt_attr *attr = &custom_svc.attrs[2];

	params.attr = attr;
	params.data = data;
	params.len = len;
	params.func = on_sent;

	if (!conn)
	{
		LOG_DBG("Notification send to all connected peers");
		return bt_gatt_notify_cb(NULL, &params);
	}
	else if (bt_gatt_is_subscribed(conn, attr, BT_GATT_CCC_NOTIFY))
	{
		return bt_gatt_notify_cb(conn, &params);
	}
	else
	{
		return -EINVAL;
	}
}
