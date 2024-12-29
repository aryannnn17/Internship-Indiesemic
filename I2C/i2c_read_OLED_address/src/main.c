#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

int main(void)
{
        const struct device *display_dev;
        lv_obj_t *hello_world_label;
        lv_obj_t *count_label;

        display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
        if (!device_is_ready(display_dev))
        {
                LOG_ERR("Device not ready, aborting test");
                return 0;
        }

        if (IS_ENABLED(CONFIG_LV_Z_POINTER_KSCAN))
        {
                lv_obj_t *hello_world_button;

                hello_world_button = lv_btn_create(lv_scr_act());
                lv_obj_align(hello_world_button, LV_ALIGN_CENTER, 0, 0);
                hello_world_label = lv_label_create(hello_world_button);
        }
        else
        {
                hello_world_label = lv_label_create(lv_scr_act());
        }
        
        lv_label_set_text(hello_world_label, "IndieSemiC\n Pvt. Ltd.");
        lv_obj_align(hello_world_label, LV_ALIGN_CENTER, 0, 0);

        count_label = lv_label_create(lv_scr_act());
        lv_obj_align(count_label, LV_ALIGN_BOTTOM_MID, 0, 0);
      
        lv_task_handler();
        display_blanking_off(display_dev);
}
