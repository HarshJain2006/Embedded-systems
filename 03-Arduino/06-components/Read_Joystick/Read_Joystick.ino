int xpin = A0;
int ypin = A1;
int spin = 2;
int xval ;
int yval;
int sval;
int dt =200;

void readjoystick(){
  xval=analogRead(xpin);
  yval=analogRead(ypin);
  sval=digitalRead(spin);
  delay(dt);

  Serial.print("X value = ");
  Serial.print(xval);
  Serial.print(" Y value = ");
  Serial.print(yval);
  Serial.print(" Switch State is ");
  Serial.println(sval);
}
void setup() {
  Serial.begin(9600);
  pinMode(xpin,INPUT);
  pinMode(ypin,INPUT);
  pinMode(spin,INPUT);
  digitalWrite(spin,HIGH);
}

void loop() {
  readjoystick();
}
