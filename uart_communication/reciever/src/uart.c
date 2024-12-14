// #include <zephyr/kernel.h>
// #include <zephyr/drivers/gpio.h>
// #include <zephyr/sys/printk.h>
// #include <zephyr/drivers/uart.h>
// #include "uart.h"

// #define SLEEP_TIME_MS 1000
// #define RECEIVE_BUFF_SIZE 10

// const struct device *uart = DEVICE_DT_GET(DT_NODELABEL(uart1));
//  static uint8_t tx_buf[] = {"Hello! Welcome to IndieSemiC Pvt Ltd!!\r\n"};
// static uint8_t rx_buf[RECEIVE_BUFF_SIZE] = {0}; // A buffer to store incoming UART data

// const struct uart_config uart_cfg = {
//     .baudrate = 115200,
//     .parity = UART_CFG_PARITY_NONE,
//     .stop_bits = UART_CFG_STOP_BITS_1,
//     .data_bits = UART_CFG_DATA_BITS_8,
//     .flow_ctrl = UART_CFG_FLOW_CTRL_NONE};

// void uart_transmit()
// {
//     // int err;
//     if (!device_is_ready(uart))
//     {
//         return 0;
//     }
//     /* err = uart_configure(uart, &uart_cfg);
//     if (err == -ENOSYS)
//     {
//         return -ENOSYS;
//     } */

//     uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_US);
//     /* if (err)
//     {
//         printk("uart_tx errored: %d.\n", err);
//     } */
//     while (1)
//     {
//         k_msleep(1000);
//     }
//     // k_msleep(1000);
// }

// static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
// {
//     switch (evt->type)
//     {
//     case UART_RX_RDY:
//         printk("evt->data.rx.len: %d\n", evt->data.rx.len);
//         printk("evt->data.rx.offset: %d\n", evt->data.rx.offset);
//         printk("data: ");
//         printk("%c \r\n", evt->data.rx.buf[evt->data.rx.offset]);
//         break;

//     case UART_RX_BUF_REQUEST:
//         // printk("UART_RX_BUF_REQUEST\n");
//         /* for (int i = 0; i < evt->data.rx.len; i++)
//         {
//                 printk("%02X ", evt->data.rx.buf[evt->data.rx.offset + i]);
//         } */
//         uart_rx_buf_rsp(uart, rx_buf, sizeof(rx_buf));
//         /* if (err)
//         {
//             printk("uart_rx_buf_rsp errored with code %d.\n", err);
//         } */
//         break;

//     case UART_RX_DISABLED:
//         uart_rx_enable(uart, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);
//         break;
//     }
// }

// void uart_reciever(void)
// {
//     // k_msleep(1000);
//     printk("Starting Program..\n");

//     // int ret;

//     // UART
//     if (!device_is_ready(uart))
//     {
//         printk("uart not ready. returning.\n");
//         return;
//     }
//    /*  ret = uart_configure(uart, &uart_cfg);
//     if (ret == -ENOSYS)
//     {
//         return -ENOSYS;
//     } */

//     uart_callback_set(uart, uart_cb, NULL);
//     /* if (ret)
//     {
//         return ret;
//     }
//  */
//     uart_rx_enable(uart, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);
//     /* if (ret)
//     {
//         printk("uart_rx_enable faild with ret=%d\n", ret);
//         return ret;
//     } */

//     // int ctr = 0;
//     /* while (1)
//     {
//             printk("uart0_rx looping... %d\n", ctr);
//             ctr++;

//             k_msleep(SLEEP_TIME_MS);
//     } */
//     return 0;
// }


// #include <zephyr/kernel.h>
// #include <zephyr/drivers/gpio.h>
// #include "stdio.h"
// #include "zephyr/drivers/uart.h"

// const struct device *uart = DEVICE_DT_GET(DT_NODELABEL(uart1));

// static uint8_t tx_buf[] =  {"nRF Connect SDK Fundamentals Course \n\r"};
// static uint8_t rx_buf[10] = {0}; //A buffer to store incoming UART data

// const struct uart_config uart_cfg = {
// 		.baudrate = 115200,
// 		.parity = UART_CFG_PARITY_NONE,
// 		.stop_bits = UART_CFG_STOP_BITS_1,
// 		.data_bits = UART_CFG_DATA_BITS_8,
// 		.flow_ctrl = UART_CFG_FLOW_CTRL_NONE
// 	};

// static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
// {
// 	switch (evt->type) {

// 	case UART_TX_DONE:
// 		printf("transmission complete \n");
// 		break;

// 	case UART_TX_ABORTED:
// 		// do something
// 		break;

// 	case UART_RX_RDY:
// 		printf("rx rdy \n");
// 		if((evt->data.rx.len) != 0){
// 			printf("data received = %s \n", evt->data.rx.buf[evt->data.rx.offset]);
// 		}

// 		break;

// 	case UART_RX_BUF_REQUEST:
// 		printf("requesting buffer \n");
// 		// do something
// 		break;

// 	case UART_RX_BUF_RELEASED:
// 		printf("buffer released \n");
// 		// do something
// 		break;

// 	case UART_RX_DISABLED:
// 		printf("rx disabled \n");
// 		uart_rx_enable(dev, rx_buf, sizeof(rx_buf), 100);
// 		break;

// 	case UART_RX_STOPPED:
// 		// do something
// 		break;

// 	default:
// 		break;
// 	}
// }

// int main(void)
// {

// 	if (!device_is_ready(uart)) {
//     	return;
// 	}

// 	int err;
// 	err = uart_callback_set(uart, uart_cb, NULL);
// 	if (err) {
// 		return err;
// 	}

// 	uart_rx_enable(uart, rx_buf, sizeof(rx_buf), 100);

// 	err = uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_US);
// 	if (err) {
// 		return err;
// 	}

// 	while(1){
// 		k_msleep(1000);
// 	}
// 	return 0;
// }