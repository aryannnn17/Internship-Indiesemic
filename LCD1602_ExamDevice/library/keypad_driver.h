#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>

#ifndef __KEYPAD_DRIVER_H__
#define __KEYPAD_DRIVER_H__

static const struct gpio_dt_spec R0_4x4 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x4_row0), gpios);
static const struct gpio_dt_spec R1_4x4 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x4_row1), gpios);
static const struct gpio_dt_spec R2_4x4 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x4_row2), gpios);
static const struct gpio_dt_spec R3_4x4 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x4_row3), gpios);
static const struct gpio_dt_spec C0_4x4 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x4_col0), gpios);
static const struct gpio_dt_spec C1_4x4 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x4_col1), gpios);
static const struct gpio_dt_spec C2_4x4 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x4_col2), gpios);
static const struct gpio_dt_spec C3_4x4 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x4_col3), gpios);

static const struct gpio_dt_spec R0_4x1 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x1_row0), gpios);
static const struct gpio_dt_spec C0_4x1 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x1_col0), gpios);
static const struct gpio_dt_spec C1_4x1 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x1_col1), gpios);
static const struct gpio_dt_spec C2_4x1 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x1_col2), gpios);
static const struct gpio_dt_spec C3_4x1 = GPIO_DT_SPEC_GET(DT_ALIAS(kpd4x1_col3), gpios);

int GPIO_config(void);
char read_keypad(void);

#endif /* __KEYPAD_DRIVER_H__ */