#include "buzzerHandler.h"

void buzzer_init() {
	pinMode(BUZZER_PIN, OUTPUT);
	digitalWrite(BUZZER_PIN, LOW); // mặc định tắt
}

void buzzer_on() {
	digitalWrite(BUZZER_PIN, HIGH);
}

void buzzer_off() {
	digitalWrite(BUZZER_PIN, LOW);
}

void buzzer_beep(uint16_t durationMs) {
	buzzer_on();
	delay(durationMs);
	buzzer_off();
}
