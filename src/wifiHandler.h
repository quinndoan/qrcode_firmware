#pragma once

#include <Arduino.h>

// Thay SSID và password STA của bạn tại đây
#define WIFI_SSID "Quinn"
#define WIFI_PASS "27032021"

// Thông tin WiFi AP (khi chuyển sang chế độ AP)
#define WIFI_AP_SSID "ESP32_AP"
#define WIFI_AP_PASS "12345678" // tối thiểu 8 ký tự

// Khởi tạo WiFi ở chế độ STA và thử kết nối
// timeoutMs: thời gian chờ kết nối (ms)
void wifi_init_sta(const char *ssid, const char *password, unsigned long timeoutMs = 15000);

// Khởi tạo/chuyển sang chế độ AP với SSID/PASS cho trước
bool wifi_start_ap(const char *ssid, const char *password);

// Trả về true nếu WiFi đang kết nối
bool wifi_is_connected();

// Lấy địa chỉ IP hiện tại (0.0.0.0 nếu chưa kết nối)
IPAddress wifi_get_ip();

// Hàm xử lý request cho WebServer khi đang ở AP mode
// Gọi hàm này thường xuyên trong loop (khi đang ở AP)
void wifi_ap_handle_client();
