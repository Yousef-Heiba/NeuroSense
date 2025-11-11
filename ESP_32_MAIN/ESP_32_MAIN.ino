#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <time.h>

#define NTP_SERVER "pool.ntp.org"
#define UTC_OFFSET_SEC -5 * 3600   // Toronto UTC-5
#define DST_OFFSET_SEC 3600        // DST offset

// Sensor pins
#define lightData 9
#define soundData 10
#define x_axis 4
#define y_axis 5
#define z_axis 6

void setup() {
  Serial.begin(115200);

  WiFi.begin("Wokwi-GUEST", "");
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Blynk.begin(BLYNK_AUTH_TOKEN, "Wokwi-GUEST", "");

  configTime(UTC_OFFSET_SEC, DST_OFFSET_SEC, NTP_SERVER);
}

void loop() {
  Blynk.run(); // Handle Blynk events

  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    // Send time to Blynk
    Blynk.virtualWrite(V0, timeinfo.tm_hour);
    Blynk.virtualWrite(V1, timeinfo.tm_min);
    Blynk.virtualWrite(V2, timeinfo.tm_sec);

    char dateStr[16];
    sprintf(dateStr, "%02d/%02d/%04d", timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
    Blynk.virtualWrite(V3, dateStr);
  }

  // Send sensor data to Blynk
  Blynk.virtualWrite(V4, analogRead(lightData));
  Blynk.virtualWrite(V5, analogRead(soundData));
  Blynk.virtualWrite(V6, analogRead(x_axis));
  Blynk.virtualWrite(V7, analogRead(y_axis));
  Blynk.virtualWrite(V8, analogRead(z_axis));  

  delay(750); 
}