#pragma once

#include <Arduino.h>

// Thay SSID và password của bạn tại đây
#define WIFI_SSID "Quinn"
#define WIFI_PASS "27032021"

// Khởi tạo WiFi ở chế độ STA và thử kết nối
// timeoutMs: thời gian chờ kết nối (ms)
void wifi_init_sta(const char *ssid, const char *password, unsigned long timeoutMs = 15000);

// Trả về true nếu WiFi đang kết nối
bool wifi_is_connected();

// Lấy địa chỉ IP hiện tại (0.0.0.0 nếu chưa kết nối)
IPAddress wifi_get_ip();
