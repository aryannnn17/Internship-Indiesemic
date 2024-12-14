/* #include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/uart.h>
#include "uart.h"

int main(){
    uart_reciever();
}

 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "zephyr/drivers/uart.h"

const struct device *uart = DEVICE_DT_GET(DT_NODELABEL(uart1));

static uint8_t tx_buf[] = {"Hello! Welcome to IndieSemiC Pvt Ltd!!\r\n"};
static uint8_t rx_buf[50] = {0};
 // A buffer to store incoming UART data

const struct uart_config uart_cfg = {
    .baudrate = 115200,
    .parity = UART_CFG_PARITY_NONE,
    .stop_bits = UART_CFG_STOP_BITS_1,
    .data_bits = UART_CFG_DATA_BITS_8,
    .flow_ctrl = UART_CFG_FLOW_CTRL_NONE};

void uart_transmit()
{
    if (!device_is_ready(uart))
    {
        return -1;
    }

    uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_US);

    while (1)
    {
        k_msleep(1000);
    }
}

static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
    // static uint8_t rx_buf[50] = {0};
    switch (evt->type)
    {

        /* case UART_TX_DONE:
            printf("transmission complete \n");
            break;

        case UART_TX_ABORTED:
            // do something
            break; */

    case UART_RX_RDY:
        printf("rx rdy \n");
        // if ((evt->data.rx.len) != 0)
        // {
        //     for (int i = 0; i < evt->data.rx.len; i++)
        //     {
        printk("data received = %s \n", evt->data.rx_buf);
        // printk("data: ");
        
        // printk("%s", evt->data.rx.buf[evt->data.rx.offset]);
        
        // printk("\n");
        // printf("received message =  %s\n",evt->data.rx.buf[evt->data.rx.offset]);
        //     }
        // }
        break;

    case UART_RX_BUF_REQUEST:
        //     /* printf("requesting buffer \n");
        //     // do something */
        break;

    /* case UART_RX_BUF_RELEASED:
        printf("buffer released \n");
        // do something
        break;
 */
    case UART_RX_DISABLED:
        // printf("rx disabled \n");
        uart_rx_enable(dev, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);
        break;
        /*
            case UART_RX_STOPPED:
                // do something
                break;

            default:
                break; */
    }
}

int main()
{
    printk("Hi!\r\n");
    if (!device_is_ready(uart))
    {
        return;
    }

    uart_callback_set(uart, uart_cb, NULL);

    uart_rx_enable(uart, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);

    uart_tx(uart, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);
    /* if (err)
    {
        return err;
    }
 */
    while (1)
    {
        k_msleep(1000);
    }
    return 0;
}