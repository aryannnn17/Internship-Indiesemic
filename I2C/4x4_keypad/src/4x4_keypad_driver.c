#include "4x4_keypad_driver.h"
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

const struct {} buttons_def_include_once;

static const struct gpio_dt_spec col[] = {
	//4x4 keypad col GPIO (1,4 | 1,3 | 1,2 | 1,1) as per overlay file
	{ .port = 1, .pin = DT_GPIO_PIN(DT_NODELABEL(col1), gpios) },
	{ .port = 1, .pin = DT_GPIO_PIN(DT_NODELABEL(col2), gpios) },
	{ .port = 1, .pin = DT_GPIO_PIN(DT_NODELABEL(col3), gpios) },
	{ .port = 1, .pin = DT_GPIO_PIN(DT_NODELABEL(col4), gpios) },

};

static const struct gpio_dt_spec row[] = {
	//4x4 keypad rows GPIO (1,8 | 1,7 | 1,6 | 1,5) as per overlay file
	{ .port = 1, .pin = DT_GPIO_PIN(DT_NODELABEL(row1), gpios) },
	{ .port = 1, .pin = DT_GPIO_PIN(DT_NODELABEL(row2), gpios) },
	{ .port = 1, .pin = DT_GPIO_PIN(DT_NODELABEL(row3), gpios) },
	{ .port = 1, .pin = DT_GPIO_PIN(DT_NODELABEL(row4), gpios) },
};