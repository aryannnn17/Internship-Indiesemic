#include <zephyr/kernel.h>
#include "uart_driver.h"
#include <zephyr/drivers/gpio.h>
#include "zephyr/drivers/uart.h"

int main(void)
{
        uart_transmit();
        printk("uart_tx exited\r\n\n");
        return 0;
}
