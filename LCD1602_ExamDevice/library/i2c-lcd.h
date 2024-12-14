#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>

#ifndef __I2C_LCD_H__
#define __I2C_LCD_H__



static const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));

void lcd_init(void); // initialize lcd

void lcd_send_cmd(char cmd); // send command to the lcd

void lcd_send_data(char data); // send data to the lcd

void lcd_send_string(char *str); // send string to the lcd

void lcd_put_cur(int row, int col); // put cursor at the entered position row (0 or 1), col (0-15);

void lcd_clear(void);

void lcd_scroll_string(char *str);

void scrollText(char *str);


#endif /* __I2C_LCD_H__ */
