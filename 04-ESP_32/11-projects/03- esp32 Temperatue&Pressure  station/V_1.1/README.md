# ESP32 Temperature & Pressure Weather Station - V1.1

## 📌 Version Overview

Version 1.1 is a major upgrade to the original ESP32 Temperature & Pressure Weather Station.

While the core functionality of reading temperature and atmospheric pressure from the BMP280 sensor remains unchanged, this version expands the project into a more complete **local IoT monitoring system**.

V1.1 introduces Wi-Fi connectivity, automatic reconnection handling, NTP-based time synchronization, a real-time web dashboard, sensor history visualization, and sensor statistics.

The version was developed and tested feature by feature, with the goal of improving both system reliability and the user interface.

---

# ✨ New Features in V1.1

## 📶 Wi-Fi Connectivity

The ESP32 connects to a configured Wi-Fi network and allows the weather station dashboard to be accessed from devices connected to the same network.

The system monitors the Wi-Fi connection status during operation.

---

## 🔄 Automatic Wi-Fi Reconnection

A Wi-Fi reconnection system was implemented to improve reliability.

If the Wi-Fi connection is lost:

- The ESP32 continues running.
- Sensor monitoring continues.
- The OLED continues displaying sensor information.
- The system attempts to reconnect to the Wi-Fi network.
- Network features become available again after reconnection.

This allows the core weather station functionality to continue even when network connectivity is temporarily unavailable.

---

## 🕒 NTP Time Synchronization

V1.1 adds time synchronization using NTP.

Once the ESP32 connects to Wi-Fi, it synchronizes the current time and date.

The synchronized time is used for:

- Dashboard time display
- Date display
- Sensor history timestamps

The dashboard displays time in a **12-hour format**.

If Wi-Fi is unavailable during startup, the system continues operating and time synchronization can occur after Wi-Fi connectivity is restored.

---

## 🌐 Local Web Dashboard

V1.1 introduces a real-time local web dashboard hosted directly by the ESP32.

The dashboard can be accessed from devices connected to the same local network.

The dashboard displays:

- Live temperature
- Live atmospheric pressure
- Current time
- Current date
- Wi-Fi signal strength
- Wi-Fi signal quality
- Device uptime
- System connection status
- Last dashboard update time

The dashboard automatically requests updated information from the ESP32.

---

## 📡 Wi-Fi Signal Monitoring

The dashboard displays the current Wi-Fi signal strength in **dBm**.

The signal strength is also converted into a user-friendly signal quality indication.

This provides a quick indication of the ESP32's current network connection quality.

---

## ⏱️ Device Uptime Monitoring

The system calculates and displays how long the ESP32 has been running since the last restart.

The uptime information is displayed on the web dashboard.

This feature provides a simple indication of system runtime and stability.

---

## 📊 Sensor History System

V1.1 stores recent sensor readings in a circular history buffer.

Each stored reading contains:

- Temperature
- Atmospheric pressure
- Time

The history data is stored in RAM and is provided to the web dashboard.

Because the current history system uses RAM, the stored history is cleared when the ESP32 restarts.

---

## 📈 Temperature and Pressure Graphs

The stored sensor history is visualized on the web dashboard.

Two separate graphs are used:

- Temperature history graph
- Pressure history graph

The graphs allow changes in sensor values to be observed over time.

---

## 📉 Sensor Statistics

The dashboard calculates statistics from the stored sensor history.

### Temperature

- Minimum temperature
- Maximum temperature
- Average temperature

### Pressure

- Minimum pressure
- Maximum pressure
- Average pressure

The statistics are updated as new history data becomes available.

---

## 📱 Responsive Dashboard

The web dashboard was designed to work on both desktop and mobile devices.

The layout automatically adjusts based on screen size.

This allows the weather station to be monitored from:

- Computers
- Laptops
- Tablets
- Mobile phones

---

# 🔌 API Endpoints

## `/api/data`

Provides the current sensor and system information.

Example response:

```json
{
  "temperature": 30.27,
  "pressure": 978.91,
  "time": "12:30:35 AM",
  "date": "26/08/2026",
  "wifi": "Connected",
  "wifiSignal": -63,
  "uptime": 177
}
```

---

## `/api/history`

Provides the stored sensor history data.

The history data is used for:

- Temperature graph
- Pressure graph
- Minimum calculations
- Maximum calculations
- Average calculations

Example structure:

```json
[
  {
    "temperature": 31.53,
    "pressure": 978.43,
    "time": "01:36:19 AM"
  },
  {
    "temperature": 31.54,
    "pressure": 978.42,
    "time": "01:36:50 AM"
  }
]
```

---

# 🔄 V1.1 System Operation

