#include <Servo.h>
Servo xservo ;
Servo yservo ;
int xpin = A0;
int ypin = A1;
int spin = 2;
int xspin= 9;
int yspin =10;
int buzzpin=12;
int WVx;
int WVy;
int xval ;
int yval;
int sval;
int dt =20;


void readjoystick(){
  xval=analogRead(xpin);
  yval=analogRead(ypin);
  sval=digitalRead(spin);
  //delay(dt);
  Serial.print("X value = ");
  Serial.print(xval);
  Serial.print(" Y value = ");
  Serial.print(yval);
  Serial.print(" Switch State is ");
  Serial.println(sval);
}
// Servo Movement Logic
void moveservo(){
  //WVx = (180./1023.)*xval;
  //WVy = (180./1023.)*yval;

  // Map joystick values to servo angles
  WVx = map(xval, 0, 1023, 0, 180);
  WVy = map(yval, 0, 1023, 0, 180);
  // Move servos
  xservo.write(WVx);
  yservo.write(WVy);
  // Buzzer feedback on joystick press
  if(sval==0){
    digitalWrite(buzzpin, HIGH);
  }
  else{
    digitalWrite(buzzpin, LOW);
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(xpin,INPUT);
  pinMode(ypin,INPUT);
  pinMode(spin,INPUT);
  pinMode(xspin,OUTPUT);
  pinMode(yspin,OUTPUT);
  pinMode(buzzpin,OUTPUT);
  xservo.attach(xspin);
  yservo.attach(yspin);
  digitalWrite(spin,HIGH);
}

void loop() {
  readjoystick();
  delay(dt);
  moveservo();
}

