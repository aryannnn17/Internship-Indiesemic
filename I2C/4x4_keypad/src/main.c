#include <zephyr/kernel.h>
#include "4x4_keypad_driver.h"
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

// static const struct gpio_dt_spec row1 = GPIO_DT_SPEC_GET(DT_NODELABEL(row1), gpios);
// static const struct gpio_dt_spec row2 = GPIO_DT_SPEC_GET(DT_NODELABEL(row2), gpios);
// static const struct gpio_dt_spec row3 = GPIO_DT_SPEC_GET(DT_NODELABEL(row3), gpios);
// static const struct gpio_dt_spec row4 = GPIO_DT_SPEC_GET(DT_NODELABEL(row4), gpios);
// static const struct gpio_dt_spec col1 = GPIO_DT_SPEC_GET(DT_NODELABEL(col1), gpios);
// static const struct gpio_dt_spec col2 = GPIO_DT_SPEC_GET(DT_NODELABEL(col2), gpios);
// static const struct gpio_dt_spec col3 = GPIO_DT_SPEC_GET(DT_NODELABEL(col3), gpios);
// static const struct gpio_dt_spec col4 = GPIO_DT_SPEC_GET(DT_NODELABEL(col4), gpios);

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
static struct gpio_callback button_cb_data;

void button_pressed(const struct device *dev, struct gpio_callback *cb,uint32_t pins)
{
	printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
}

int keypad_4x4(void)
{
    int val1;
    if (!device_is_ready(row[0].port))
    {
        printk("Bus is not ready\r\n");
        return 0;
    }

    gpio_pin_configure_dt(&col[0], GPIO_OUTPUT);
    gpio_pin_configure_dt(&col[1], GPIO_OUTPUT);
    gpio_pin_configure_dt(&col[2], GPIO_OUTPUT);
    gpio_pin_configure_dt(&col[3], GPIO_OUTPUT);
    gpio_pin_configure_dt(&row[1], GPIO_INPUT | GPIO_PULL_DOWN);
    gpio_pin_configure_dt(&row[2], GPIO_INPUT | GPIO_PULL_DOWN);
    gpio_pin_configure_dt(&row[3], GPIO_INPUT | GPIO_PULL_DOWN);
    gpio_pin_configure_dt(&row[0], GPIO_INPUT | GPIO_PULL_DOWN);

    int ret;

    ret = gpio_pin_interrupt_configure_dt(&row[0].port, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0)
    {
        printk("Error: failed to configure interrupt\n");
        return 0;
    }

	gpio_init_callback(&button_cb_data, button_pressed, BIT(row[0].pin));
	gpio_add_callback(row[0].port, &button_cb_data);

    
	printk("Press the button\n");
	
		while (1)
		{
			/* If we have an LED, match its state to the button's. */
            for(int i=0;i<=3;i++){
                gpio_pin_get_dt(&row[i]);
            }
			// if (val >= 0)
			// {
			// 	gpio_pin_set_dt(&col[0], val);
			// }
	}
	return 0;
}

// char read_keypad()
// {

//         for (int row_no = 0; row_no < 4; row_no++)
//         {

//                 gpio_pin_set_dt(&row1, row_no == 0 ? 0 : 1);
//                 gpio_pin_set_dt(&row2, row_no == 1 ? 0 : 1);
//                 gpio_pin_set_dt(&row3, row_no == 2 ? 0 : 1);
//                 gpio_pin_set_dt(&row4, row_no == 3 ? 0 : 1);

//                 if (gpio_pin_get_dt(&col1))
//                         return keypad[row_no][0];
//                 if (gpio_pin_get_dt(&col2))
//                         return keypad[row_no][1];
//                 if (gpio_pin_get_dt(&col3))
//                         return keypad[row_no][2];
//                 if (gpio_pin_get_dt(&col4))
//                         return keypad[row_no][3];
//         }

//         return '\0';
// }
// int main(void)
// {
//         static void mytimer_cb(struct k_timer * dummy)
//         {

//                 char key = read_keypad();
//                 static uint8_t *p_key = keypadkey;

//                 if (key != '\0')
//                 {
//                         printk(" %c\n ", key);

//                         switch (key)
//                         {

//                         case '8':
//                                 **send this somhow **(membrane_key_stroke_to_send);
//                                 break;

//                         case '2':
//                                 **send this somhow **(membrane_key_stroke_to_send + 1);
//                                 break;

//                         case '4':
//                                 **send this somhow **(membrane_key_stroke_to_send + 2);
//                                 break;

//                         case '6':
//                                 **send this somhow **(membrane_key_stroke_to_send + 3);
//                                 break;

//                         case '1':
//                                 **send this somhow **(membrane_key_stroke_to_send + 4);
//                                 break;

//                         case '7':
//                                 **send this somhow **(membrane_key_stroke_to_send + 5);
//                                 break;

//                         case '3':
//                                 **send this somhow **(membrane_key_stroke_to_send + 6);
//                                 break;

//                         case 'A':
//                                 **send this somhow **(membrane_key_stroke_to_send + 7);
//                                 break;

//                         case 'B':
//                                 **send this somhow **(membrane_key_stroke_to_send + 8);
//                                 break;

//                         case 'C':
//                                 **send this somhow **(membrane_key_stroke_to_send + 9);
//                                 break;

//                         case '*':
//                                 **send this somhow **(membrane_key_stroke_to_send + 10);
//                                 break;

//                         case '#':
//                                 **send this somhow **(membrane_key_stroke_to_send + 11);
//                                 break;
//                         }
//                 }
//         }
//         return 0;
// }
