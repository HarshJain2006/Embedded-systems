#include <WiFi.h>
#include <U8g2lib.h>
#include "time.h"

// Wi-Fi Credentials
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Time Server Configuration (India Standard Time GMT+5:30)
const long  gmtOffset_sec = 19800; 
const int   daylightOffset_sec = 0;

//Switched to 4W_SW_SPI to correctly accept all 6 pin arguments
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, 18,  23, 5,16, 17);

void setup() {
  u8g2.begin();
  
  // Display Connection Status
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(10, 30, "Connecting to WiFi...");
  u8g2.sendBuffer();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Initialize and fetch time from internet
  configTime(gmtOffset_sec, daylightOffset_sec, "pool.ntp.org");
}

void loop() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return; // Skip loop if time fetch fails
  }


  char timeHourMin[10];
  char timeSec[5];
  char dateStr[20];

  // Format time data into readable strings
  strftime(timeHourMin, sizeof(timeHourMin), "%H:%M", &timeinfo);
  strftime(timeSec, sizeof(timeSec), ":%S", &timeinfo);
  strftime(dateStr, sizeof(dateStr), "%A, %b %d", &timeinfo);

  // Draw Interface to screen
  u8g2.clearBuffer();
  
  // 1. Draw Date at top
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(15, 16, dateStr);
  
  u8g2.drawHLine(0, 22, 128); 

  // 2. Draw Large Hour and Minutes
  u8g2.setFont(u8g2_font_fub20_tf);
  u8g2.drawStr(15, 52, timeHourMin);

  // 3. Draw Smaller Seconds
  u8g2.setFont(u8g2_font_7x14B_tf);
  u8g2.drawStr(92, 45, timeSec);

  u8g2.sendBuffer();
  delay(1000); 
}
