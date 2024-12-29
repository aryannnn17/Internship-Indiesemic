#include "uart.h"

uint8_t Rxbuf[BUFF_SIZE]= {0};
uint8_t tx_buf2[100] = {0};

void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
	int ret = 0; 
	switch (evt->type) {


		case UART_RX_RDY:

		int i = 0; 
		uint8_t temp = 0; 
		uint8_t length = evt->data.rx.len; 

		// for(i = 0; i<evt->data.rx.len; i++)
		// {
		// 	temp = evt->data.rx.buf[evt->data.rx.offset + i];
		// 	tx_buf2[i] = temp; 
		// }

		// ret = uart_tx(uart ,tx_buf2,sizeof(tx_buf2),RECEIVE_TIMEOUT);  //echo uart
		
		

		for (int i=0; i < evt->data.rx.len; i++) 
		{
			// printk("%02X ", evt->data.rx.buf[evt->data.rx.offset + i]);
			printk("%c", evt->data.rx.buf[evt->data.rx.offset + i]);
		}


		break;

	case UART_RX_DISABLED:
	uart_rx_enable(uart ,Rxbuf,sizeof(Rxbuf),SYS_FOREVER_US);
		break;
		
	default:
		break;
	}
}




