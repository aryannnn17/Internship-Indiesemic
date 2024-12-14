/*  keypad_driver.c */
#include "keypad_driver.h"

int GPIO_config(void)
{
	int ret;
	ret = gpio_pin_configure_dt(&R0_4x4, GPIO_OUTPUT);
	if (ret < 0)
	{
		return 1;
	}
	ret = gpio_pin_configure_dt(&R1_4x4, GPIO_OUTPUT);
	if (ret < 0)
	{
		return 1;
	}
	ret = gpio_pin_configure_dt(&R2_4x4, GPIO_OUTPUT);
	if (ret < 0)
	{
		return 1;
	}
	ret = gpio_pin_configure_dt(&R3_4x4, GPIO_OUTPUT);
	if (ret < 0)
	{
		return 1;
	}

	ret = gpio_pin_configure_dt(&C0_4x4, GPIO_INPUT | GPIO_PULL_UP);
	if (ret < 0)
	{
		return 1;
	}
	ret = gpio_pin_configure_dt(&C1_4x4, GPIO_INPUT | GPIO_PULL_UP);
	if (ret < 0)
	{
		return 1;
	}
	ret = gpio_pin_configure_dt(&C2_4x4, GPIO_INPUT | GPIO_PULL_UP);
	if (ret < 0)
	{
		return 1;
	}
	ret = gpio_pin_configure_dt(&C3_4x4, GPIO_INPUT | GPIO_PULL_UP);
	if (ret < 0)
	{
		return 1;
	}

	
	ret = gpio_pin_configure_dt(&R0_4x1, (GPIO_OUTPUT));
	if (ret < 0)
	{
		return 1;
	}
	
	ret = gpio_pin_configure_dt(&C0_4x1, (GPIO_INPUT | GPIO_PULL_UP));
	if (ret < 0)
	{
		return 1;
	}
	ret = gpio_pin_configure_dt(&C1_4x1, (GPIO_INPUT | GPIO_PULL_UP));
	if (ret < 0)
	{
		return 1;
	}
	ret = gpio_pin_configure_dt(&C2_4x1, (GPIO_INPUT | GPIO_PULL_UP));
	if (ret < 0)
	{
		return 1;
	}
	ret = gpio_pin_configure_dt(&C3_4x1, (GPIO_INPUT | GPIO_PULL_UP));
	if (ret < 0)
	{
		return 1;
	}
}

