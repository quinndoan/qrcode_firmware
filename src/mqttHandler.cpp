#include "mqttHandler.h"
#include "wifiHandler.h"

#include <WiFi.h>
#include <PubSubClient.h>

// Sử dụng MQTT broker free công cộng
// Lưu ý: chỉ dùng cho thử nghiệm, không gửi dữ liệu nhạy cảm
static const char *MQTT_BROKER = "broker.hivemq.com"; // broker free
static const uint16_t MQTT_PORT = 1883;

static const char *MQTT_TOPIC_SUB = "esp32/qrcode_firmware/cmd";
static const char *MQTT_TOPIC_PUB = "esp32/qrcode_firmware/status";
static const char *MQTT_TOPIC_BTN = "esp32/qrcode_firmware/button";

static WiFiClient espClient;
static PubSubClient mqttClient(espClient);

static void mqtt_reconnect();

static void mqtt_callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("[MQTT] Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void mqtt_init() {
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(mqtt_callback);
  Serial.print("[MQTT] Configured broker: ");
  Serial.print(MQTT_BROKER);
  Serial.print(":");
  Serial.println(MQTT_PORT);
}

bool mqtt_is_connected() {
  return mqttClient.connected();
}

bool mqtt_publish(const char *topic, const char *payload) {
  if (!wifi_is_connected() || !mqttClient.connected()) {
    return false;
  }
  return mqttClient.publish(topic, payload);
}

void mqtt_loop() {
  // Chỉ xử lý MQTT khi có WiFi (STA) đang kết nối
  if (!wifi_is_connected()) {
    return;
  }

  if (!mqttClient.connected()) {
    mqtt_reconnect();
  }

  if (mqttClient.connected()) {
    mqttClient.loop();
  }
}

static void mqtt_reconnect() {
  if (!wifi_is_connected()) {
    return;
  }

  if (mqttClient.connected()) {
    return;
  }

  Serial.println("[MQTT] Attempting connection...");

  // Tạo clientId đơn giản dựa trên millis()
  String clientId = "ESP32-qrcode-";
  clientId += String((uint32_t)millis(), HEX);

  if (mqttClient.connect(clientId.c_str())) {
    Serial.println("[MQTT] Connected");
    // Đăng ký topic nhận lệnh
    mqttClient.subscribe(MQTT_TOPIC_SUB);
    // Gửi trạng thái online
    mqttClient.publish(MQTT_TOPIC_PUB, "online");
  } else {
    Serial.print("[MQTT] Failed, rc=");
    Serial.print(mqttClient.state());
    Serial.println("; will retry later");
  }
}

// Hàm tiện dùng riêng để publish trạng thái nút (sẽ dùng trong main)
bool mqtt_publish_button(const char *state) {
  return mqtt_publish(MQTT_TOPIC_BTN, state);
}
