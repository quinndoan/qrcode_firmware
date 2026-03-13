#pragma once

#include <Arduino.h>

// Buzzer nối vào chân D4 (GPIO4 trên ESP32)
#define BUZZER_PIN 4

// Khởi tạo chân buzzer
void buzzer_init();

// Bật buzzer (kêu liên tục)
void buzzer_on();

// Tắt buzzer
void buzzer_off();

// Kêu beep ngắn với thời gian ms
void buzzer_beep(uint16_t durationMs = 100);
