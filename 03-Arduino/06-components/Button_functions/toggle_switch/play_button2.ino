int ledstate=0;
int ledpin=7;
int buttonpin=9;
int buttonnew;
int buttonold=1;
int dt=100;

void setup()
{
  pinMode(ledpin, OUTPUT);
  pinMode(buttonpin, INPUT);
  Serial.begin(9600);
  
}
void toggleswitch(){
  buttonnew=digitalRead(buttonpin);
  if(buttonold==0 && buttonnew==1){
    if(ledstate==0){
    	digitalWrite(ledpin,HIGH);
      	ledstate=1;
    }
    else{
    	digitalWrite(ledpin,LOW);
      	ledstate=0; 
    }
  }
  buttonold=buttonnew;
  delay(dt);
}
void loop()
{
 toggleswitch();
 
}