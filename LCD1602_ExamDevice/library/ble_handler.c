/*
 * Copyright (c) 2024 Indiesemic Pvt Ltd.
 */

#include "ble_handler.h"
#include "custom_service.h"
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/settings/settings.h>
#include <stdint.h>
#include "ble_data_process.h"
#include <zephyr/kernel.h>

LOG_MODULE_REGISTER(ble_handler, LOG_LEVEL_DBG);

#define STOP_BLE_TIMEOUT_MS 15 * 60 * 1000

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

bool ble_connected_state = false;
bool ble_advertising = false;
struct bt_conn *current_conn;

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static const struct bt_data sd[] = {
    BT_DATA_BYTES(BT_DATA_UUID16_ALL, BT_UUID_16_ENCODE(BT_UUID_BAS_VAL),
                  BT_UUID_16_ENCODE(BT_UUID_DIS_VAL)),
    BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_CUSTOM_SERVICE_VAL),
};

#define BT_LE_ADV_CONN_NO_ACCEPT_LIST BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONNECTABLE | \
                                                          BT_LE_ADV_OPT_ONE_TIME, \
                                                      BT_GAP_ADV_FAST_INT_MIN_2,  \
                                                      BT_GAP_ADV_FAST_INT_MAX_2, NULL)

#define BT_LE_ADV_CONN_ACCEPT_LIST BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONNECTABLE |     \
                                                       BT_LE_ADV_OPT_FILTER_CONN | \
                                                       BT_LE_ADV_OPT_ONE_TIME,     \
                                                   BT_GAP_ADV_FAST_INT_MIN_2,      \
                                                   BT_GAP_ADV_FAST_INT_MAX_2, NULL)

void stop_ble_timer_handler(struct k_timer *dummy)
{
    int err;

    err = stop_ble();
    if (err)
    {
        LOG_ERR("BLE stop failed (err %d)", err);
        return;
    }

    LOG_INF("Bluetooth Stopped Successfully");
}

K_TIMER_DEFINE(stop_ble_timer, stop_ble_timer_handler, NULL);

static void setup_accept_list_cb(const struct bt_bond_info *info, void *user_data)
{
    int *bond_cnt = user_data;

    if ((*bond_cnt) < 0)
    {
        return;
    }

    int err = bt_le_filter_accept_list_add(&info->addr);
    LOG_DBG("Added following peer to accept list: %x %x", info->addr.a.val[0],
            info->addr.a.val[1]);
    if (err)
    {
        LOG_ERR("Cannot add peer to filter accept list (err: %d)", err);
        (*bond_cnt) = -EIO;
    }
    else
    {
        (*bond_cnt)++;
    }
}

static int setup_accept_list(uint8_t local_id)
{
    int err = bt_le_filter_accept_list_clear();

    if (err)
    {
        LOG_ERR("Cannot clear accept list (err: %d)", err);
    }

    int bond_cnt = 0;

    bt_foreach_bond(local_id, setup_accept_list_cb, &bond_cnt);

    return bond_cnt;
}

void advertise_with_acceptlist(struct k_work *work)
{
    if (!ble_advertising)
        return;

    int err = 0;
    int allowed_cnt = setup_accept_list(BT_ID_DEFAULT);
    if (allowed_cnt < 0)
    {
        LOG_ERR("Acceptlist setup failed (err:%d)", allowed_cnt);
    }
    else
    {
        err = bt_le_adv_stop();
        if (err)
        {
            LOG_ERR("Cannot stop advertising err: %d", err);
        }

        if (allowed_cnt == 0)
        {
            LOG_DBG("Advertising with no Accept list");
            err = bt_le_adv_start(BT_LE_ADV_CONN_NO_ACCEPT_LIST, ad, ARRAY_SIZE(ad), sd,
                                  ARRAY_SIZE(sd));
    
        }
        else
        {
            LOG_DBG("Acceptlist setup number  = %d", allowed_cnt);
            err = bt_le_adv_start(BT_LE_ADV_CONN_ACCEPT_LIST, ad, ARRAY_SIZE(ad), sd,
                                  ARRAY_SIZE(sd));
        }
        if (err)
        {
            LOG_ERR("Advertising failed to start (err %d)", err);

            return;
        }
        LOG_DBG("Advertising successfully started");
    }
}

K_WORK_DEFINE(advertise_acceptlist_work, advertise_with_acceptlist);

void ble_adv_start_handler(struct k_timer *dummy)
{
    k_work_submit(&advertise_acceptlist_work);
}

K_TIMER_DEFINE(ble_adv_start, ble_adv_start_handler, NULL);

static void connected(struct bt_conn *conn, uint8_t err)
{
    int sec_err;
    char addr[BT_ADDR_LE_STR_LEN];

    if (err)
    {
        LOG_ERR("Connection failed (err 0x%02x)", err);
        return;
    }

    current_conn = conn;
    ble_connected_state = true;

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
    LOG_DBG("Connected %s", addr);

    sec_err = bt_conn_set_security(conn, BT_SECURITY_L2);
    if (sec_err)
    {
        LOG_ERR("Failed to set security (err %d)", sec_err);
        ble_connected_state = false;
    }
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    char addr[BT_ADDR_LE_STR_LEN];

    ble_connected_state = false;

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
    LOG_DBG("Disconnected from %s (reason %u)", addr, reason);

    k_timer_start(&ble_adv_start, K_MSEC(1000), K_NO_WAIT);
    k_timer_start(&stop_ble_timer, K_MSEC(STOP_BLE_TIMEOUT_MS), K_NO_WAIT);
}

