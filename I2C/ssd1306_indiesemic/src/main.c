// #include <zephyr/kernel.h>
// #include <zephyr/sys/printk.h>
// #include <zephyr/drivers/i2c.h>
// #include <zephyr/devicetree.h>
// // #include <zephyr/drivers/display.h>
// #define SSD1306_I2C_ADDR 0x3C
// #define SSD1306_SETCONTRAST 0x81
// // #define SSD1306_DISPLAYALLON_RESUME 0xA4
// #define SSD1306_DISPLAYALLON 0xA5
// // #define SSD1306_NORMALDISPLAY 0xA6
// // #define SSD1306_INVERTDISPLAY 0xA7
// #define SSD1306_DISPLAYOFF 0xAE
// #define SSD1306_DISPLAYON 0xAF
// // const struct device *dev_i2c = DEVICE_DT_GET(DT_NODELABEL(i2c0));
// #define I2C1_NODE DT_NODELABEL(ssd1306)
// // static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C1_NODE);
// int main(void)
// {

//     const struct device *const i2c_dev = DEVICE_DT_GET(I2C1_NODE);
//     // uint32_t i2c_cfg_tmp;
//     if (!device_is_ready(i2c_dev))
//     {
//         printk("I2C bus is not ready!\n\r");
//         return 0;
//     }
//     unsigned char datas[1];
//     datas[0]= 0xAF;
//     if (i2c_reg_write_byte(i2c_dev, SSD1306_I2C_ADDR, SSD1306_DISPLAYON, 0xAF))
//     {
//         printk("Fail to configure 1 SSD1306\n");
//         // return 0;
//     }
//     k_msleep(500);

//     datas[0]=0x81;
//     if (i2c_write(i2c_dev, datas, 1, SSD1306_I2C_ADDR))
//     {
//         printk("Fail to configure 2 SSD1306\n");
//         // return 0;
//     }
//     /* uint8_t init_seq[] = {SSD1306_DISPLAYOFF, SSD1306_SETCONTRAST, SSD1306_DISPLAYON};
//     int ret_init = i2c_write_dt(&dev_i2c, init_seq, sizeof(init_seq));
//     printk("\r%d\n", ret_init);

//     if (ret_init != 0)
//     {
//         printk("Failed to initialize SSD1306 display.\n");
//         return 0;
//     }

//     uint8_t set_display_config[] = {SSD1306_DISPLAYALLON};
//     int ret_display_config = i2c_write_dt(&dev_i2c, set_display_config, sizeof(set_display_config));
//     printk("\r%d\n", ret_display_config);

//     if (ret_display_config != 0)
//     {
//         printk("Failed to set display configuration.\n");
//         return 0;
//     }

//     uint8_t set_contrast_config[] = {SSD1306_SETCONTRAST};
//     int ret_contrast_config = i2c_write_dt(&dev_i2c, set_contrast_config, sizeof(set_contrast_config));
//     printk("\r%d\n", ret_contrast_config);

//     if (ret_contrast_config != 0)
//     {
//         printk("Failed to set contrast configuration.\n");
//         return 0;
//     } */
//     printk("SSD1306 display turned on and contrast set to maximum\n");
// }

// #include <zephyr/kernel.h>
// #include <zephyr/device.h>
// #include <zephyr/drivers/gpio.h>
// #include <zephyr/drivers/i2c.h>
// // #define I2C_DEV_NAME DT_LABEL(DT_INST(0, nordic_nrf_i2))
// #define SSD1306_ADDR 0x3C
// #define SSD1306_COMMAND_BYTE 0x00
// #define SSD1306_SET_COLUMN_ADDR 0x21
// #define SSD1306_SET_PAGE_ADDR 0x22
// #define SSD1306_WIDTH 128
// #define SSD1306_HEIGHT 64
// /* Function prototypes */
// void ssd1306_write_cmd(const struct device *dev, uint8_t cmd);
// void ssd1306_write_data(const struct device *dev, const uint8_t *data, size_t len);
// void ssd1306_init(const struct device *dev);
// void ssd1306_clear_screen(const struct device *dev);
// void ssd1306_display_string(const struct device *dev, const char *str, uint8_t x, uint8_t y);

