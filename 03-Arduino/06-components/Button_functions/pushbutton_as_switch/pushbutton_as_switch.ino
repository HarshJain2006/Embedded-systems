int buttonpin=2;
int buttonval;
int dt=200;

void setup() {
  pinMode(buttonpin,INPUT);
  digitalWrite(buttonpin,HIGH);
  Serial.begin(9600);
}

void loop() {
  buttonval=digitalRead(buttonpin);
  Serial.print("Button state is: ");
  Serial.println(buttonval);
  delay(dt);
}
