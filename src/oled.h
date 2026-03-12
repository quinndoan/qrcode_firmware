#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <U8g2lib.h>

// Thay đổi model màn hình hoặc chân nếu bạn dùng loại khác
// Ví dụ dưới đây: SSD1306 128x64, giao tiếp I2C, SDA=21, SCL=22
#define OLED_SDA_PIN 21
#define OLED_SCL_PIN 22
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled;  // khai báo biến oled dùng chung

// Khởi tạo OLED (gọi trong setup)
void oled_init();

// In chuỗi text đơn giản lên OLED (x=0, y=15)
void oled_print(const char *text);

#endif