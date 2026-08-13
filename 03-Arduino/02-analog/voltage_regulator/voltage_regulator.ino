int readPin = A0;
int value = 0;
float volt;
int ledpin[]={8,9,10};
int wait =500;

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 3; i++){
    pinMode(ledpin[i], OUTPUT);
  }
}

void readpot(int){
	value = analogRead(readPin); 
  // Convert ADC to voltage
  volt = (5./1023.)*value;
  Serial.print("voltage of potentiometer is ");
  Serial.println(volt);
}
void loop() {
  readpot(readPin); 
  //analogWrite(ledpin, brightness);
  if (volt<1 ){
    // very low voltage
    digitalWrite(ledpin[0],LOW);
    digitalWrite(ledpin[1],LOW);
    digitalWrite(ledpin[2],LOW);
  }
  else if(volt<2.5){
    //low voltage
    digitalWrite(ledpin[0],HIGH);
    digitalWrite(ledpin[1],LOW);
    digitalWrite(ledpin[2],LOW);
  }
  else if(volt<3.5){
    // medium voltage
     digitalWrite(ledpin[0],HIGH);
     digitalWrite(ledpin[1],HIGH);
     digitalWrite(ledpin[2],LOW);
  }
  else{
    // high voltage
    Serial.println("Voltage is High");
    digitalWrite(ledpin[0],HIGH);
    digitalWrite(ledpin[1],HIGH);
    digitalWrite(ledpin[2],HIGH);
  }
  delay(wait);
}
