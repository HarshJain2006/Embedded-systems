int lightpin =A5;
int redpin = 6;
int greenpin = 5;
int buzzpin =4;
int photoval;
int dt=200;

int delayt;

void setup()
{
  pinMode(lightpin, INPUT);
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(buzzpin, OUTPUT);
  Serial.begin(9600);
}

void readphotoval(){
  photoval= analogRead(lightpin);
  float volt = photoval * (5.0 / 1023.0);
  Serial.print("voltage is: ");
  Serial.println(volt);
  
}
void ledindicat(){
	if(photoval>500){
  	digitalWrite(redpin,HIGH);
    digitalWrite(greenpin,LOW);
  }
  else{
    digitalWrite(redpin,LOW);
    digitalWrite(greenpin,HIGH);
  }
}

void buzztone(){
  	delayt = map(photoval, 0, 1023, 50, 500);
  	digitalWrite(buzzpin,HIGH);
  	delay(delayt);
  	digitalWrite(buzzpin,LOW);
  	delay(delayt);
}
void loop()
{
  readphotoval();
  ledindicat();
  buzztone();
  
}