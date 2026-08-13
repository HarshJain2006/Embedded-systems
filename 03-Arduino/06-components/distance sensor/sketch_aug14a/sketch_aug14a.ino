
#define TRIG_PIN 9
#define ECHO_PIN 10

#define LED_CLOSE 2
#define LED_MED   3
#define LED_FAR   4

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  pinMode(LED_CLOSE, OUTPUT);
  pinMode(LED_MED, OUTPUT);
  pinMode(LED_FAR, OUTPUT);
}

void loop() {
  // Send trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo time
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance
  float distance = (duration * 0.0343) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // LED control based on distance
  if (distance < 10) { // Very close
    digitalWrite(LED_CLOSE, HIGH);
    digitalWrite(LED_MED, LOW);
    digitalWrite(LED_FAR, LOW);
  } 
  else if (distance < 30) { // Medium range
    digitalWrite(LED_CLOSE, LOW);
    digitalWrite(LED_MED, HIGH);
    digitalWrite(LED_FAR, LOW);
  } 
  else { // Far
    digitalWrite(LED_CLOSE, LOW);
    digitalWrite(LED_MED, LOW);
    digitalWrite(LED_FAR, HIGH);
  }

  delay(200);
}
