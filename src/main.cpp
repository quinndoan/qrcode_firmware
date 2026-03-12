#include <Arduino.h>
#include "oled.h"

void setup() {
  Serial.begin(115200);

  // Khởi tạo màn hình OLED
  oled_init();

  // In thử một dòng chữ lên OLED
  oled_print("Hello OLED");
}

void loop() {
  // Nếu chỉ cần hiển thị tĩnh thì để trống
  // Có thể thêm hiệu ứng hay cập nhật nội dung ở đây
}