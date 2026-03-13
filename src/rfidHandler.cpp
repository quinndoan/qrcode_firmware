#include "rfidHandler.h"

// Sử dụng Serial2 cho module RFID 125kHz
// Nhiều module 125kHz (VD: RDM6300) gửi chuỗi ASCII kết thúc bằng \r hoặc \n

static String rfidBuffer;
static bool rfidTagReady = false;

void rfid_init() {
  rfidBuffer.reserve(32);
  Serial2.begin(RFID_BAUD, SERIAL_8N1, RFID_RX_PIN, RFID_TX_PIN);
}

void rfid_update() {
  while (Serial2.available() > 0) {
    char c = (char)Serial2.read();

    // Ký tự kết thúc dòng -> hoàn thành một mã thẻ
    if (c == '\n' || c == '\r') {
      if (rfidBuffer.length() > 0) {
        rfidTagReady = true;
      }
      // Không reset buffer ở đây; sẽ reset sau khi ứng dụng đọc
      return;
    }

    // Lọc chỉ cho phép ký tự in được
    if (isPrintable(c)) {
      // Giới hạn độ dài để tránh tràn
      if (rfidBuffer.length() < 32) {
        rfidBuffer += c;
      }
    }
  }
}

bool rfid_has_new_tag() {
  return rfidTagReady;
}

String rfid_get_last_tag() {
  String tag = rfidBuffer;
  rfidBuffer = "";
  rfidTagReady = false;
  return tag;
}