```text
Power ON
   │
   ▼
Initialize ESP32
   │
   ├── Initialize SPI
   │
   ├── Initialize OLED
   │
   └── Initialize BMP280
            │
            ▼
Connect to Wi-Fi
            │
     ┌──────┴──────┐
     │             │
 Connected     Not Connected
     │             │
     ▼             ▼
Sync NTP      Continue System
Time          Operation
     │             │
     └──────┬──────┘
            │
            ▼
Start Web Server
            │
            ▼
Read BMP280 Data
            │
     ┌──────┴────────┐
     ▼               ▼
Temperature       Pressure
     │               │
     └──────┬────────┘
            │
            ▼
Update OLED Display
            │
            ▼
Store Reading in
History Buffer
            │
            ▼
Provide Data Through
API Endpoints
            │
            ▼
Update Web Dashboard
            │
            ▼
Repeat
```

---

# 📁 Version Files

```text
V_1.1/
│
├── V_1.1.ino
├── README.md
│
└── images/
    ├── hardware/
    ├── oled/
    └── dashboard/
```

The source code contains:

- ESP32 system initialization
- BMP280 sensor handling
- OLED display handling
- Wi-Fi connection handling
- Automatic Wi-Fi reconnection
- NTP time synchronization
- Web server handling
- API endpoints
- Sensor history buffer
- HTML dashboard
- CSS styling
- JavaScript data handling
- Sensor graph generation
- Sensor statistics calculation

---

# 🔧 Technologies Used

## Embedded System

- ESP32
- BMP280
- OLED Display
- SPI communication

## Software

- Arduino IDE
- Embedded C/C++

## Networking

- Wi-Fi
- Local Web Server
- HTTP
- JSON API

## Web Dashboard

- HTML
- CSS
- JavaScript
- Chart.js

---

# 🧪 Testing

The following functionality was tested during the development of V1.1:

- BMP280 sensor detection
- Temperature readings
- Pressure readings
- OLED initialization
- OLED sensor display
- Wi-Fi connection
- Wi-Fi disconnection handling
- Automatic Wi-Fi reconnection
- NTP time synchronization
- Time display
- Date display
- Web server access
- `/api/data` endpoint
- `/api/history` endpoint
- Live dashboard updates
- Wi-Fi signal display
- Device uptime display
- Temperature history graph
- Pressure history graph
- Minimum sensor statistics
- Maximum sensor statistics
- Average sensor statistics
- Dashboard responsiveness

All major V1.1 functionality was tested successfully.

---

# ⚠️ Current Limitations

The current V1.1 implementation has some limitations:

- Sensor history is stored in RAM.
- History is cleared after an ESP32 restart.
- Dashboard access is limited to the available local network.
- The system currently monitors only temperature and atmospheric pressure.
- No persistent data logging is implemented yet.
- No cloud connectivity is implemented yet.

These limitations provide possible areas for future development.

---

# 🚀 Improvements Over V1.0

V1.0 focused primarily on basic local environmental monitoring.

V1.1 expands the project with:

```text
V1.0
  │
  ▼
ESP32
  +
BMP280
  +
OLED
  +
Basic Temperature
and Pressure Monitoring

        │
        ▼

V1.1
  │
  ▼
ESP32
  +
BMP280
  +
OLED
  +
Wi-Fi
  +
Automatic Reconnection
  +
NTP Time
  +
Web Dashboard
  +
API Communication
  +
Sensor History
  +
Graphs
  +
Statistics
```

This transforms the project from a basic sensor monitoring system into a more complete local IoT monitoring application.

---

# 🎯 Learning Outcomes from V1.1

During the development of Version 1.1, the following concepts were explored and implemented:

- ESP32 Wi-Fi connectivity
- Wi-Fi reconnection handling
- NTP time synchronization
- ESP32 web server development
- HTTP communication
- JSON data formatting
- API endpoint creation
- Embedded backend and frontend communication
- Real-time dashboard updates
- HTML dashboard design
- CSS responsive design
- JavaScript data processing
- Chart-based data visualization
- Circular history buffers
- Sensor statistics calculation
- Embedded system debugging
- Incremental feature development

---

# 📸 Screenshots and Images

Project images and screenshots can be added to document:

- Complete hardware setup
- OLED display output
- Web dashboard
- Mobile dashboard

---

# ⭐ Version Status

🟢 **Stable**

Version 1.1 is currently the stable and tested version of the ESP32 Temperature & Pressure Weather Station.

Future development will continue from this stable version.

---

# 🔮 Next Version

## V1.2 - Planned Features

Possible features planned for the next version include:

- Pressure trend detection
- Temperature trend detection
- Weather condition indicator
- Dashboard alert system
- Automatic OLED screen rotation

---

**Part of the ESP32 Temperature & Pressure Weather Station project.**
