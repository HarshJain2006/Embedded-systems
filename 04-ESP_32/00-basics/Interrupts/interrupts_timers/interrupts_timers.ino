#include <Arduino.h>
const uint8_t led = 16;
const uint8_t motionSensor = 17;

unsigned long now;
volatile unsigned long lastTrigger = 0;
volatile bool startTimer = false;

bool printMotion = false;

const unsigned long timeSeconds = 10 * 1000UL;  //20 seconds in milliseconds

void ARDUINO_ISR_ATTR motionISR() {
  lastTrigger = millis();
  startTimer = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(motionSensor, motionISR, RISING);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  now = millis();

// Turn LED on immediately on new trigger
  if (startTimer && !printMotion) {
    digitalWrite(led, HIGH);
    Serial.println("MOTION DETECTED!!!");
    printMotion = true;
  }

// Turn off the LED after timeout
  if (startTimer && (now - lastTrigger > timeSeconds)) {
    Serial.println("Motion stopped...");
    digitalWrite(led, LOW);
    startTimer = false;
    printMotion = false;
  }
}