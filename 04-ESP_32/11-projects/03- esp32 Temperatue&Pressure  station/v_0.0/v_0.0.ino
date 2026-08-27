#include <SPI.h>
#include <U8g2lib.h>
#include <Adafruit_BMP280.h>

#define OLED_CLK   14
#define OLED_MOSI  13
#define OLED_CS    5
#define OLED_DC    16
#define OLED_RST   17

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(
  U8G2_R0,
  OLED_CLK,
  OLED_MOSI,
  OLED_CS,
  OLED_DC,
  OLED_RST
);


#define BMP_CS    4
#define BMP_SCK   18
#define BMP_MISO  19
#define BMP_MOSI  23

Adafruit_BMP280 bmp(BMP_CS);


void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println("Starting Weather Station...");


  SPI.begin(
    BMP_SCK,
    BMP_MISO,
    BMP_MOSI,
    BMP_CS
  );

  u8g2.begin();

  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(20, 25, "Starting...");
  u8g2.drawStr(10, 40, "Weather Station");

  u8g2.sendBuffer();

  delay(1000);

  if (!bmp.begin()) {

    Serial.println("BMP280 NOT detected!");

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(15, 30, "BMP280 ERROR");
    u8g2.sendBuffer();

    while (true);
  }


  Serial.println("BMP280 detected!");

  Serial.print("Sensor ID: 0x");
  Serial.println(bmp.sensorID(), HEX);


  // Configure BMP280
  bmp.setSampling(
    Adafruit_BMP280::MODE_NORMAL,
    Adafruit_BMP280::SAMPLING_X2,
    Adafruit_BMP280::SAMPLING_X16,
    Adafruit_BMP280::FILTER_X16,
    Adafruit_BMP280::STANDBY_MS_500
  );
}


void loop() {

  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;

  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" C");

  Serial.print("Pressure: ");
  Serial.print(pressure, 2);
  Serial.println(" hPa");

  Serial.println("----------------");


  char tempStr[25];
  char pressureStr[25];

  sprintf(tempStr, "Temp: %.2f C", temperature);
  sprintf(pressureStr, "Press: %.2f hPa", pressure);


  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(15, 10, "ESP32 WEATHER");

  u8g2.drawHLine(0, 15, 128);

  u8g2.setFont(u8g2_font_7x14B_tf);
  u8g2.drawStr(5, 35, tempStr);

  u8g2.drawStr(5, 57, pressureStr);

  u8g2.sendBuffer();


  delay(2000);
}