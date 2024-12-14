#include "eeprom_at24.h"

int eeprom_init(void)
{
    if (!i2c_is_ready_dt(&eeprom_dev))
    {
        printk("eeprom not ready!");
        return -1;
    }
    if (!gpio_is_ready_dt(&eeprom_wp))
    {
        printk("gpio is not ready");
        return -1;
    }

    int ret = gpio_pin_configure_dt(&eeprom_wp, (GPIO_OUTPUT));
    if (ret)
    {
        return ret;
    }

    gpio_pin_set_dt(&eeprom_wp, 1);
    return 0;
}

int i2c_eeprom_write(uint16_t address, uint8_t *data, uint8_t length)
{
    gpio_pin_set_dt(&eeprom_wp, 0);
    uint8_t buf[3 + length];
    buf[0] = 0x00;
    buf[1] = (uint8_t)address >> 8;
    buf[2] = (uint8_t)address;
    memcpy(&buf[3], data, length);
    int err = i2c_write_dt(&eeprom_dev, buf, sizeof(buf));
    if (err)
    {
        return err;
    }
    gpio_pin_set_dt(&eeprom_wp, 1);
    return 0;
}

int i2c_eeprom_read(uint16_t address, uint8_t *data, uint8_t length)
{
    uint8_t buf[3];
    buf[0] = 0x00;
    buf[1] = (uint8_t)address >> 8;
    buf[2] = (uint8_t)address;
    int err = i2c_write_dt(&eeprom_dev, buf, sizeof(buf));
    if (err)
    {
        return err;
    }
    k_sleep(K_MSEC(10));
    err = i2c_read_dt(&eeprom_dev, data, length);
    if (err)
    {
        return err;
    }
    return 0;
}