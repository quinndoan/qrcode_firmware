#include "wifiHandler.h"
#include <WiFi.h>

void wifi_init_sta(const char *ssid, const char *password, unsigned long timeoutMs) {
  Serial.println("[WiFi] Starting STA mode...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeoutMs) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WiFi] Connected");
    Serial.print("[WiFi] IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n[WiFi] Connect failed");
  }
}

bool wifi_is_connected() {
  return WiFi.status() == WL_CONNECTED;
}

IPAddress wifi_get_ip() {
  if (WiFi.status() == WL_CONNECTED) {
    return WiFi.localIP();
  }
  return IPAddress(0, 0, 0, 0);
}
