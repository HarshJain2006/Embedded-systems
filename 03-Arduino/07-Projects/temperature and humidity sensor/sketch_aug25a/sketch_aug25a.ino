#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

#include <DHT.h> //Include the DHT library.

#define dataPin 6 //Define the type data pin
#define DHTType DHT11 //Define the DHT sensor (DHT11, DHT21, or DHT22)

//Instantiate the dht class with our data pin and DHT type.
DHT dht = DHT(dataPin, DHTType);

void setup() {
  Serial.begin(9600); //Start the serial interface on 9600
    dht.begin();   //Call the begin class in the dht object

      lcd.init();                      // initialize the lcd 
      lcd.init();
      lcd.backlight();
       lcd.setCursor(0,0);
       lcd.print("Welcome...");
}

void loop() {
  delay(2000); // Delay for 2 seconds
  float h = dht.readHumidity(); //read the humidity from the sensor
  
  float t = dht.readTemperature();  // Read temperature as Celsius (the default), insert true as a parameter for fahrenheit

  // Check for any errors, if there is, display error and restart.
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from the DHT sensor, check wiring.");
    return;
  }
  
  //Print out the humidity
  Serial.print("Humidity: ");
  Serial.print(h);
  
  //Print out the Temperature
  Serial.print("% || Temperature: ");
  Serial.print(t);
  Serial.print("°C ");
  
  //Print new line
  Serial.println();


       lcd.setCursor(0,0);
       lcd.print("Humidity:");
       lcd.setCursor(9,0);
       lcd.print(h);
       lcd.setCursor(15,0);
       lcd.print("%");
       lcd.setCursor(0,1);
       lcd.print("Temp:");
       lcd.setCursor(9,1);
       lcd.print(t);
       lcd.setCursor(15,1);
       lcd.print("C ");
}
