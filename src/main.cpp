#include <Arduino.h>
#include "oled.h"
#include "wifiHandler.h"
#include "buttonHandler.h"

void setup() {
  Serial.begin(115200);

  // Cấu hình nút nhấn: nối nút xuống GND thì dùng INPUT_PULLUP
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Khởi tạo WiFi STA thông qua wifiHandler
  wifi_init_sta(WIFI_SSID, WIFI_PASS);

  // Khởi tạo màn hình OLED
  oled_init();

  // Hiển thị trạng thái WiFi lên OLED
  if (wifi_is_connected()) {
    oled_print("WiFi OK");
  } else {
    oled_print("WiFi FAIL");
  }
}

void loop() {
  // Đọc trạng thái nút
  int buttonState = digitalRead(BUTTON_PIN);

  // Ví dụ: in trạng thái nút ra Serial (nhấn = 0 nếu dùng INPUT_PULLUP)
  static int lastState = HIGH;
  if (buttonState != lastState) {
    lastState = buttonState;
    if (buttonState == LOW) {
      Serial.println("Button pressed");
    } else {
      Serial.println("Button released");
    }
  }

  delay(20); // chống dội đơn giản, giảm tải CPU
}