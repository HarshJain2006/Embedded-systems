int ledpin=7;
int buttonpin=9;
int buttonval;
int dt=250;

void setup()
{
  pinMode(ledpin, OUTPUT);
  pinMode(buttonpin, INPUT);
  Serial.begin(9600);
  
}
void buttonread(){
	buttonval=digitalRead(buttonpin);
  	Serial.println(buttonval);
  	delay(dt);
}
void ledstate(){
  if(buttonval==0){
  	digitalWrite(ledpin,LOW);
  }
  else if(buttonval==1){
  digitalWrite(ledpin,HIGH);
  }
  else{
    Serial.println("ERROR");
  }
  
}
void loop()
{
 buttonread();
 ledstate();
  delay(dt);
 
}