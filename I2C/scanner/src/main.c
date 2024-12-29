#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>

const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));

int main()
{
	printk("The I2C scanner started\n");
	int error;
	if (!device_is_ready(i2c_dev))
	{
		printk("I2C device is not ready\r\n");
		return 0;
	}

	int count = 0;
	for (uint8_t i = 0x01; i <= 0x7F; i++)
	{
		struct i2c_msg msgs[1];
		uint8_t dst;

		msgs[0].buf = &dst;
		msgs[0].len = 0U;
		msgs[0].flags = I2C_MSG_READ | I2C_MSG_STOP;

		error = i2c_transfer(i2c_dev, &msgs[0], 1, i);
		if (error == 0)
		{
			printk("0x%2x FOUND\n", i);
			// printk("%d FOUND\n", i);
			count++;
		}
		k_msleep(100);
	}
	printk("%d devices found on the bus\n", count);
}
/* 
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>																						
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));

int main()
{
	printk("The I2C scanner started\n");
	int error;
	if (!device_is_ready(i2c_dev))
	{
		printk("I2C device is not ready\r\n");
		return 0;
	}
	// int count = 0;
	uint8_t data = {0};
	for (uint8_t i = 1; i <= 127; i++)
	{
		error = i2c_read(i2c_dev, &data, 1 ,i);
		if (error == 0)
		{
			printk("I2C device address %d \n\r", i2c_dev);
		}
	}
} */
	/*
	#include <zephyr/kernel.h>
	#include <zephyr/sys/printk.h>
	#include <zephyr/drivers/i2c.h>

	// #define MY_I2C DT_ALIAS(i2c0)

	void scan_i2c_bus(const struct device *dev, int i2cbus)
	{
		printk(" Scanning I2C_%u bus: \n", i2cbus);

		for (uint8_t addr = 0; addr < 128; addr++)
		{
			struct i2c_msg msg = {
					.buf = NULL,
					.len = 0,
					.flags = I2C_MSG_WRITE};

			int ret = i2c_transfer(dev, &msg, 1, addr);
			if (ret == 0)
				printk("Found device at address 0x%2x \n", addr);
		}
	}

	void main(void){
		const struct device *devi2c = DEVICE_DT_GET(DT_NODELABEL(i2c0));
		if (!devi2c)
		{
			printk("Could not get I2C device\n");
			return;
		}
		scan_i2c_bus(devi2c, 1);
	} */