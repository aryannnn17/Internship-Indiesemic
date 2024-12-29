
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>


#include "uart.h"
#include "cmd.h"
#include "GPS_config_io.h"
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <stdarg.h>

#define SLEEP_TIME_MS 1000


int main(void)
{
	int ret,err;


	printk("COMMUNICATION START for GPS with Nordic DK\r\n");
		

	const struct uart_config uart_cfg = {
		.baudrate  = 115200,
		.parity    = UART_CFG_PARITY_NONE,
		.stop_bits = UART_CFG_STOP_BITS_1, 
		.data_bits = UART_CFG_DATA_BITS_8, 
		.flow_ctrl = UART_CFG_FLOW_CTRL_NONE
	};

	
	err = uart_configure(uart, &uart_cfg); 

	    if (!device_is_ready(IF_CTRL.port))
        {
                printk("GPIO device is not ready\r\n");
                return 1;
        }

		ret = gpio_pin_configure_dt(&DS_EN, GPIO_INPUT | GPIO_ACTIVE_HIGH | GPIO_PULL_UP);
        if (ret < 0)
        {
                return 1;
        }
		ret = gpio_pin_configure_dt(&IF_CTRL, GPIO_INPUT |  GPIO_PULL_DOWN);
        if (ret < 0)
        {
                return 1;
        }

		// ret = gpio_pin_configure_dt(&AUTO_START, GPIO_INPUT |  GPIO_ACTIVE_HIGH | GPIO_PULL_UP);
        // if (ret < 0)
        // {
        //         return 1;
        // }

		ret = gpio_pin_configure_dt(&AUTO_START, GPIO_OUTPUT );
        if (ret < 0)
        {
                return 1;
        }

		ret = gpio_pin_configure_dt(&nRESET, GPIO_OUTPUT );
        if (ret < 0)
        {
                return 1;
        }

	if (!device_is_ready(uart)){
		printk("UART device not ready\r\n");
		return 1 ;
	}

	
	gpio_pin_set_dt(&DS_EN,HIGH);

	gpio_pin_set_dt(&IF_CTRL,LOW);

	gpio_pin_set_dt(&nRESET,HIGH);

	gpio_pin_set_dt(&AUTO_START,LOW);
	

	ret = uart_callback_set(uart, uart_cb, NULL);
	if (ret) {
		return ret;
	}


	k_msleep(1000);

	// ret = uart_rx_enable(uart ,Rxbuf,sizeof(Rxbuf),SYS_FOREVER_US);
	// if (ret)
	// {
	// 	printk("uart_rx_enable failed with ret=%d\n", ret);
	// 	return ret;
	// }


	//  firmware for E65 GPS 

	// gps_auto_start();
	
	// gps_baudrate_cmd("115200");

	// gps_check_version_cmd('0');

	gps_start_cmd('C','0');

	// gps_stop_cmd('0');

	// gps_reset_cmd('0');

	// gps_gns_cmd('0','0');

	// gps_pps_cmd('0','0',"-1000");

	// gps_msk_cmd('0',"10");

	// gps_nmea_cmd("GGA",'0');

	// gps_enm_cmd('0');

	// gps_init_pos_cmd('0',"36","137","-10","5");

	// gps_set_time_cmd('0',"070615","14","02","2024");

	// gps_sls_cmd("16",'M');

	// gps_clr_cmd('1');

	// gps_sav_cmd('1');

	// gps_hwc_cmd('0','0','0');

	// gps_icf_cmd("ALL");

	// gps_ibe_cmd("000000","01","01","0001",'0',"0","0","0","0");

	// gps_qzs_cmd("0047");

	// gps_psm_cmd('1','0','0','0','0');
	
    return 0;

}




