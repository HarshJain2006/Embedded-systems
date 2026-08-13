int tiltpin=2;
int tiltval;
int redpin=4;
int greenpin=5;
void setup()
{
  pinMode(tiltpin,INPUT);
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  digitalWrite(tiltpin,HIGH);
  Serial.begin(9600);
}

void loop()
{
  tiltval=digitalRead(tiltpin);
  Serial.println(tiltval);
  if(tiltval==0){
  	digitalWrite(greenpin,HIGH);
    digitalWrite(redpin,LOW);
  }
  if(tiltval==1){
  	digitalWrite(greenpin,LOW);
    digitalWrite(redpin,HIGH);
  }
  
}