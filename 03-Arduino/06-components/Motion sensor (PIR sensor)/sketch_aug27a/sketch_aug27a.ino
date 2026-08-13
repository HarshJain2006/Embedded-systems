// PIR Motion Sensor with LED + Serial Output
const int ledPin = 12;  // LED pin
const int pirPin = 8;   // PIR sensor pin

int pirState = LOW;  
int val = 0;         
unsigned long timeNow;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);  
  Serial.begin(9600);

  Serial.println("PIR Sensor Ready...");
  delay(2000);  
  timeNow = millis();
}

void loop() {
  val = digitalRead(pirPin);
  
  if((millis() - timeNow)/1000 > 4 || pirState == LOW ) {
    timeNow = millis();
    if (val == HIGH) {  
      digitalWrite(ledPin, HIGH);

      if (pirState == LOW) {
        Serial.println("Motion detected!");
        pirState = HIGH;
      }
    } else {  
      digitalWrite(ledPin, LOW);

      if (pirState == HIGH) {
        Serial.println("Motion ended!");
        pirState = LOW;
      }
    }
  }

  delay(200);  
}
