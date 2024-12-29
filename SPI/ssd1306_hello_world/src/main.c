
#include <zephyr/kernel.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/drivers/spi.h>
// #define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

int main(void)
{
	lv_obj_t *hello_world_label;
	// lv_obj_t *label;
	const struct device *display_dev;

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

	// const struct device *display_dev = DEVICE_DT_GET(DT_NODELABEL(ssd1306));
	if (!device_is_ready(display_dev))
	{
		printk("Device not ready, aborting test");
		return 0;
	}

	if (IS_ENABLED(CONFIG_LV_Z_POINTER_KSCAN))
	{
		lv_obj_t *hello_world_button;

		hello_world_button = lv_btn_create(lv_scr_act());
		lv_obj_align(hello_world_button, LV_ALIGN_CENTER, 0, 0);
		hello_world_label = lv_label_create(hello_world_button);
		// lv_obj_set_style_bg_color(hello_world_button, lv_color_hex(255), LV_PART_MAIN);
		// lv_obj_t *hello_world_button;
		/* lv_obj_t *label;
		lv_obj_t *btn;
		btn = lv_btn_create(lv_scr_act());
		lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
		label = lv_label_create(label); */
	}
	else
	{
		// label = lv_label_create(lv_scr_act());
		hello_world_label = lv_label_create(lv_scr_act());
	}
	// label = lv_btn_create(lv_scr_act());
	// lv_obj_set_style_text_color(label, lv_color_hex(0x00), LV_PART_MAIN);
	// lv_label_set_text(label, "Indiesemic");
	// lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
	lv_label_set_text(hello_world_label, "IndieSemiC");
	lv_obj_align(hello_world_label, LV_ALIGN_CENTER, 0, 0);
	// lv_obj_set_style_text_color(hello_world_label, lv_color_hex(0), LV_PART_MAIN);

	/*  count_label = lv_label_create(lv_scr_act());
		lv_obj_align(count_label, LV_ALIGN_BOTTOM_MID, 0, 0); */
	lv_task_handler();
	display_blanking_off(display_dev);
}
