// #include <zephyr/kernel.h>
// #include <zephyr/drivers/gpio.h>
// // #include "stdio.h"
// #include "zephyr/drivers/uart.h"

// const struct device *uart = DEVICE_DT_GET(DT_NODELABEL(uart1));

// static uint8_t tx_buf[] =  {"nRF Connect SDK Fundamentals Course \n\r"};
// static uint8_t rx_buf[50] = {0}; //A buffer to store incoming UART data 

// const struct uart_config uart_cfg = {
// 		.baudrate = 9600,
// 		.parity = UART_CFG_PARITY_NONE,
// 		.stop_bits = UART_CFG_STOP_BITS_1,
// 		.data_bits = UART_CFG_DATA_BITS_8,
// 		.flow_ctrl = UART_CFG_FLOW_CTRL_NONE
// 	};

// static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
// {
// 	switch (evt->type) {
// 	/* 
// 	case UART_TX_DONE:
// 		printf("transmission complete \n");
// 		break;

// 	case UART_TX_ABORTED:
// 		// do something
// 		break; */
		
// 	case UART_RX_RDY:
// 		// printf("rx rdy \n");
// 		// if((evt->data.rx.len) != 0){
// 		printf("data received from 1 = %s \n",evt->data.rx.buf);
// 		printf("data received from 2 = %s \n",rx_buf);
// 		// }
// 		break;

// 	case UART_RX_BUF_REQUEST:
// 		printf("requesting buffer \n");
// 		// do something
// 		break;
// /* 
// 	case UART_RX_BUF_RELEASED:
// 		printf("buffer released \n");
// 		// do something
// 		break;
// 		 */
// 	case UART_RX_DISABLED:
// 		// printf("rx disabled \n");
// 		uart_rx_enable(dev, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);
// 		break;
// /* 
// 	case UART_RX_STOPPED:
// 		// do something
// 		break;
// 		 */
// 	default:
// 		break;
// 	}
// }


// void uart_receiver()
// {	
//     k_msleep(500);
// 	if (!device_is_ready(uart)) {
//     	return;
// 	}

// 	int err;
// 	err = uart_callback_set(uart, uart_cb, NULL);
// 	if (err) {
// 		return err;
// 	}

// 	uart_rx_enable(uart, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);

// /* 
// 	err = uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_US);
// 	if (err) {
// 		return err;
// 	} */


// /* 
// 	while(1){
// 		k_msleep(1000);
// 	} */
// 	return 0;
// }























































// /* #include <zephyr/kernel.h>
// #include <zephyr/drivers/gpio.h>
// #include "zephyr/drivers/uart.h"
// #include "uart_driver.h"

// const struct device *uart = DEVICE_DT_GET(DT_NODELABEL(uart1));

// static uint8_t tx_buf[] = {"Hello! Welcome to IndieSemiC Pvt Ltd!!\r\n"};
// static uint8_t rx_buf[50] = {0};

// const struct uart_config uart_cfg = {
//     .baudrate = 115200,
//     .parity = UART_CFG_PARITY_NONE,
//     .stop_bits = UART_CFG_STOP_BITS_1,
//     .data_bits = UART_CFG_DATA_BITS_8,
//     .flow_ctrl = UART_CFG_FLOW_CTRL_NONE};

// void uart_transmit()
// {
//     if (!device_is_ready(uart))
//     {
//         return 0;
//     }

//     uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_US);

//     while (1)
//     {
//         k_msleep(1000);
//     }
// }

// static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
// {
//     switch (evt->type)
//     {
//     case UART_RX_RDY:
//         printf("rx rdy \n");
//         printk("data received = %s \n", evt->data.rx_buf);
//         break;

//     case UART_RX_BUF_REQUEST:
//         break;

//     case UART_RX_DISABLED:
//         printf("rx disabled \n");
//         uart_rx_enable(dev, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);
//         break;

//     default:
//         break;
//     }
// }

// void uart_receiver()
// {
//     printk("Hi!\r\n");
//     if (!device_is_ready(uart))
//     {
//         return 0;
//     }

//     uart_callback_set(uart, uart_cb, NULL);
//     uart_rx_enable(uart, rx_buf, sizeof(rx_buf), SYS_FOREVER_US);
//     // uart_tx(uart, tx_buf, sizeof(tx_buf), SYS_FOREVER_US);

//     while (1)
//     {
//         k_msleep(1000);
//     }
//     return 0;
// } */


// /*
//  * Copyright (c) 2012-2014 Wind River Systems, Inc.
//  *
//  * SPDX-License-Identifier: Apache-2.0
//  */
