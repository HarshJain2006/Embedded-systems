const int BATTERY_PIN = A0;

// Calibration values
const float REFERENCE_VOLTAGE = 5.0; // Change to 3.3 if using a 3.3V Arduino
const int ADC_RESOLUTION = 1024;     // Standard 10-bit ADC

void setup() {
  Serial.begin(9600);
  pinMode(BATTERY_PIN, INPUT);
}

void loop() {
  // Read the raw ADC value (0 to 1023)
  int rawADC = analogRead(BATTERY_PIN);
  
  // Calculate actual voltage
  float batteryVoltage = (rawADC * REFERENCE_VOLTAGE) / ADC_RESOLUTION;
  
  // Print results
  Serial.print("Battery Voltage: ");
  Serial.print(batteryVoltage, 2);
  Serial.println(" V");
  
  delay(1000);
}
