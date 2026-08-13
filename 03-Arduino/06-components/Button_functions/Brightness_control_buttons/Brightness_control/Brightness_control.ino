int buttonpin1 =10;
int buttonpin2 = 11;
int ledpin =3;
int buzzpin=2;
int buttonval1;
int buttonval2;
int ledbright=0;
int dt =250;
void setup()
{
  pinMode(buttonpin1, INPUT);
  pinMode(buttonpin2, INPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(buzzpin, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  buttonval1=digitalRead(buttonpin1);
  buttonval2=digitalRead(buttonpin2);
  Serial.print("Button 1 = ");
  Serial.print(buttonval1);
  Serial.print(" , 	");
  Serial.print("Button 2 = ");
  Serial.println(buttonval2);
  delay(dt);
  if(buttonval1==0){
  ledbright=ledbright+5;
  }
  else if (buttonval2==0){
  	ledbright=ledbright-5;
  }
  Serial.print("Brightness: ");
  Serial.println(ledbright);
  
  if(ledbright>255){
  	ledbright=255;
    digitalWrite(buzzpin,HIGH);
    delay(dt);
    digitalWrite(buzzpin,LOW);
    Serial.println("Buzz HIGH");
    
  }
  if(ledbright<0){
  	ledbright=0;
    digitalWrite(buzzpin,HIGH);
    delay(dt);
    digitalWrite(buzzpin,LOW);
    Serial.println("Buzz LOW");
  }
  analogWrite(ledpin,ledbright);
}