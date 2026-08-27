#include <DHT.h>
#include <U8g2lib.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(
  U8G2_R0, 18, 23, 5, 16, 17
);

void setup() {
  Serial.begin(115200);

  dht.begin();
  u8g2.begin();
}

void loop() {

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11");
    return;
  }

  char tempStr[10];
  char humStr[10];

  sprintf(tempStr, "%.1f C", temperature);
  sprintf(humStr, "%.1f %%", humidity);

  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(25, 12, "ENVIRONMENT");

  u8g2.setFont(u8g2_font_10x20_tf);
  u8g2.drawStr(10, 35, tempStr);
  u8g2.drawStr(10, 58, humStr);

  u8g2.sendBuffer();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000);
}