// void main(void)
// {
//     const struct device *i2c_dev;
//     i2c_dev = DEVICE_DT_GET(DT_NODELABEL(ssd1306));
//     if (!i2c_is_ready_dt(i2c_dev))
//     {
//         printk("I2C: Device driver not found.\n");
//         return;
//     }
//     ssd1306_init(i2c_dev);
//     ssd1306_display_string(i2c_dev, "indiesemic", 0, 0);
// }
// /* Write a command byte to SSD1306 */
// void ssd1306_write_cmd(const struct device *dev, uint8_t cmd)
// {
//     uint8_t data[] = {SSD1306_COMMAND_BYTE, cmd};
//     i2c_burst_write_dt(dev, SSD1306_ADDR, data, sizeof(data));
// }
// /* Write data bytes to SSD1306 */
// void ssd1306_write_data(const struct device *dev, const uint8_t *data, size_t len)
// {
//     uint8_t buf[len + 1];
//     buf[0] = 0x40; // Data Mode
//     memcpy(&buf[1], data, len);
//     i2c_write(dev, buf, sizeof(buf), SSD1306_ADDR);
// }
// /* Initialize SSD1306 OLED display */
// void ssd1306_init(const struct device *dev)
// {
//     ssd1306_write_cmd(dev, SSD1306_SET_COLUMN_ADDR);  // Set Column Address
//     ssd1306_write_cmd(dev, 0x00);                     // Start Column
//     ssd1306_write_cmd(dev, SSD1306_WIDTH - 1);        // End Column
//     ssd1306_write_cmd(dev, SSD1306_SET_PAGE_ADDR);    // Set Page Address
//     ssd1306_write_cmd(dev, 0x00);                     // Start Page
//     ssd1306_write_cmd(dev, (SSD1306_HEIGHT / 8) - 1); // End Page
//     // Turn on SSD1306
//     ssd1306_write_cmd(dev, 0xAF);
// }
// /* Clear the entire screen of SSD1306 */
// void ssd1306_clear_screen(const struct device *dev)
// {
//     uint8_t data[SSD1306_WIDTH];
//     memset(data, 0x00, sizeof(data));
//     for (int i = 0; i < SSD1306_HEIGHT / 8; i++)
//     {
//         ssd1306_write_data(dev, data, sizeof(data));
//     }
// }
// /* Display a string starting from coordinates (x, y) */
// void ssd1306_display_string(const struct device *dev, const char *str, uint8_t x, uint8_t y)
// {
//     const uint8_t font6x8[] = {
//     // Font data for 'i'
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x7D, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     // Font data for 'n'
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x7C, 0x08, 0x04, 0x04, 0x78, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     // Font data for 'd'
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x7C, 0x04, 0x04, 0x08, 0x7C, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     // Font data for 'e'
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x7C, 0x14, 0x14, 0x14, 0x18, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     // Font data for 's'
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x28, 0x54, 0x54, 0x44, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     // Font data for 'm'
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x7C, 0x08, 0x10, 0x08, 0x7C, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     // Font data for 'i'
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x7D, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     // Font data for 'c'
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x38, 0x44, 0x44, 0x28, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// };

//     ssd1306_clear_screen(dev); // Clear screen
//     uint8_t column = x * 6;    // Each character is 6 columns wide
//     // Write each character
//     while (*str)
//     {
//         for (int i = 0; i < 6; i++)
//         {
//             ssd1306_write_data(dev, &font6x8[(*str - ' ') * 6 + i], 1);
//         }
//         str++;
//         column += 6;
//     }
// }

#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/display.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include<zephyr/drivers/spi.h>
#include "logo.h"
#define DISPLAY_BUFFER_PITCH 128
LOG_MODULE_REGISTER(display);

static const struct device *display = DEVICE_DT_GET(DT_NODELABEL(ssd1306));

int main(void)
{   
    printk("Starting....\n");
    if (display == NULL)
    {
        printk("device pointer is NULL");
        return 0;
    }
    printk("Device pointer test done\n");

    if (!device_is_ready(display))
    {
        printk("display device is not ready");
        return 0;
    }
    printk("Device ready test done\n");

    struct display_capabilities capabilities;
    display_get_capabilities(display, &capabilities);

    printk("display cap done\n");
    const uint16_t x_res = capabilities.x_resolution;
    const uint16_t y_res = capabilities.y_resolution;
   
    const struct display_buffer_descriptor buf_desc = {
        .width = x_res,
        .height = y_res,
        .buf_size = x_res * y_res,
        .pitch = DISPLAY_BUFFER_PITCH};
    
    if (display_write(display, 0, 0, &buf_desc, buf) != 0)
    {
        printk("could not write to display");
    }
    display_set_contrast(display,255);
    display_set_brightness(display,255);
    printk("end\n");
    // if (display_set_contrast(display, 0) != 0)
    // {
    //     LOG_ERR("could not set display contrast");
    // }
    // size_t ms_sleep = 5; 

    // while (true)
    // {
    //     // Increase brightness
    //     for (size_t i = 0; i < 255; i++)
    //     {
    //         display_set_contrast(display, i);
    //         k_sleep(K_MSEC(ms_sleep));
    //     }

    //     // Decrease brightness
    //     for (size_t i = 255; i > 0; i--)
    //     {
    //         display_set_contrast(display, i);
    //         k_sleep(K_MSEC(ms_sleep));
    //     }
    // } 
}