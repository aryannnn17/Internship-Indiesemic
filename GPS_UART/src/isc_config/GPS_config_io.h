#ifndef GPS_CONFIG_IO_H
#define GPS_CONFIG_IO_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

#define HIGH 1
#define LOW 0

// static struct device *gpio_dev;

static const struct gpio_dt_spec CE = GPIO_DT_SPEC_GET(DT_ALIAS(ce), gpios);
// static const struct gpio_dt_spec HIF4 = GPIO_DT_SPEC_GET(DT_ALIAS(pin2), gpios);
// static const struct gpio_dt_spec HIF3 = GPIO_DT_SPEC_GET(DT_ALIAS(pin3), gpios);
// static const struct gpio_dt_spec HIF2 = GPIO_DT_SPEC_GET(DT_ALIAS(pin4), gpios);

static const struct gpio_dt_spec DS_EN = GPIO_DT_SPEC_GET(DT_ALIAS(dsen), gpios);
static const struct gpio_dt_spec DS_STS = GPIO_DT_SPEC_GET(DT_ALIAS(dssts), gpios);
static const struct gpio_dt_spec SYS_READY = GPIO_DT_SPEC_GET(DT_ALIAS(sysready), gpios);
static const struct gpio_dt_spec FIX_OUT = GPIO_DT_SPEC_GET(DT_ALIAS(fixout), gpios);
static const struct gpio_dt_spec AUTO_START = GPIO_DT_SPEC_GET(DT_ALIAS(autostart), gpios);
static const struct gpio_dt_spec EPPS_OUT = GPIO_DT_SPEC_GET(DT_ALIAS(eppsout), gpios);
static const struct gpio_dt_spec IF_CTRL = GPIO_DT_SPEC_GET(DT_ALIAS(ifctrl), gpios);
static const struct gpio_dt_spec nRESET = GPIO_DT_SPEC_GET(DT_ALIAS(nreset), gpios);

int GPIO_INIT(void);
// void GPIO_INIT(void);

uint8_t eps_init(void);

void DS_EN_CONFIG(void);
void DS_STS_CONFIG(void);
void SYS_READY_CONFIG(void);
void FIX_OUT_CONFIG(void);
void AUTO_START_CONFIG(void);
void EPPS_OUT_CONFIG(void);
void IF_CTRL_CONFIG(void);
void nRESET_CONFIG(void);

#endif  // CONFIG_H
