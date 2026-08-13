#include <Servo.h>

int servopin = 6;
int servopos =0;
int lightpin=A4;
int photoval;
int angle;
Servo myservo;
int dt=250;

void setup()
{
  Serial.begin(9600);
  myservo.attach(servopin);
  pinMode(lightpin,INPUT);
  pinMode(servopin,OUTPUT);
  
}
void askservo(){
  Serial.print("what angle you want");
  while(Serial.available()==0){}
  servopos=Serial.parseInt();
  myservo.write(servopos);
}

void readphotoval(){
  photoval= analogRead(lightpin);
  //float volt = photoval * (5.0 / 1023.0);
  //Serial.print("voltage is: ");
  //Serial.println(volt);
  Serial.println(photoval);
  
}
void moveangle(){
  angle=(-0.265*photoval+271.193);
  myservo.write(angle);
  Serial.println(angle);
  
}
void loop()
{
  //askservo();
  readphotoval();
  moveangle();
  delay(dt);
}