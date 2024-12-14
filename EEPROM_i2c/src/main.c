#include <zephyr/kernel.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>

const struct i2c_dt_spec dev = I2C_DT_SPEC_GET(DT_NODELABEL(eeprom));

int main()
{
        if (!device_is_ready(dev.bus))
        {
                printk("\nError: Device is not ready, check the driver initialization logs for errors.\n");
                return 0;
        }
        printk("Found EEPROM device\n");

        int ret;
        // char data[]="Hello";
        uint8_t data_to_write[3] = {0x00, 0x00 ,0x44};
        int data_length = sizeof(data_to_write);
        ret = i2c_reg_write_byte_dt(&dev, 0x0004, 0x34);
        if (ret != 0)
        {
                printk("Failed to write to I2C device address\n ");
        }
        printk("Write Succesfully\n");
        k_msleep(10);
        
        // uint8_t msg[] = {'h', 'e', 'l', 'l', 'o', '\0'};
        // ret = i2c_burst_write_dt(&dev,0x00,msg,sizeof(msg));
        // uint8_t data_to_c_write[3] = {0x00, 0x00, msg};
        // int data_c_length = sizeof(data_to_c_write);
        // ret = i2c_write_dt(&dev, data_to_c_write, data_c_length);
        // if (ret != 0)
        // {
        //         printk("Failed to write to I2C device address\n ");
        // }
        // printk("Write Succesfully w\n");
        // k_msleep(10);
        
        uint8_t data_to_r_write[2] = {0x00, 0x00};
        int data_r_length = sizeof(data_to_r_write);
        ret = i2c_write_dt(&dev, data_to_r_write, data_r_length);
        if (ret != 0)
        {
                printk("Failed to write to I2C device address\n ");
        }
        printk("Write Succesfully to r\n");
        k_msleep(10);
        uint8_t data_read[sizeof(data_to_write)];
        // int data_l = sizeof(data_read);
        i2c_reg_read_byte_dt(&dev,0x0004,data_read);
        // ret = i2c_read_dt(&dev,data_read, sizeof(data_read));
        if (ret != 0)
        {
                printk("Failed to read from I2C device address\n\r");
        }
        // data_read[sizeof(data_read) - 1] = '\0'; // Null-terminate the string
        printk("Read data: %x\n", *data_read);
        return 0;
}
