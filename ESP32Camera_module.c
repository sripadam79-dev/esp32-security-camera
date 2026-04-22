#define BLYNK_TEMPLATE_ID   "TMPL3_Pky1JmT"
#define BLYNK_TEMPLATE_NAME "hello"
#define BLYNK_AUTH_TOKEN    "LMMDw4vmAT8KhkNP5i1NRTUBD3b8WXAb"

#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// ✅ PIR connected to UOR = GPIO 3 (as per your circuit)
#define PIR 3

const char* ssid     = "POCOX6";
const char* password = "12345234";
char auth[]          = "LMMDw4vmAT8KhkNP5i1NRTUBD3b8WXAb";

String local_IP;
bool pirEnabled = false; // delay PIR reading on startup

void startCameraServer();

void takePhoto() {
  uint32_t randomNum = random(50000);

  Serial.println("========================================");
  Serial.println("📸 Motion Detected - Photo Captured!");
  Serial.println("Open in browser:");
  Serial.println("http://" + local_IP + "/capture?_cb=" + (String)randomNum);
  Serial.println("========================================");

  Blynk.virtualWrite(V1, 1);
  delay(500);
  Blynk.virtualWrite(V1, 0);
}

void setup() {
  Serial.begin(115200);

  // ✅ GPIO 3 is Serial RX — release it for PIR use after serial init
  delay(1000);
  pinMode(PIR, INPUT);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = Y2_GPIO_NUM;
  config.pin_d1       = Y3_GPIO_NUM;
  config.pin_d2       = Y4_GPIO_NUM;
  config.pin_d3       = Y5_GPIO_NUM;
  config.pin_d4       = Y6_GPIO_NUM;
  config.pin_d5       = Y7_GPIO_NUM;
  config.pin_d6       = Y8_GPIO_NUM;
  config.pin_d7       = Y9_GPIO_NUM;
  config.pin_xclk     = XCLK_GPIO_NUM;
  config.pin_pclk     = PCLK_GPIO_NUM;
  config.pin_vsync    = VSYNC_GPIO_NUM;
  config.pin_href     = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn     = PWDN_GPIO_NUM;
  config.pin_reset    = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size   = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count     = 2;
  } else {
    config.frame_size   = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count     = 1;
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed: 0x%x\n", err);
    return;
  }

  sensor_t* s = esp_camera_sensor_get();
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);
    s->set_brightness(s, 1);
    s->set_saturation(s, -2);
  }
  s->set_framesize(s, FRAMESIZE_QVGA);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");

  startCameraServer();

  local_IP = WiFi.localIP().toString();
  Serial.println("✅ Camera Ready!");
  Serial.println("📷 Stream: http://" + local_IP + ":81/stream");
  Serial.println("📸 Capture: http://" + local_IP + "/capture");

  Blynk.begin(auth, ssid, password);

  // ✅ Wait 5 seconds after boot before reading PIR
  // This prevents false triggers on startup
  Serial.println("⏳ Waiting 5 seconds before enabling PIR...");
  delay(5000);
  pirEnabled = true;
  Serial.println("✅ PIR Enabled! Ready to detect motion.");
}

void loop() {
  Blynk.run();

  if (pirEnabled) {
    int pirState = digitalRead(PIR);
    Serial.println("PIR: " + String(pirState)); // remove this line after testing

    if (pirState == HIGH) {
      Serial.println("🚨 Motion Detected!");
      Blynk.logEvent("intruder_detected", "🚨 Intruder Detected!");
      takePhoto();
      delay(3000); // cooldown
    }
  }
}
