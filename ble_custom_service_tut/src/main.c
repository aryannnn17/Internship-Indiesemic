
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <dk_buttons_and_leds.h>
#include "custom.h"

#define LOG_MODULE_NAME app
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#define RUN_STATUS_LED DK_LED1
#define CONN_STATUS_LED DK_LED2
#define RUN_LED_BLINK_INTERVAL 1000

static struct bt_conn *current_conn;

/* Declarations */
void on_connected(struct bt_conn *conn, uint8_t err);
void on_disconnected(struct bt_conn *conn, uint8_t reason);
void on_notif_changed(enum bt_button_notifications_enabled status);
void on_data_received(struct bt_conn *conn, const uint8_t *const data, uint16_t len);
void on_le_param_updated(struct bt_conn *conn, uint16_t interval, uint16_t latency, uint16_t timeout);
void on_le_data_len_updated(struct bt_conn *conn, struct bt_conn_le_data_len_info *info);

/* Create variable that holds callback for MTU negotiation */
static struct bt_gatt_exchange_params exchange_params;

/* forward declaration of exchange_func(): */
static void exchange_func(struct bt_conn *conn, uint8_t att_err, struct bt_gatt_exchange_params *params);

struct bt_conn_cb bluetooth_callbacks = {
    .connected = on_connected,
    .disconnected = on_disconnected,
    .le_param_updated = on_le_param_updated,
    .le_data_len_updated = on_le_data_len_updated,
};
struct bt_remote_service_cb remote_callbacks = {
    .notif_changed = on_notif_changed,
    .data_received = on_data_received,
};

/*  Define the function to update the connection's data length */
static void update_data_length(struct bt_conn *conn)
{
        int err;
        struct bt_conn_le_data_len_param my_data_len = {
            .tx_max_len = BT_GAP_DATA_LEN_MAX,
            .tx_max_time = BT_GAP_DATA_TIME_MAX,
        };
        err = bt_conn_le_data_len_update(conn, &my_data_len);
        if (err)
        {
                LOG_ERR("data_len_update failed (err %d)", err);
        }
}

/*  Define the function to update the connection's MTU */
static void update_mtu(struct bt_conn *conn)
{
        int err;
        exchange_params.func = exchange_func;

        err = bt_gatt_exchange_mtu(conn, &exchange_params);
        if (err)
        {
                LOG_ERR("bt_gatt_exchange_mtu failed (err %d)", err);
        }
}

/* Implement callback function for MTU exchange */
static void exchange_func(struct bt_conn *conn, uint8_t att_err, struct bt_gatt_exchange_params *params)
{
        LOG_INF("MTU exchange %s", att_err == 0 ? "successful" : "failed");
        if (!att_err)
        {
                uint16_t payload_mtu =
                    bt_gatt_get_mtu(conn) - 3; // 3 bytes used for Attribute headers.
                LOG_INF("New MTU: %d bytes", payload_mtu);
        }
}

/* Callbacks */
void on_connected(struct bt_conn *conn, uint8_t err)
{
        if (err)
        {
                LOG_ERR("connection err: %d", err);
                return;
        }
        LOG_INF("Connected.");
        current_conn = bt_conn_ref(conn);
        dk_set_led_on(CONN_STATUS_LED);

        struct bt_conn_info info;
        err = bt_conn_get_info(conn, &info);
        if (err)
        {
                LOG_ERR("bt_conn_get_info() returned %d", err);
                return;
        }

        /*  Add the connection parameters to your log */
        double connection_interval = info.le.interval * 1.25; // in ms
        uint16_t supervision_timeout = info.le.timeout * 10;  // in ms
        LOG_INF("Connection parameters: interval %.2f ms, latency %d intervals, timeout %d ms",
                connection_interval, info.le.latency, supervision_timeout);
        /*  Update the data length and MTU */
        update_data_length(conn);
        update_mtu(conn);
}

void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
        LOG_INF("Disconnected (reason: %d)", reason);
        dk_set_led_off(CONN_STATUS_LED);
        if (current_conn)
        {
                bt_conn_unref(current_conn);
                current_conn = NULL;
        }
}
/* Add the callback for connection parameter updates */
void on_le_param_updated(struct bt_conn *conn, uint16_t interval, uint16_t latency,
                         uint16_t timeout)
{
        double connection_interval = interval * 1.25; // in ms
        uint16_t supervision_timeout = timeout * 10;  // in ms
        LOG_INF("Connection parameters updated: interval %.2f ms, latency %d intervals, timeout %d ms",
                connection_interval, latency, supervision_timeout);
}
/* Write a callback function to inform about updates in data length */
void on_le_data_len_updated(struct bt_conn *conn, struct bt_conn_le_data_len_info *info)
{
        uint16_t tx_len = info->tx_max_len;
        uint16_t tx_time = info->tx_max_time;
        uint16_t rx_len = info->rx_max_len;
        uint16_t rx_time = info->rx_max_time;
        LOG_INF("Data length updated. Length %d/%d bytes, time %d/%d us", tx_len, rx_len, tx_time,
                rx_time);
}

void on_notif_changed(enum bt_button_notifications_enabled status)
{
        if (status == BT_BUTTON_NOTIFICATIONS_ENABLED)
        {
                LOG_INF("Notifications enabled");
        }
        else
        {
                LOG_INF("Notifications disabled");
        }
}

void on_data_received(struct bt_conn *conn, const uint8_t *const data, uint16_t len)
{
        uint8_t temp_str[len + 1];
        memcpy(temp_str, data, len);
        temp_str[len] = 0x00;

        LOG_INF("Received data on conn %p. Len: %d", (void *)conn, len);
        LOG_INF("Data: %s", strdup(temp_str));
}

void button_handler(uint32_t button_state, uint32_t has_changed)
{
        int err;
        int button_pressed = 0;
        if (has_changed & button_state)
        {
                switch (has_changed)
                {
                case DK_BTN1_MSK:
                        button_pressed = 1;
                        break;
                case DK_BTN2_MSK:
                        button_pressed = 2;
                        break;
                case DK_BTN3_MSK:
                        button_pressed = 3;
                        break;
                case DK_BTN4_MSK:
                        button_pressed = 4;
                        break;
                default:
                        break;
                }
                LOG_INF("Button %d pressed.", button_pressed);
                set_button_value(button_pressed);
                err = send_button_notification(current_conn, button_pressed);
                if (err)
                {
                        LOG_ERR("Couldn't send notificaton. (err: %d)", err);
                }
        }
}

/* Configurations */
static void configure_dk_buttons_leds(void)
{
        int err;
        err = dk_leds_init();
        if (err)
        {
                LOG_ERR("Couldn't init LEDS (err %d)", err);
        }
        err = dk_buttons_init(button_handler);
        if (err)
        {
                LOG_ERR("Couldn't init buttons (err %d)", err);
        }
}

/* Main */
void main(void)
{
        int err;
        int blink_status = 0;
        LOG_INF("Hello World! %s\n", CONFIG_BOARD);

        configure_dk_buttons_leds();

        err = bluetooth_init(&bluetooth_callbacks, &remote_callbacks);
        if (err)
        {
                LOG_INF("Couldn't initialize Bluetooth. err: %d", err);
        }

        LOG_INF("Running...");
        for (;;)
        {
                dk_set_led(RUN_STATUS_LED, (blink_status++) % 2);
                k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
        }
}