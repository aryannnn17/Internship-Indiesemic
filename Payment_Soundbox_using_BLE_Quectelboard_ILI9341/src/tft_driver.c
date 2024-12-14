#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <stdio.h>
#include <string.h>
#include <lvgl.h>
#include "tft_driver.h"

LOG_MODULE_REGISTER(ILI9341_DISPLAY, LOG_LEVEL_INF);

void tft_init(const struct device *dev)
{
        if (!device_is_ready(dev))
        {
                LOG_ERR("Device not ready, aborting test");
                return;
        }
        LOG_INF("Display is connected");
}

void tft_execute(const struct device *dev)
{
        lv_task_handler();
        display_blanking_off(dev);
}

void tft_qrcode(const char *data, lv_coord_t size, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs)
{
        lv_color_t bg_color = lv_palette_lighten(LV_PALETTE_WHITE, 5);
        lv_color_t fg_color = lv_palette_darken(LV_PALETTE_BLACK, 4);

        lv_obj_t *qr = lv_qrcode_create(lv_scr_act(), size, bg_color, fg_color);

        /*Set data*/
        // const char *data = "https://g.co/kgs/f7btthT";
        lv_qrcode_update(qr, data, strlen(data));
        lv_obj_align(qr, align, x_ofs, y_ofs);

        /*Add a border with bg_color*/
        lv_obj_set_style_border_color(qr, fg_color, 0);
        lv_obj_set_style_border_width(qr, 5, 0);
}

void tft_clean(void)
{
        lv_obj_clean(lv_scr_act());
}

void tft_text(char msg[], lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs, uint32_t text_color)
{
        /*Change the active screen's background color*/
        // lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);

        /*Create a white label, set its text and align it to the center*/
        lv_obj_t *label = lv_label_create(lv_scr_act());
        lv_label_set_text(label, msg);
        lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(text_color), LV_PART_MAIN);
        lv_obj_align(label, align, x_ofs, y_ofs);
}

void tft_bg_color(uint32_t bg_color)
{
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(bg_color), LV_PART_MAIN);
}

static void event_cb(lv_event_t *e)
{
        LV_LOG_USER("Clicked");

        static uint32_t cnt = 1;
        lv_obj_t *btn = lv_event_get_target(e);
        lv_obj_t *label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "%" LV_PRIu32, cnt);
        cnt++;
}

void lv_example_event_1(void)
{
        lv_obj_t *btn = lv_btn_create(lv_scr_act());
        lv_obj_set_size(btn, 100, 50);
        lv_obj_center(btn);
        lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, NULL);

        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, "Click me!");
        lv_obj_center(label);
}

void lv_example_style_10(void)
{
        static const lv_style_prop_t props[] = {LV_STYLE_BG_COLOR, LV_STYLE_BORDER_COLOR, LV_STYLE_BORDER_WIDTH, 0};

        /* A default transition
         * Make it fast (100ms) and start with some delay (200 ms)*/
        static lv_style_transition_dsc_t trans_def;
        lv_style_transition_dsc_init(&trans_def, props, lv_anim_path_linear, 1000, 200, NULL);

        /* A special transition when going to pressed state
         * Make it slow (500 ms) but start  without delay*/
        static lv_style_transition_dsc_t trans_pr;
        lv_style_transition_dsc_init(&trans_pr, props, lv_anim_path_linear, 2000, 1000, NULL);

        static lv_style_t style_def;
        lv_style_init(&style_def);
        lv_style_set_transition(&style_def, &trans_def);

        static lv_style_t style_pr;
        lv_style_init(&style_pr);
        lv_style_set_bg_color(&style_pr, lv_palette_main(LV_PALETTE_RED));
        lv_style_set_border_width(&style_pr, 6);
        lv_style_set_border_color(&style_pr, lv_palette_darken(LV_PALETTE_RED, 3));
        lv_style_set_transition(&style_pr, &trans_pr);

        /*Create an object with the new style_pr*/
        lv_obj_t *obj = lv_obj_create(lv_scr_act());
        lv_obj_add_style(obj, &style_def, 0);
        lv_obj_add_style(obj, &style_pr, LV_STATE_PRESSED);

        lv_obj_center(obj);
}