char read_keypad(void)
{
	/* Make ROW 1 LOW and all other ROWs HIGH */
	gpio_pin_set_dt(&R0_4x4, 0); // Pull the R1 low
	gpio_pin_set_dt(&R1_4x4, 1); // Pull the R2 High
	gpio_pin_set_dt(&R2_4x4, 1); // Pull the R3 High
	gpio_pin_set_dt(&R3_4x4, 1); // Pull the R4 High

	if (!(gpio_pin_get_dt(&C0_4x4))) // if the Col 1 is low
	{
		while (!(gpio_pin_get_dt(&C0_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("1");
		return '1';
	}

	if (!(gpio_pin_get_dt(&C1_4x4))) // if the Col 2 is low
	{
		while (!(gpio_pin_get_dt(&C1_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("2");
		return '2';
	}

	if (!(gpio_pin_get_dt(&C2_4x4))) // if the Col 3 is low
	{
		while (!(gpio_pin_get_dt(&C2_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("3");
		return '3';
	}

	if (!(gpio_pin_get_dt(&C3_4x4))) // if the Col 4 is low
	{
		while (!(gpio_pin_get_dt(&C3_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("A");
		return 'A';
	}

	/* Make ROW 2 LOW and all other ROWs HIGH */

	gpio_pin_set_dt(&R0_4x4, 1); // Pull the R1 low
	gpio_pin_set_dt(&R1_4x4, 0); // Pull the R2 High
	gpio_pin_set_dt(&R2_4x4, 1); // Pull the R3 High
	gpio_pin_set_dt(&R3_4x4, 1); // Pull the R4 High

	if (!(gpio_pin_get_dt(&C0_4x4))) // if the Col 1 is low
	{
		while (!(gpio_pin_get_dt(&C0_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("4");
		return '4';
	}

	if (!(gpio_pin_get_dt(&C1_4x4))) // if the Col 2 is low
	{
		while (!(gpio_pin_get_dt(&C1_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("5");
		return '5';
	}

	if (!(gpio_pin_get_dt(&C2_4x4))) // if the Col 3 is low
	{
		while (!(gpio_pin_get_dt(&C2_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("6");
		return '6';
	}

	if (!(gpio_pin_get_dt(&C3_4x4))) // if the Col 4 is low
	{
		while (!(gpio_pin_get_dt(&C3_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("B");
		return 'B';
	}

	/* Make ROW 3 LOW and all other ROWs HIGH */

	gpio_pin_set_dt(&R0_4x4, 1); // Pull the R1 low
	gpio_pin_set_dt(&R1_4x4, 1); // Pull the R2 High
	gpio_pin_set_dt(&R2_4x4, 0); // Pull the R3 High
	gpio_pin_set_dt(&R3_4x4, 1); // Pull the R4 High

	if (!(gpio_pin_get_dt(&C0_4x4))) // if the Col 1 is low
	{
		while (!(gpio_pin_get_dt(&C0_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("7");
		return '7';
	}

	if (!(gpio_pin_get_dt(&C1_4x4))) // if the Col 2 is low
	{
		while (!(gpio_pin_get_dt(&C1_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("8");
		return '8';
	}

	if (!(gpio_pin_get_dt(&C2_4x4))) // if the Col 3 is low
	{
		while (!(gpio_pin_get_dt(&C2_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("9");
		return '9';
	}

	if (!(gpio_pin_get_dt(&C3_4x4))) // if the Col 4 is low
	{
		while (!(gpio_pin_get_dt(&C3_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("C");
		return 'C';
	}

	/* Make ROW 4 LOW and all other ROWs HIGH */

	gpio_pin_set_dt(&R0_4x4, 1); // Pull the R1 low
	gpio_pin_set_dt(&R1_4x4, 1); // Pull the R2 High
	gpio_pin_set_dt(&R2_4x4, 1); // Pull the R3 High
	gpio_pin_set_dt(&R3_4x4, 0); // Pull the R4 High

	if (!(gpio_pin_get_dt(&C0_4x4))) // if the Col 1 is low
	{
		while (!(gpio_pin_get_dt(&C0_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("*");
		return '*';
	}

	if (!(gpio_pin_get_dt(&C1_4x4))) // if the Col 1 is low
	{
		while (!(gpio_pin_get_dt(&C1_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("0");
		return '0';
	}

	if (!(gpio_pin_get_dt(&C2_4x4))) // if the Col 3 is low
	{
		while (!(gpio_pin_get_dt(&C2_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("#");
		return '#';
	}

	if (!(gpio_pin_get_dt(&C3_4x4))) // if the Col 4 is low
	{
		while (!(gpio_pin_get_dt(&C3_4x4)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("D");
		return 'D';
	}


	if (!(gpio_pin_get_dt(&C0_4x1))) // if the Col 1 is low
	{
		while (!(gpio_pin_get_dt(&C0_4x1)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("1");
		return 'E';
	}

	if (!(gpio_pin_get_dt(&C1_4x1))) // if the Col 2 is low
	{
		while (!(gpio_pin_get_dt(&C1_4x1)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("2");
		return 'P';
	}

	if (!(gpio_pin_get_dt(&C2_4x1))) // if the Col 3 is low
	{
		while (!(gpio_pin_get_dt(&C2_4x1)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("3");
		return 'N';
	}

	if (!(gpio_pin_get_dt(&C3_4x1))) // if the Col 4 is low
	{
		while (!(gpio_pin_get_dt(&C3_4x1)))
			k_sleep(K_USEC(100)); // wait till the button is pressed
		printk("4");
		return 'V';
	}
}
