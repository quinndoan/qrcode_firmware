#include "oled.h"

// Tạo đối tượng OLED sử dụng I2C phần cứng của ESP32
// SCL = 22, SDA = 21, không dùng chân RESET (U8X8_PIN_NONE)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ OLED_SCL_PIN, /* data=*/ OLED_SDA_PIN);

void oled_init() {
	oled.begin();
	oled.clearBuffer();
	oled.setFont(u8g2_font_ncenB08_tr);  // chọn font chữ dễ nhìn
}

void oled_print(const char *text) {
	oled.clearBuffer();
	oled.drawStr(0, 15, text);  // in tại vị trí (0,15)
	oled.sendBuffer();
}
