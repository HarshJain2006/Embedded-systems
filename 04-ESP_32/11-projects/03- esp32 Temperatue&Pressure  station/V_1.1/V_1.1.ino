// ============================================================
// ESP32 WEATHER STATION - VERSION 1.1
// ============================================================


// ============================================================
// LIBRARIES
// ============================================================

#include <SPI.h>
#include <U8g2lib.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <time.h>
#include <WebServer.h>


// ============================================================
// WIFI CONFIGURATION
// ============================================================

const char* WIFI_SSID = "Your_wifi_name";
const char* WIFI_PASSWORD = "Your_wifi_password";

const unsigned long WIFI_CHECK_INTERVAL = 5000;

unsigned long lastWiFiCheck = 0;
bool wasWiFiConnected = false;


// ============================================================
// TIME CONFIGURATION
// ============================================================

// India Standard Time = UTC + 5 hours 30 minutes

const long GMT_OFFSET_SEC = 19800;
const int DAYLIGHT_OFFSET_SEC = 0;

const char* NTP_SERVER = "pool.ntp.org";


// ============================================================
// OLED CONFIGURATION
// Software SPI
// ============================================================

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


// ============================================================
// BMP280 CONFIGURATION
// Hardware SPI
// ============================================================

#define BMP_CS    4
#define BMP_SCK   18
#define BMP_MISO  19
#define BMP_MOSI  23


Adafruit_BMP280 bmp(BMP_CS);


// ============================================================
// WEB SERVER
// ============================================================

WebServer server(80);


// ============================================================
// SENSOR VARIABLES
// ============================================================

float temperature = 0.0;
float pressure = 0.0;


// ============================================================
// TIME VARIABLES
// ============================================================

String currentTime = "--:--:--";
String currentDate = "--/--/----";


// ============================================================
// SENSOR HISTORY CONFIGURATION
// ============================================================

#define MAX_HISTORY 60

const unsigned long HISTORY_INTERVAL = 10000;

struct SensorHistory {

  float temperature;
  float pressure;
  String time;

};


SensorHistory history[MAX_HISTORY];

int historyIndex = 0;
int historyCount = 0;

unsigned long lastHistorySave = 0;


// ============================================================
// FUNCTION PROTOTYPES
// ============================================================

// BMP280
bool initBMP280();
void readSensorData();

// OLED
void initOLED();
void updateOLED();

// Wi-Fi
bool connectWiFi();
void checkWiFi();

// Time
bool initTime();
void updateTime();

//sensor data
void printSensorData();
void saveSensorHistory();


// Web Server
void initWebServer();
void handleWebServer();
void handleRoot();
void handleSensorData();
void handleHistoryData();


// ============================================================
// SETUP
// ============================================================

void setup() {

  Serial.begin(115200);

  delay(3000);

  Serial.println();
  Serial.println("================================");
  Serial.println("Starting ESP32 Weather Station...");
  Serial.println("================================");


  // ----------------------------------------------------------
  // Initialize Shared Hardware SPI Bus
  // ----------------------------------------------------------

  SPI.begin(
    BMP_SCK,
    BMP_MISO,
    BMP_MOSI
  );

  delay(500);


  // ----------------------------------------------------------
  // Initialize OLED
  // ----------------------------------------------------------

  Serial.println("Initializing OLED...");

  initOLED();

  Serial.println("OLED initialized.");

  delay(1000);


  // ----------------------------------------------------------
  // Initialize BMP280
  // ----------------------------------------------------------

  if (initBMP280()) {

    Serial.println("BMP280 initialized.");

  } else {

    Serial.println("BMP280 initialization failed!");

  }


  // ----------------------------------------------------------
  // Connect Wi-Fi
  // ----------------------------------------------------------

  bool wifiConnected = connectWiFi();


  // ----------------------------------------------------------
  // Initialize Time
  // ----------------------------------------------------------

  if (wifiConnected) {

    initTime();

  } else {

    Serial.println("Skipping NTP for now.");
    Serial.println("Time will sync after Wi-Fi connects.");

  }


  // ----------------------------------------------------------
  // Start Web Server
  // ----------------------------------------------------------

  initWebServer();


  Serial.println("================================");
  Serial.println("Weather Station Ready!");
  Serial.println("================================");

}


// ============================================================
// MAIN LOOP
// ============================================================

