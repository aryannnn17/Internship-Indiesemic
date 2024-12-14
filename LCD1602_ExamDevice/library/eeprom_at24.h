#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>


#ifndef __EEPROM_AT24_H__
#define __EEPROM_AT24_H__

static const struct i2c_dt_spec eeprom_dev = I2C_DT_SPEC_GET(DT_ALIAS(eeprom_0));
static const struct gpio_dt_spec eeprom_wp = GPIO_DT_SPEC_GET(DT_ALIAS(eeprom_wp), gpios);

/**
 * @brief Initilizes peripherals
*/
int eeprom_init(void);
/**
 * @brief API to write data to EEPROM
 * @param address 16 bit page address
 * @param data pointer to data to be saved to EEPROM
 * @param length length of data
*/
int i2c_eeprom_write(uint16_t address, uint8_t *data, uint8_t length);
/**
 * @brief API to read data from EEPROM
 * @param address 16 bit page address
 * @param data pointer to variable where data is to be stored
 * @param length length of data to be read
*/
int i2c_eeprom_read(uint16_t address, uint8_t *data, uint8_t length);

#endif /* __EEPROM_AT24_H__ */