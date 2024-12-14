
/** Put this in the src folder **/

#include "i2c-lcd.h"
#include "keypad_driver.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define SLAVE_ADDRESS_LCD 0x27 // change this according to ur setup

// void lcd_pulse(void)
// {
// 	uint8_t data = 0x20;
// 	i2c_write(i2c_dev, &data, sizeof(data), SLAVE_ADDRESS_LCD);
// 	return;
// }

// void lcd_send4bits(uint8_t value)
// {
// 	uint8_t data = value & 0x0F;
// 	i2c_write(i2c_dev, &data, sizeof(data), SLAVE_ADDRESS_LCD);
// 	lcd_pulse();
// 	return;
// }

void lcd_send_cmd(char cmd) // changed from char to uint8_t
{
	
	char data_u, data_l;
	uint8_t data_t[4];

	data_u = (cmd & 0xf0);
	data_l = ((cmd << 4) & 0xf0);

	data_t[0] = data_u | 0x0C; // en=1, rs=0
	data_t[1] = data_u | 0x08; // en=0, rs=0
	data_t[2] = data_l | 0x0C; // en=1, rs=0
	data_t[3] = data_l | 0x08; // en=0, rs=0

	i2c_write(i2c_dev, (uint8_t *)data_t, sizeof(data_t), SLAVE_ADDRESS_LCD); 
	
	// uint8_t data = cmd & 0x80;
	// lcd_send4bits(data >> 4);
	// lcd_send4bits(data & 0x0F);
	return;
}

void lcd_send_data(char data)
{
	char data_u, data_l;
	uint8_t data_t[4];

	data_u = (data & 0xf0);
	data_l = ((data << 4) & 0xf0);
	data_t[0] = data_u | 0x0D;
	data_t[1] = data_u | 0x09;
	data_t[2] = data_l | 0x0D;
	data_t[3] = data_l | 0x09;

	i2c_write(i2c_dev, (uint8_t *)data_t, sizeof(data_t), SLAVE_ADDRESS_LCD);
}

void lcd_clear(void)
{
	// lcd_send_cmd(0x80);
	// for (int i = 0; i < 70; i++)
	// {
	// 	lcd_send_data(' ');
	// }
	lcd_send_cmd(0x01);
	k_sleep(K_USEC(100));
}

void lcd_put_cur(int row, int col)
{
	uint8_t position;

    if (row == 0)
        position = 0x80 + col; 
    else if (row == 1)
        position = 0xC0 + col;
    
	lcd_send_cmd(position);
	k_sleep(K_MSEC(100));
}

void lcd_init(void)
{
	// 4 bit initialisation
	k_msleep(50); // wait for >40ms
	lcd_send_cmd(0x30);
	k_msleep(5); // wait for >4.1ms
	lcd_send_cmd(0x30);
	k_msleep(1); // wait for >100us
	lcd_send_cmd(0x30);
	k_msleep(10);
	lcd_send_cmd(0x20); // 4bit mode
	k_msleep(10);

	// dislay initialisation
	lcd_send_cmd(0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	k_msleep(1);
	lcd_send_cmd(0x08); // Display on/off control --> D=0,C=0, B=0  ---> display off
	k_msleep(1);
	lcd_send_cmd(0x01); // clear display
	k_msleep(1);
	k_msleep(1);
	lcd_send_cmd(0x06); // Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	k_msleep(1);
	lcd_send_cmd(0x0C); // Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_send_string(char *str)
{
	while (*str)
	{
		lcd_send_data(*str++);
	}
	k_sleep(K_MSEC(10));
	
}

void lcd_scroll_string(char *str)
{

	int i = 0;

	while (str[i] != '\0')
	{
		lcd_send_data(str[i]);

		if (i >= 14)
		{
			lcd_send_cmd(0x18); // Scrolling text to Right
		}
		k_msleep(50);
		i++;
	}
}

void scrollText(char *str)
{
	int len = strlen(str);
	int i;
	for (i = 0; i < len + 16; i++)
	{
		// lcd_clear();
		// lcd.setCursor(0, 0);
		lcd_send_data(str + i);
		k_msleep(500); // Adjust delay time for desired scrolling speed
	}
}



void enter_digit(int digit_count)
{

	char input[4] = {0};
	// int digit_count = 0;

	char key = read_keypad();

	if (key >= '0' && key <= '9')
	{
		if (digit_count < 3)
		{
			input[digit_count++] = key;
			lcd_send_cmd(0xC0);
			lcd_send_cmd(0x0E);
			lcd_send_string(input);
		}
	}
	else if (key == '#')
	{
		input[digit_count] = '\0';
		digit_count = 0;
		lcd_send_string(input);
		k_msleep(2000);
		lcd_send_cmd(0x01);

		printk("key value:%c ,input value %s\n", key, input);
	}
}