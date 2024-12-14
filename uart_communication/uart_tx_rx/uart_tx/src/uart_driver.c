#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "zephyr/drivers/uart.h"
#include "uart_driver.h"

const struct device *uart = DEVICE_DT_GET(DT_NODELABEL(uart1));

static uint8_t tx_buf[] = {"NO MORE WORK FROM HOME\r\n"};
static uint8_t rx_buf[50] = {0};

const struct uart_config uart_cfg = {
    .baudrate = 115200,
    .parity = UART_CFG_PARITY_NONE,
    .stop_bits = UART_CFG_STOP_BITS_1,
    .data_bits = UART_CFG_DATA_BITS_8,
    .flow_ctrl = UART_CFG_FLOW_CTRL_NONE};

void uart_transmit()
{
    // k_msleep(1000);
    // static uint8_t tx_buf[] = {"Hello! Welcome to IndieSemiC Pvt Ltd!!\r\n"};

    if (!device_is_ready(uart))
    {
        return 0;
    }
    uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_MS);
    k_msleep(500);
    printk("Data Transmitted....\r\n");
}

static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
    switch (evt->type)
    {
    case UART_RX_RDY:
        printf("rx rdy \n");
        printk("data received = %s \n", evt->data.rx_buf);
        break;

    case UART_RX_BUF_REQUEST:
        break;

    case UART_RX_DISABLED:
        printf("rx disabled \n");
        uart_rx_enable(dev, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);
        break;

    default:
        break;
    }
}

void uart_receiver()
{
    printk("Hi!\r\n");
    if (!device_is_ready(uart))
    {
        return;
    }

    uart_callback_set(uart, uart_cb, NULL);
    uart_rx_enable(uart, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);
    // uart_tx(uart, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);
/* 
    while (1)
    {
        k_msleep(1000);
    } */
    return 0;
}