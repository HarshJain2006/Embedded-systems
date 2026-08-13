# Arduino Learning Journey 🔧

This section documents my hands-on learning with **Arduino**, starting from basic microcontroller programming and gradually moving toward hardware interfacing, communication, sensors, actuators, and small embedded projects.

The purpose of this phase was not only to learn how to write Arduino programs, but to understand how software interacts with hardware.

---

## 🎯 What I Learned

### 01 — Basics

* Arduino program structure
* `setup()` and `loop()`
* Digital input/output
* `digitalRead()`
* `digitalWrite()`
* Serial Monitor
* Reading numbers and strings through Serial
* Basic debugging

### 02 — Analog & ADC

* Analog input
* `analogRead()`
* ADC concept
* Potentiometer
* LDR / photoresistor
* Converting ADC values into meaningful values
* Mapping sensor values

### 03 — Actuators

* LEDs
* PWM
* LED brightness control
* Buzzers
* Tone generation
* Servo motors
* Controlling servo position
* Basic actuator interfacing

### 04 — Displays

* 16×2 LCD
* LCD interfacing
* I2C LCD
* Displaying sensor and program data
* Understanding basic display communication

### 05 — Communication

* Serial communication
* UART fundamentals
* I2C fundamentals
* Communication between Arduino and peripherals

### 06 — Components & Interfacing

* Sensors
* Joystick
* Servo motors
* Shift registers
* 74HC595
* LEDs
* Buzzers
* LCD displays

---

## 🧪 Experiments

Some of the experiments completed during this phase include:

* LED control
* Serial input and output
* Potentiometer ADC reading
* LDR / light sensing
* Voltage measurement
* LED brightness control
* RGB LED control
* Buzzer experiments
* Servo control
* Joystick-controlled servo
* Binary counter
* 74HC595 shift register
* LCD interfacing
* I2C LCD
* Sensor interfacing

---

## 🚀 Projects

The projects folder contains larger experiments where multiple concepts were combined.

| Project             | Concepts                       |
| ------------------- | ------------------------------ |
| Calculator          | LCD, keypad/input, logic       |
| Servo Controller    | Joystick, ADC, PWM, servo      |
| Binary Counter      | Digital I/O, binary logic      |
| Sensor Monitoring   | Sensors, ADC, LCD              |
| Other Mini Projects | Hardware interfacing & control |

More projects will be added as I continue learning.

---

## 🧠 What This Phase Taught Me

The Arduino phase helped me understand the basic relationship between:

```text
Input
  ↓
Microcontroller
  ↓
Processing / Logic
  ↓
Output
```

For example:

```text
Sensor → ADC → Arduino → Processing → LCD / Actuator
```

This became the foundation for moving toward more advanced microcontrollers and embedded systems.

---

## 🔍 Concepts I Want to Understand Deeper

Arduino makes hardware programming accessible, but the next step is understanding what happens underneath the Arduino abstractions.

Topics I want to explore further:

* Microcontroller architecture
* Registers
* GPIO registers
* ADC registers
* Timers and counters
* Interrupts
* UART hardware
* I2C hardware
* SPI hardware
* Memory architecture
* Embedded C
* Bare-metal programming
* RTOS

---

## 🛠️ Tools Used

* Arduino
* Arduino IDE
* Tinkercad
* Wokwi
* VS Code
* Git & GitHub

---

## 📈 Progression

My learning path is progressing from:

```text
Arduino
   ↓
Embedded C
   ↓
ESP32 / ESP8266
   ↓
Microcontroller Architecture
   ↓
STM32
   ↓
Communication Protocols
   ↓
RTOS / Advanced Embedded Systems
```

---

## 📌 Philosophy

> Learn the concept → build it → debug it → understand what happens underneath → improve it.

Arduino is my starting point for building a stronger foundation in Embedded Systems.
