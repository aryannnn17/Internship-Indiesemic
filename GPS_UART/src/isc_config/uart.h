#ifndef UART_H
#define UART_H

#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


#define BUFF_SIZE 500
#define RECEIVE_TIMEOUT 100

//--------------------------------uart--------------------------------
static const struct device *uart = DEVICE_DT_GET(DT_NODELABEL(uart0));


static uint8_t tx_buf[] =   {"UART Driver Test for communication btwn GPS and Nordik\n"};

extern uint8_t tx_buf2[100];

extern uint8_t Rxbuf[BUFF_SIZE];


/* uart_cb function is callback function used for handling 
UART (Universal Asynchronous Receiver-Transmitter) events. 
This function gets called when certain events related to UART occur.

Here's a breakdown of its parameters and what it does:

const struct device *dev: This parameter likely represents the UART device that triggered the event. 
It contains information about the UART hardware being used.


struct uart_event *evt: This parameter represents the UART event that occurred. 
The structure uart_event likely contains information about the type of event and possibly additional data associated with it. 
Common UART events include receiving data, transmitting data, errors in transmission or reception, and others.

void *user_data: This parameter is a pointer to user-defined data that can be passed to the callback function. 
It allows users to provide additional context or data to the callback function if needed.

This function to handle UART events according to the requirements of your application. 
For example, if you're receiving data over UART, you might process the received data or trigger other actions based on the content of the data. 
If you're transmitting data, you might monitor the transmission status or handle any errors that occur during transmission.

Overall, uart_cb is a callback function used to handle UART events and is an essential part of implementing UART communication in nRF-based applications.

*/

void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data);

								

#endif  // CONFIG_H
