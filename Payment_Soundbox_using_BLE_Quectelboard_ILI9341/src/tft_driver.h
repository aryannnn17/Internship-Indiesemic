void tft_init(const struct device *dev);
void tft_qrcode(const char *data, lv_coord_t size, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs);
void tft_text(char msg[], lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs, uint32_t text_color);
void tft_execute(const struct device *dev);
void tft_bg_color(uint32_t bg_color);
void lv_example_event_1(void);
void lv_example_style_10(void);
void tft_clean(void);