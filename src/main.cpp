#include <Arduino.h>
#include "oled.h"
#include "wifiHandler.h"
#include "buttonHandler.h"

enum WifiMode {
  WIFI_MODE_STA = 0,
  WIFI_MODE_AP
};

WifiMode currentWifiMode = WIFI_MODE_STA;

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

      // Khi đang ở STA, nhấn nút sẽ chuyển sang AP
      if (currentWifiMode == WIFI_MODE_STA) {
        bool ok = wifi_start_ap(WIFI_AP_SSID, WIFI_AP_PASS);
        if (ok) {
          currentWifiMode = WIFI_MODE_AP;
          oled_print("AP MODE");
        } else {
          oled_print("AP FAIL");
        }
      }
    } else {
      Serial.println("Button released");
    }
  }

  // Nếu đang ở AP mode thì xử lý request WebServer
  if (currentWifiMode == WIFI_MODE_AP) {
    wifi_ap_handle_client();
  }

  delay(20); // chống dội đơn giản, giảm tải CPU
}