void loop() {

  // Handle incoming web requests
  handleWebServer();


  // Read BMP280 sensor
  readSensorData();


  // Check and maintain Wi-Fi connection
  checkWiFi();


  // Update NTP time
  updateTime();


  // Save sensor data to history buffer
  saveSensorHistory();


  // Update OLED display
  updateOLED();


  // Print system information
  printSensorData();


  delay(2000);

}


// ============================================================
// BMP280 FUNCTIONS
// ============================================================

bool initBMP280() {

  Serial.println("Testing BMP280...");


  // Make sure BMP280 is deselected
  pinMode(BMP_CS, OUTPUT);
  digitalWrite(BMP_CS, HIGH);

  delay(100);


  if (!bmp.begin()) {

    Serial.println("BMP280 NOT detected!");

    return false;

  }


  Serial.println("BMP280 detected!");

  Serial.print("Sensor ID: 0x");
  Serial.println(bmp.sensorID(), HEX);


  bmp.setSampling(
    Adafruit_BMP280::MODE_NORMAL,
    Adafruit_BMP280::SAMPLING_X2,
    Adafruit_BMP280::SAMPLING_X16,
    Adafruit_BMP280::FILTER_X16,
    Adafruit_BMP280::STANDBY_MS_500
  );


  return true;

}


void readSensorData() {

  temperature = bmp.readTemperature();

  pressure = bmp.readPressure() / 100.0F;

}


// ============================================================
// OLED FUNCTIONS
// ============================================================

void initOLED() {

  u8g2.begin();

  u8g2.clearBuffer();

  u8g2.setFont(
    u8g2_font_6x10_tf
  );

  u8g2.drawStr(
    20,
    25,
    "Starting..."
  );

  u8g2.sendBuffer();

}


void updateOLED() {

  char tempStr[20];
  char pressureStr[25];


  snprintf(
    tempStr,
    sizeof(tempStr),
    "Temp: %.1f C",
    temperature
  );


  snprintf(
    pressureStr,
    sizeof(pressureStr),
    "Press: %.1f hPa",
    pressure
  );


  u8g2.clearBuffer();


  // Title
  u8g2.setFont(
    u8g2_font_6x10_tf
  );

  u8g2.drawStr(
    20,
    9,
    "ESP32 WEATHER"
  );


  // Time
  u8g2.drawStr(
    2,
    23,
    currentTime.c_str()
  );


  // Temperature
  u8g2.setFont(
    u8g2_font_7x14B_tf
  );

  u8g2.drawStr(
    2,
    43,
    tempStr
  );


  // Pressure
  u8g2.setFont(
    u8g2_font_6x10_tf
  );

  u8g2.drawStr(
    2,
    60,
    pressureStr
  );


  u8g2.sendBuffer();

}


// ============================================================
// WIFI FUNCTIONS
// ============================================================

bool connectWiFi() {

  Serial.println("Connecting to Wi-Fi...");


  // Reset Wi-Fi hardware state
  WiFi.mode(WIFI_OFF);

  delay(1000);


  WiFi.mode(WIFI_STA);

  delay(1000);


  WiFi.setAutoReconnect(true);

  WiFi.persistent(false);


  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );


  int attempts = 0;


  while (
    WiFi.status() != WL_CONNECTED &&
    attempts < 20
  ) {

    Serial.print(".");

    delay(500);

    attempts++;

  }


  Serial.println();


  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("Wi-Fi Connected!");

    Serial.print("ESP32 IP Address: ");
    Serial.println(
      WiFi.localIP()
    );


    wasWiFiConnected = true;

    return true;

  }


  Serial.println("Wi-Fi connection failed.");
  Serial.println("Will retry automatically.");

  return false;

}


void checkWiFi() {

  // ----------------------------------------------------------
  // Wi-Fi Connected
  // ----------------------------------------------------------

  if (WiFi.status() == WL_CONNECTED) {

    // Detect reconnection
    if (!wasWiFiConnected) {

      Serial.println("Wi-Fi reconnected!");

      Serial.print("ESP32 IP Address: ");
      Serial.println(
        WiFi.localIP()
      );


      wasWiFiConnected = true;


      // Synchronize NTP time again
      initTime();

    }


    return;

  }


  // ----------------------------------------------------------
  // Wi-Fi Disconnected
  // ----------------------------------------------------------

  wasWiFiConnected = false;


  // Retry connection periodically
  if (
    millis() - lastWiFiCheck >=
    WIFI_CHECK_INTERVAL
  ) {

    lastWiFiCheck = millis();


    Serial.println(
      "Wi-Fi not connected. Retrying..."
    );


    WiFi.disconnect();

    delay(200);


    WiFi.begin(
      WIFI_SSID,
      WIFI_PASSWORD
    );

  }

}


