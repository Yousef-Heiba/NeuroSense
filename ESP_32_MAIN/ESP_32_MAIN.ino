#include <WiFi.h>
#include <time.h>

#define NTP_SERVER "pool.ntp.org"
#define UTC_OFFSET_SEC -5 * 3600
#define DST_OFFSET_SEC 3600

#define lightData 9
#define soundData 38
#define x_axis 4
#define y_axis 5
#define z_axis 6

String lastDate = "";

void setup() {
  Serial.begin(115200);

  WiFi.begin("hospital", "password");
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  configTime(UTC_OFFSET_SEC, DST_OFFSET_SEC, NTP_SERVER);
}

void loop() {
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    char dateStr[16];
    sprintf(dateStr, "%02d/%02d/%04d", timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);

    if (lastDate != String(dateStr)) {
      lastDate = String(dateStr);
      Serial.println();
      Serial.print("Date: ");
      Serial.println(dateStr);
    }

    char timeStr[10];
    sprintf(timeStr, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    Serial.print("Time: ");
    Serial.println(timeStr);
  } else {
    Serial.println("Failed to get time");
  }
  Serial.print("Light: ");
  Serial.println(analogRead(lightData));
  Serial.print("Sound: ");
  Serial.println(digitalRead(soundData));
  Serial.print("X: ");
  Serial.println(analogRead(x_axis));
  Serial.print("Y: ");
  Serial.println(analogRead(y_axis));
  Serial.print("Z: ");
  Serial.println(analogRead(z_axis));

  delay(500);
}