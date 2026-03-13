#pragma once

#include <Arduino.h>

// Khởi tạo cấu hình MQTT (broker, port, callback...)
void mqtt_init();

// Gọi thường xuyên trong loop khi đang ở chế độ STA và đã có WiFi
void mqtt_loop();

// Kiểm tra trạng thái kết nối MQTT
bool mqtt_is_connected();

// Publish một message đơn giản (trả về true nếu gửi được)
bool mqtt_publish(const char *topic, const char *payload);