// ============================================================
// TIME FUNCTIONS
// ============================================================

bool initTime() {

  Serial.println(
    "Synchronizing time with NTP..."
  );


  configTime(
    GMT_OFFSET_SEC,
    DAYLIGHT_OFFSET_SEC,
    NTP_SERVER
  );


  struct tm timeInfo;

  int attempts = 0;


  while (
    !getLocalTime(&timeInfo) &&
    attempts < 20
  ) {

    Serial.print(".");

    delay(500);

    attempts++;

  }


  Serial.println();


  if (!getLocalTime(&timeInfo)) {

    Serial.println(
      "Time synchronization failed!"
    );

    return false;

  }


  Serial.println(
    "Time synchronized successfully!"
  );

  return true;

}


void updateTime() {

  struct tm timeInfo;


  if (getLocalTime(&timeInfo)) {

    char timeBuffer[15];
    char dateBuffer[15];


    // 12-hour time format
    strftime(
      timeBuffer,
      sizeof(timeBuffer),
      "%I:%M:%S %p",
      &timeInfo
    );


    // Date format
    strftime(
      dateBuffer,
      sizeof(dateBuffer),
      "%d/%m/%Y",
      &timeInfo
    );


    currentTime = String(timeBuffer);
    currentDate = String(dateBuffer);

  } else {

    currentTime = "--:--:--";
    currentDate = "--/--/----";

  }

}


// ============================================================
// SENSOR HISTORY FUNCTIONS
// ============================================================

void saveSensorHistory() {

  // Do not save history until time is valid
  if (currentTime == "--:--:--") {

    return;

  }


  // Save at fixed interval
  if (
    millis() - lastHistorySave >=
    HISTORY_INTERVAL
  ) {

    lastHistorySave = millis();


    // Save current reading
    history[historyIndex].temperature =
      temperature;

    history[historyIndex].pressure =
      pressure;

    history[historyIndex].time =
      currentTime;


    // Move to next history position
    historyIndex++;


    // Circular buffer
    if (historyIndex >= MAX_HISTORY) {

      historyIndex = 0;

    }


    // Increase valid reading count
    if (historyCount < MAX_HISTORY) {

      historyCount++;

    }


    Serial.print(
      "History saved. Total readings: "
    );

    Serial.println(
      historyCount
    );

  }

}


// ============================================================
// WEB SERVER FUNCTIONS
// ============================================================

void initWebServer() {

  // Main dashboard
  server.on(
    "/",
    handleRoot
  );


  // Live sensor API
  server.on(
    "/api/data",
    handleSensorData
  );


  // Sensor history API
  server.on(
    "/api/history",
    handleHistoryData
  );


  server.begin();

  Serial.println(
    "Web Server Started!"
  );

}


void handleWebServer() {

  server.handleClient();

}

// ============================================================
// WEB DASHBOARD
// ============================================================

