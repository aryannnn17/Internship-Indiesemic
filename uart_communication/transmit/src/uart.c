#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/uart.h>
#include "uart.h"

#define SLEEP_TIME_MS 1000
#define RECEIVE_BUFF_SIZE 100

const struct device *uart = DEVICE_DT_GET(DT_NODELABEL(uart0));
static uint8_t tx_buf[] = {"WELCOME TO INDIESEMIC PVT. LTD."};

const struct uart_config uart_cfg = {
    .baudrate = 115200,
    .parity = UART_CFG_PARITY_NONE,
    .stop_bits = UART_CFG_STOP_BITS_1,
    .data_bits = UART_CFG_DATA_BITS_8,
    .flow_ctrl = UART_CFG_FLOW_CTRL_NONE};

void uart_transmit()
{
        // char input_data[100];
        // scanf("%s",&input_data);
        
        int err;
        if (!device_is_ready(uart))
        {
                return -1;
        }

        err = uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_US);

        while (1)
        {
                k_msleep(1000);
        }
        
}


static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
        switch (evt->type)
        {
        case UART_RX_RDY:
                printk("data: ");
                for (int i = 0; i < evt->data.rx.len; i++)
                {
                        printk("%s", evt->data.rx.buf[evt->data.rx.offset + i]);
                }
                printk("\n");
                break;

        case UART_RX_BUF_REQUEST:
                break;
        }
}

void uart_reciever(void)
{
        static uint8_t rx_buf[50] = {0};
        if (!device_is_ready(uart))
        {
                printk("uart not ready. returning.\n");
                return;
        }

        uart_callback_set(uart, uart_cb, NULL);
        uart_rx_enable(uart, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);
        return 0;
}