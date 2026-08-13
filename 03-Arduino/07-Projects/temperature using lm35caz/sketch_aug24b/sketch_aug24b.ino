#define TEMP_PIN A0   // Sensor pin

#define LED_GREEN 2
#define LED_YELLOW 3
#define LED_RED 4

void setup() {
  Serial.begin(9600);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop() {
  // Read analog value
  int sensorValue = analogRead(TEMP_PIN);

  // Convert to voltage (assuming 5V and 10-bit ADC)
  float voltage = sensorValue * (5.0 / 1023.0);

  // LM35 gives 10mV per °C → Temp in Celsius
  float temperatureC = voltage * 100;

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // LED Indication (you can adjust thresholds)
  if (temperatureC < 19) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  } 
  else if (temperatureC < 23) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
  } 
  else {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
  }

  delay(500); // half second update
}