void handleRoot() {

  String html = R"rawliteral(

    <!DOCTYPE html>
    <html>

      <head>

        <meta charset="UTF-8">

        <meta
          name="viewport"
          content="width=device-width, initial-scale=1.0"
        >

        <title>ESP32 Weather Station</title>

        <!-- Chart.js -->
        <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>

        <style>
          /* ============================================================
            GLOBAL STYLES
          ============================================================ */

          * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
          }


          body {
            font-family: Arial, sans-serif;
            min-height: 100vh;
            color: white;

            background:
              linear-gradient(
                135deg,
                #0f172a,
                #1e293b,
                #0f172a
              );

            padding: 25px;
          }


          /* ============================================================
            MAIN CONTAINER
          ============================================================ */

          .container {
            max-width: 1100px;
            margin: auto;
          }


          /* ============================================================
            HEADER
          ============================================================ */

          .header {
            text-align: center;
            margin-bottom: 35px;
          }


          .header h1 {
            font-size: 38px;
            margin-bottom: 10px;
            letter-spacing: 1px;
          }


          .subtitle {
            color: #94a3b8;
            font-size: 17px;
          }


          /* ============================================================
            LIVE SENSOR DASHBOARD
          ============================================================ */

          .dashboard {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 20px;
          }


          /* ============================================================
            SENSOR CARDS
          ============================================================ */

          .card {
            background: rgba(30, 41, 59, 0.9);

            border:
              1px solid
              rgba(148, 163, 184, 0.15);

            border-radius: 18px;

            padding: 30px;

            box-shadow:
              0 10px 25px
              rgba(0, 0, 0, 0.25);

            transition:
              transform 0.2s,
              box-shadow 0.2s;
          }


          .card:hover {
            transform: translateY(-3px);

            box-shadow:
              0 15px 30px
              rgba(0, 0, 0, 0.35);
          }


          .card-title {
            color: #cbd5e1;
            font-size: 19px;
            font-weight: bold;
            margin-bottom: 20px;
          }


          .value {
            font-size: 34px;
            font-weight: bold;
            color: white;
            word-break: break-word;
          }


          /* ============================================================
            DEVICE STATUS SECTION
          ============================================================ */

          .device-section {
            margin-top: 25px;

            background: rgba(30, 41, 59, 0.9);

            border:
              1px solid
              rgba(148, 163, 184, 0.15);

            border-radius: 18px;

            padding: 30px;

            box-shadow:
              0 10px 25px
              rgba(0, 0, 0, 0.25);
          }


          .section-title {
            text-align: center;
            font-size: 26px;
            margin-bottom: 25px;
          }


          /* ============================================================
            DEVICE INFORMATION
          ============================================================ */

          .device-info {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 20px;
          }


          .info-box {
            background: rgba(15, 23, 42, 0.7);

            border:
              1px solid
              rgba(148, 163, 184, 0.1);

            border-radius: 15px;

            padding: 22px;
            text-align: center;
          }


          .info-title {
            color: #94a3b8;
            font-size: 16px;
            margin-bottom: 12px;
          }


          .info-value {
            font-size: 25px;
            font-weight: bold;
            color: white;
          }


          .signal-quality {
            margin-top: 10px;

            color: #cbd5e1;
            font-size: 14px;
            font-weight: bold;
          }


          /* ============================================================
            CONNECTION STATUS
          ============================================================ */

          .system-status {
            margin-top: 25px;
            text-align: center;
          }


          .status {
            display: inline-block;

            padding: 10px 20px;

            border-radius: 25px;

            font-weight: bold;

            background:
              rgba(34, 197, 94, 0.15);

            color: #4ade80;
          }


          /* ============================================================
            LAST UPDATED
          ============================================================ */

          .last-updated {
            margin-top: 18px;

            text-align: center;

            color: #94a3b8;
            font-size: 14px;
          }


          /* ============================================================
            SENSOR HISTORY SECTION
          ============================================================ */

          .history-section {
            margin-top: 25px;

            background: rgba(30, 41, 59, 0.9);

            border:
              1px solid
              rgba(148, 163, 184, 0.15);

            border-radius: 18px;

            padding: 30px;

            box-shadow:
              0 10px 25px
              rgba(0, 0, 0, 0.25);
          }


          .graph-grid {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 25px;
          }


          .graph-card {
            background: rgba(15, 23, 42, 0.7);

            border:
              1px solid
              rgba(148, 163, 184, 0.1);

            border-radius: 15px;

            padding: 20px;
          }


          .graph-card h3 {
            text-align: center;

            margin-bottom: 20px;

            color: #cbd5e1;
          }


          .graph-card canvas {
            width: 100% !important;
            height: 300px !important;
          }


          /* ============================================================
            SENSOR STATISTICS SECTION
          ============================================================ */

          .statistics-section {
            margin-top: 25px;

            background: rgba(30, 41, 59, 0.9);

            border:
              1px solid
              rgba(148, 163, 184, 0.15);

            border-radius: 18px;

            padding: 30px;

            box-shadow:
              0 10px 25px
              rgba(0, 0, 0, 0.25);
          }


          .statistics-grid {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 20px;
          }


          .stat-card {
            background: rgba(15, 23, 42, 0.7);

            border:
              1px solid
              rgba(148, 163, 184, 0.1);

            border-radius: 15px;

            padding: 25px;
            text-align: center;
          }


          .stat-label {
            color: #94a3b8;
            font-size: 15px;
            margin-bottom: 12px;
          }


          .stat-value {
            font-size: 24px;
            font-weight: bold;
            color: #f8fafc;
          }


          /* ============================================================
            FOOTER
          ============================================================ */

          .footer {
            margin-top: 30px;

            text-align: center;

            color: #64748b;
            font-size: 13px;
          }


          /* ============================================================
            RESPONSIVE DESIGN
          ============================================================ */

          @media (max-width: 700px) {

            body {
              padding: 15px;
            }


            /* Header */

            .header h1 {
              font-size: 28px;
            }


            .subtitle {
              font-size: 15px;
            }


            /* Dashboard */

            .dashboard {
              grid-template-columns: 1fr;
            }


            /* Device Information */

            .device-info {
              grid-template-columns: 1fr;
            }


            /* Sensor Cards */

            .card {
              padding: 25px;
            }


            .value {
              font-size: 30px;
            }


            /* Graphs */

            .graph-grid {
              grid-template-columns: 1fr;
            }


            /* Statistics */

            .statistics-grid {
              grid-template-columns: 1fr;
            }

          }
        </style>
      </head>


      <body>

        <div class="container">

          <!-- ============================================================
              HEADER
          ============================================================= -->

          <header class="header">

            <h1>ESP32 Weather Station</h1>

            <p class="subtitle">
              Live Environmental Monitoring
            </p>

          </header>


          <!-- ============================================================
              LIVE SENSOR DASHBOARD
          ============================================================= -->

          <section class="dashboard">

            <!-- Temperature -->

            <div class="card">

              <div class="card-title">
                🌡️ Temperature
              </div>

              <div class="value" id="temperature">
                -- °C
              </div>

            </div>


            <!-- Pressure -->

            <div class="card">

              <div class="card-title">
                🌬️ Pressure
              </div>

              <div class="value" id="pressure">
                -- hPa
              </div>

            </div>


            <!-- Time -->

            <div class="card">

              <div class="card-title">
                🕒 Time
              </div>

              <div class="value" id="time">
                --:--:--
              </div>

            </div>


            <!-- Date -->

            <div class="card">

              <div class="card-title">
                📅 Date
              </div>

              <div class="value" id="date">
                --/--/----
              </div>

            </div>

          </section>


          <!-- ============================================================
              DEVICE STATUS
          ============================================================= -->

          <section class="device-section">

            <h2 class="section-title">
              Device Status
            </h2>


            <div class="device-info">

              <!-- Wi-Fi Signal -->

              <div class="info-box">

                <div class="info-title">
                  📶 Wi-Fi Signal
                </div>

                <div class="info-value" id="wifiSignal">
                  -- dBm
                </div>

                <div class="signal-quality" id="signalQuality">
                  Checking...
                </div>

              </div>


              <!-- System Uptime -->

              <div class="info-box">

                <div class="info-title">
                  ⏱️ Uptime
                </div>

                <div class="info-value" id="uptime">
                  00:00:00
                </div>

              </div>


              <!-- System Status -->

              <div class="info-box">

                <div class="info-title">
                  🔄 System
                </div>

                <div class="info-value" id="systemStatus">
                  Connecting...
                </div>

              </div>

            </div>


            <!-- Connection Status -->

            <div class="system-status">

              <div class="status" id="status">
                ● ESP32 Connecting...
              </div>

            </div>


            <!-- Last Updated -->

            <div class="last-updated" id="lastUpdated">
              Last update: Waiting for data...
            </div>

          </section>


          <!-- ============================================================
              SENSOR HISTORY
          ============================================================= -->

          <section class="history-section">

            <h2 class="section-title">
              Sensor History
            </h2>


            <div class="graph-grid">

              <!-- Temperature History -->

              <div class="graph-card">

                <h3>
                  🌡️ Temperature History
                </h3>

                <canvas id="temperatureChart"></canvas>

              </div>


              <!-- Pressure History -->

              <div class="graph-card">

                <h3>
                  🌬️ Pressure History
                </h3>

                <canvas id="pressureChart"></canvas>

              </div>

            </div>

          </section>


          <!-- ============================================================
              SENSOR STATISTICS
          ============================================================= -->

          <section class="statistics-section">

            <h2 class="section-title">
              Sensor Statistics
            </h2>


            <div class="statistics-grid">

              <!-- Minimum Temperature -->

              <div class="stat-card">

                <div class="stat-label">
                  🌡️ Minimum Temperature
                </div>

                <div class="stat-value" id="minTemperature">
                  -- °C
                </div>

              </div>


              <!-- Maximum Temperature -->

              <div class="stat-card">

                <div class="stat-label">
                  🌡️ Maximum Temperature
                </div>

                <div class="stat-value" id="maxTemperature">
                  -- °C
                </div>

              </div>


              <!-- Average Temperature -->

              <div class="stat-card">

                <div class="stat-label">
                  📊 Average Temperature
                </div>

                <div class="stat-value" id="avgTemperature">
                  -- °C
                </div>

              </div>


              <!-- Minimum Pressure -->

              <div class="stat-card">

                <div class="stat-label">
                  🌬️ Minimum Pressure
                </div>

                <div class="stat-value" id="minPressure">
                  -- hPa
                </div>

              </div>


              <!-- Maximum Pressure -->

              <div class="stat-card">

                <div class="stat-label">
                  🌬️ Maximum Pressure
                </div>

                <div class="stat-value" id="maxPressure">
                  -- hPa
                </div>

              </div>


              <!-- Average Pressure -->

              <div class="stat-card">

                <div class="stat-label">
                  📊 Average Pressure
                </div>

                <div class="stat-value" id="avgPressure">
                  -- hPa
                </div>

              </div>

            </div>

          </section>


          <!-- ============================================================
              FOOTER
          ============================================================= -->

          <footer class="footer">

            ESP32 Web Dashboard • Live Sensor Monitoring

          </footer>

        </div>


        <script>

          // ============================================================
          // DASHBOARD HELPER FUNCTIONS
          // ============================================================


          // ------------------------------------------------------------
          // Format uptime from seconds to HH:MM:SS
          // ------------------------------------------------------------

          function formatUptime(seconds) {

            const hours = Math.floor(seconds / 3600);

            const minutes = Math.floor(
              (seconds % 3600) / 60
            );

            const secs = seconds % 60;


            return (
              String(hours).padStart(2, "0")
              + ":"
              + String(minutes).padStart(2, "0")
              + ":"
              + String(secs).padStart(2, "0")
            );

          }


          // ------------------------------------------------------------
          // Get Wi-Fi signal quality from RSSI
          // ------------------------------------------------------------

          function getSignalQuality(rssi) {

            if (rssi >= -50) {

              return "Excellent Signal";

            }

            if (rssi >= -60) {

              return "Good Signal";

            }

            if (rssi >= -70) {

              return "Fair Signal";

            }

            return "Weak Signal";

          }


          // ------------------------------------------------------------
          // Get current browser time
          // ------------------------------------------------------------

          function getCurrentTime() {

            const now = new Date();

            return now.toLocaleTimeString();

          }


          // ============================================================
          // CHART VARIABLES
          // ============================================================

          let temperatureChart;
          let pressureChart;


          // ============================================================
          // CHART INITIALIZATION
          // ============================================================

          function initCharts() {

            const temperatureContext =
              document
                .getElementById("temperatureChart")
                .getContext("2d");


            const pressureContext =
              document
                .getElementById("pressureChart")
                .getContext("2d");


            // ----------------------------------------------------------
            // Temperature Chart
            // ----------------------------------------------------------

            temperatureChart = new Chart(
              temperatureContext,
              {

                type: "line",

                data: {

                  labels: [],

                  datasets: [

                    {

                      label: "Temperature (°C)",

                      data: [],

                      borderWidth: 2,

                      tension: 0.3,

                      fill: false

                    }

                  ]

                },

                options: {

                  responsive: true,

                  maintainAspectRatio: false,

                  animation: false

                }

              }
            );


            // ----------------------------------------------------------
            // Pressure Chart
            // ----------------------------------------------------------

            pressureChart = new Chart(
              pressureContext,
              {

                type: "line",

                data: {

                  labels: [],

                  datasets: [

                    {

                      label: "Pressure (hPa)",

                      data: [],

                      borderWidth: 2,

                      tension: 0.3,

                      fill: false

                    }

                  ]

                },

                options: {

                  responsive: true,

                  maintainAspectRatio: false,

                  animation: false

                }

              }
            );

          }


          // ============================================================
          // LIVE SENSOR DATA
          // ============================================================

          function updateDashboard() {

            fetch("/api/data")

              .then(response => {

                if (!response.ok) {

                  throw new Error(
                    "API request failed"
                  );

                }

                return response.json();

              })


              .then(data => {

                // ------------------------------------------------------
                // Temperature
                // ------------------------------------------------------

                document.getElementById(
                  "temperature"
                ).textContent =
                  data.temperature + " °C";


                // ------------------------------------------------------
                // Pressure
                // ------------------------------------------------------

                document.getElementById(
                  "pressure"
                ).textContent =
                  data.pressure + " hPa";


                // ------------------------------------------------------
                // Time
                // ------------------------------------------------------

                document.getElementById(
                  "time"
                ).textContent =
                  data.time;


                // ------------------------------------------------------
                // Date
                // ------------------------------------------------------

                document.getElementById(
                  "date"
                ).textContent =
                  data.date;


                // ------------------------------------------------------
                // Wi-Fi Signal
                // ------------------------------------------------------

                document.getElementById(
                  "wifiSignal"
                ).textContent =
                  data.wifiSignal + " dBm";


                // ------------------------------------------------------
                // Wi-Fi Quality
                // ------------------------------------------------------

                document.getElementById(
                  "signalQuality"
                ).textContent =
                  getSignalQuality(
                    data.wifiSignal
                  );


                // ------------------------------------------------------
                // Uptime
                // ------------------------------------------------------

                document.getElementById(
                  "uptime"
                ).textContent =
                  formatUptime(
                    data.uptime
                  );


                // ------------------------------------------------------
                // System Status
                // ------------------------------------------------------

                document.getElementById(
                  "systemStatus"
                ).textContent =
                  data.wifi;


                // ------------------------------------------------------
                // Connection Status
                // ------------------------------------------------------

                const statusElement =
                  document.getElementById(
                    "status"
                  );


                if (data.wifi === "Connected") {

                  statusElement.textContent =
                    "● ESP32 Online";

                  statusElement.style.background =
                    "rgba(34, 197, 94, 0.15)";

                  statusElement.style.color =
                    "#4ade80";

                }

                else {

                  statusElement.textContent =
                    "● ESP32 Reconnecting...";

                  statusElement.style.background =
                    "rgba(234, 179, 8, 0.15)";

                  statusElement.style.color =
                    "#facc15";

                }


                // ------------------------------------------------------
                // Last Updated
                // ------------------------------------------------------

                document.getElementById(
                  "lastUpdated"
                ).textContent =
                  "Last successful update: "
                  + getCurrentTime();

              })


              .catch(error => {

                console.log(
                  "Dashboard update failed:",
                  error
                );


                const statusElement =
                  document.getElementById(
                    "status"
                  );


                statusElement.textContent =
                  "● Connection Lost";

                statusElement.style.background =
                  "rgba(239, 68, 68, 0.15)";

                statusElement.style.color =
                  "#f87171";


                document.getElementById(
                  "systemStatus"
                ).textContent =
                  "Reconnecting...";

              });

          }


          // ============================================================
          // HISTORY DATA
          // ============================================================

          function fetchHistoryData() {

            fetch("/api/history")

              .then(response => {

                if (!response.ok) {

                  throw new Error(
                    "History API request failed"
                  );

                }

                return response.json();

              })


              .then(data => {

                // Do nothing until valid history exists
                if (!data || data.length === 0) {

                  console.log(
                    "No history data available."
                  );

                  return;

                }


                // ------------------------------------------------------
                // Extract Time Labels
                // ------------------------------------------------------

                const labels =
                  data.map(
                    item => item.time
                  );


                // ------------------------------------------------------
                // Extract Temperature Values
                // ------------------------------------------------------

                const temperatures =
                  data.map(
                    item => Number(item.temperature)
                  );


                // ------------------------------------------------------
                // Extract Pressure Values
                // ------------------------------------------------------

                const pressures =
                  data.map(
                    item => Number(item.pressure)
                  );


                // ------------------------------------------------------
                // Update Charts
                // ------------------------------------------------------

                updateTemperatureGraph(
                  labels,
                  temperatures
                );


                updatePressureGraph(
                  labels,
                  pressures
                );


                // ------------------------------------------------------
                // Update Statistics
                // ------------------------------------------------------

                updateStatistics(data);

              })


              .catch(error => {

                console.log(
                  "History update failed:",
                  error
                );

              });

          }


          // ============================================================
          // TEMPERATURE GRAPH
          // ============================================================

          function updateTemperatureGraph(
            labels,
            temperatures
          ) {

            temperatureChart.data.labels =
              labels;

            temperatureChart.data.datasets[0].data =
              temperatures;

            temperatureChart.update();

          }


          // ============================================================
          // PRESSURE GRAPH
          // ============================================================

          function updatePressureGraph(
            labels,
            pressures
          ) {

            pressureChart.data.labels =
              labels;

            pressureChart.data.datasets[0].data =
              pressures;

            pressureChart.update();

          }


          // ============================================================
          // SENSOR STATISTICS
          // ============================================================

          function updateStatistics(data) {

            if (!data || data.length === 0) {

              return;

            }


            // ----------------------------------------------------------
            // Temperature Values
            // ----------------------------------------------------------

            const temperatures =
              data.map(
                item => Number(item.temperature)
              );


            const minTemperature =
              Math.min(...temperatures);


            const maxTemperature =
              Math.max(...temperatures);


            const avgTemperature =
              temperatures.reduce(
                (sum, value) => sum + value,
                0
              ) / temperatures.length;


            // ----------------------------------------------------------
            // Pressure Values
            // ----------------------------------------------------------

            const pressures =
              data.map(
                item => Number(item.pressure)
              );


            const minPressure =
              Math.min(...pressures);


            const maxPressure =
              Math.max(...pressures);


            const avgPressure =
              pressures.reduce(
                (sum, value) => sum + value,
                0
              ) / pressures.length;


            // ----------------------------------------------------------
            // Update Temperature Statistics
            // ----------------------------------------------------------

            document.getElementById(
              "minTemperature"
            ).textContent =
              minTemperature.toFixed(2) + " °C";


            document.getElementById(
              "maxTemperature"
            ).textContent =
              maxTemperature.toFixed(2) + " °C";


            document.getElementById(
              "avgTemperature"
            ).textContent =
              avgTemperature.toFixed(2) + " °C";


            // ----------------------------------------------------------
            // Update Pressure Statistics
            // ----------------------------------------------------------

            document.getElementById(
              "minPressure"
            ).textContent =
              minPressure.toFixed(2) + " hPa";


            document.getElementById(
              "maxPressure"
            ).textContent =
              maxPressure.toFixed(2) + " hPa";


            document.getElementById(
              "avgPressure"
            ).textContent =
              avgPressure.toFixed(2) + " hPa";

          }


          // ============================================================
          // DASHBOARD INITIALIZATION
          // ============================================================


          // Initialize charts first
          initCharts();


          // Load current data immediately
          updateDashboard();


          // Load history immediately
          fetchHistoryData();


          // ============================================================
          // PERIODIC UPDATES
          // ============================================================


          // Update live data every 2 seconds
          setInterval(
            updateDashboard,
            2000
          );


          // Update history and statistics every 10 seconds
          setInterval(
            fetchHistoryData,
            10000
          );

        </script>


      </body>

    </html>

  )rawliteral";


    server.send(
      200,
      "text/html",
      html
    );

}

