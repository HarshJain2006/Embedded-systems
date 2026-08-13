void setup() {
  pinMode(13,OUTPUT);

}
void short_blink(int times){
  for(int i=0;i<times;i++){
    digitalWrite(13,HIGH);
    delay(200);
    digitalWrite(13,LOW); 
    delay(200);
  }
}
void long_blink(int times){
  for(int i=0;i<times;i++){
  digitalWrite(13,HIGH);
  delay(600);
  digitalWrite(13,LOW);
  delay(200);
  }
}
void blinkPattern(int shortCount, int longCount){
  short_blink(shortCount); //for "S"
  delay(600);
  long_blink(longCount); //for "O"
  delay(600);
  short_blink(shortCount); //for "S"
}

void loop() {
  blinkPattern(3, 3);
  delay(2000); // pause before repeating
}
  
