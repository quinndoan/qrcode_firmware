#include "wifiHandler.h"
#include <WiFi.h>
#include <WebServer.h>

// Web server dùng khi ở AP mode
static WebServer apServer(80);
static bool apServerStarted = false;

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

bool wifi_start_ap(const char *ssid, const char *password) {
  Serial.println("[WiFi] Switching to AP mode...");

  // Ngắt kết nối STA hiện tại (nếu có) và chuyển chế độ
  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP);

  bool result = WiFi.softAP(ssid, password);
  if (result) {
    Serial.println("[WiFi] AP started");
    Serial.print("[WiFi] AP SSID: ");
    Serial.println(ssid);
    Serial.print("[WiFi] AP IP address: ");
    Serial.println(WiFi.softAPIP());

    // Cấu hình WebServer đơn giản
    apServer.on("/", []() {
      apServer.send(200, "text/html",
                    "<!DOCTYPE html><html><head><meta charset='utf-8'><title>ESP32 AP</title></head>"
                    "<body><h1>Hello from AP mode</h1></body></html>");
    });
    apServer.begin();
    apServerStarted = true;
    Serial.println("[WiFi] WebServer started on AP");
  } else {
    Serial.println("[WiFi] Failed to start AP");
    apServerStarted = false;
  }

  return result;
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

void wifi_ap_handle_client() {
  if (apServerStarted) {
    apServer.handleClient();
  }
}