// ============================================================
// LIVE SENSOR DATA API
// ============================================================

void handleSensorData() {

  String json = "{";


  json += "\"temperature\":";
  json += String(
    temperature,
    2
  );


  json += ",\"pressure\":";
  json += String(
    pressure,
    2
  );


  json += ",\"time\":\"";
  json += currentTime;
  json += "\"";


  json += ",\"date\":\"";
  json += currentDate;
  json += "\"";


  json += ",\"wifi\":\"";

  json += (
    WiFi.status() == WL_CONNECTED
    ? "Connected"
    : "Disconnected"
  );

  json += "\"";


  json += ",\"wifiSignal\":";


  if (WiFi.status() == WL_CONNECTED) {

    json += String(
      WiFi.RSSI()
    );

  } else {

    json += "0";

  }


  json += ",\"uptime\":";
  json += String(
    millis() / 1000
  );


  json += "}";


  server.send(
    200,
    "application/json",
    json
  );

}


// ============================================================
// SENSOR HISTORY API
// ============================================================

void handleHistoryData() {

  String json = "[";


  // Determine the oldest reading
  int startIndex;


  if (historyCount < MAX_HISTORY) {

    startIndex = 0;

  } else {

    startIndex = historyIndex;

  }


  // Send readings in chronological order
  for (
    int i = 0;
    i < historyCount;
    i++
  ) {

    int index =
      (startIndex + i) % MAX_HISTORY;


    json += "{";


    json += "\"temperature\":";
    json += String(
      history[index].temperature,
      2
    );


    json += ",\"pressure\":";
    json += String(
      history[index].pressure,
      2
    );


    json += ",\"time\":\"";
    json += history[index].time;
    json += "\"";


    json += "}";


    // Add comma between readings
    if (i < historyCount - 1) {

      json += ",";

    }

  }


  json += "]";


  server.send(
    200,
    "application/json",
    json
  );

}


// ============================================================
// SERIAL MONITOR OUTPUT
// ============================================================

void printSensorData() {

  Serial.print("Time: ");
  Serial.println(currentTime);


  Serial.print("Date: ");
  Serial.println(currentDate);


  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" C");


  Serial.print("Pressure: ");
  Serial.print(pressure, 2);
  Serial.println(" hPa");


  Serial.println(
    "----------------"
  );

}