static void security_changed(struct bt_conn *conn, bt_security_t level,
                             enum bt_security_err err)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    if (!err)
    {
        LOG_DBG("Security changed: %s level %u", addr, level);
    }
    else
    {
        LOG_ERR("Security failed: %s level %u err %d", addr, level, err);
    }
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected = connected,
    .disconnected = disconnected,
    .security_changed = security_changed,
};

static void auth_cancel(struct bt_conn *conn)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    LOG_INF("Pairing cancelled: %s", addr);

    bt_conn_disconnect(conn, BT_HCI_ERR_REMOTE_USER_TERM_CONN);
}

static void pairing_complete(struct bt_conn *conn, bool bonded)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    LOG_INF("Pairing completed: %s, bonded: %d", addr, bonded);
}

static void pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    LOG_ERR("Pairing failed conn: %s, reason %d", addr, reason);

    bt_conn_disconnect(conn, BT_HCI_ERR_REMOTE_USER_TERM_CONN);
}

static struct bt_conn_auth_cb conn_auth_callbacks = {
    .cancel = auth_cancel,
};

static struct bt_conn_auth_info_cb conn_auth_info_callbacks = {
    .pairing_complete = pairing_complete,
    .pairing_failed = pairing_failed,
};

static void bt_custom_service_receive_cb(struct bt_conn *conn, const uint8_t *const data,
                                         uint16_t len)
{
    int err;
    char addr[BT_ADDR_LE_STR_LEN] = {0};

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, ARRAY_SIZE(addr));

    LOG_DBG("Received data from: %s", addr);

    uint8_t resp_data[255];
    int resp_length = ble_process_received_data(data, len, &resp_data[0]);
    if (!resp_length)
    {
        LOG_ERR("Processing Data Failed");
    }

    err = bt_custom_service_send(conn, &resp_data[0], resp_length);
    if (err)
    {
        LOG_ERR("Sending over BLE failed (err %d)", err);
    }
}

static struct bt_custom_service_cb custom_service_cb = {
    .received = bt_custom_service_receive_cb,
};

int ble_init()
{
    int err;

    err = bt_enable(NULL);
    if (err)
    {
        LOG_ERR("Bluetooth init failed (err %d)", err);
        return err;
    }

    LOG_DBG("Bluetooth initialized");

    if (IS_ENABLED(CONFIG_SETTINGS))
    {
        settings_load();
    }

    err = bt_conn_auth_cb_register(&conn_auth_callbacks);
    if (err)
    {
        LOG_ERR("Failed to register authorization callbacks");
        return 0;
    }

    err = bt_conn_auth_info_cb_register(&conn_auth_info_callbacks);
    if (err)
    {
        LOG_ERR("Failed to register authorization info callbacks.");
        return 0;
    }

    err = bt_custom_service_init(&custom_service_cb);
    if (err)
    {
        LOG_ERR("Failed to initialize custom service (err: %d)", err);
        return err;
    }

    LOG_DBG("BLE initialised successfully");
    return 0;
}

int start_ble()
{
    k_work_submit(&advertise_acceptlist_work);

    ble_advertising = true;
    k_timer_start(&ble_adv_start, K_MSEC(1000), K_NO_WAIT);
    LOG_DBG("Advertising successfully started");
    return 0;
}

int start_ble_pairing()
{
    int err;

    err = bt_le_adv_stop();
    if (err)
    {
        LOG_ERR("Cannot stop advertising err: %d", err);
        return err;
    }

    err = bt_le_filter_accept_list_clear();
    if (err)
    {
        LOG_ERR("Cannot clear accept list (err: %d)", err);
        return err;
    }
    LOG_DBG("Filter Accept List cleared succesfully");

    err = bt_le_adv_start(BT_LE_ADV_CONN_NO_ACCEPT_LIST, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (err)
    {
        LOG_ERR("Cannot start open advertising (err: %d)", err);
        return err;
    }

    ble_advertising = true;

    LOG_DBG("Advertising successfully started in pairing mode");
    return 0;
}

int stop_ble()
{
    int err;

    err = ble_disconnect();
    if (err)
    {
        LOG_ERR("Failed to disconnect BLE (err %d)", err);
        return err;
    }

    err = bt_le_adv_stop();
    if (err)
    {
        LOG_ERR("Advertising failed to stop (err %d)", err);
        return err;
    }

    ble_advertising = false;

    LOG_DBG("Advertising successfully stopped");
    return 0;
}

int ble_disconnect()
{
    int err;

    err = bt_conn_disconnect(current_conn, BT_HCI_ERR_REMOTE_USER_TERM_CONN);
    if (err)
    {
        LOG_ERR("BLE disconnect failed (err %d)", err);
        return err;
    }

    ble_connected_state = false;

    LOG_DBG("BLE disconnected successfully");
    return 0;
}

int ble_remove_pairing()
{
    int err = bt_unpair(BT_ID_DEFAULT, BT_ADDR_LE_ANY);
    if (err)
    {
        LOG_ERR("Cannot delete bond (err: %d)", err);
        return err;
    }
    
    LOG_DBG("Bond deleted successfully");
    return 0;
}