//Examples
//byte mybyte=0;
byte mybyte=0x0;
//byte mybyte = 0xAB;
//byte mybyte=B00000000; //0
//byte mybyte=B00001111;   //F
//byte mybyte=B10001111;	//8F

int dt =500;

void convert(){
  Serial.print(mybyte,DEC);
  Serial.print("   ");
  Serial.print(mybyte,BIN);
  Serial.print("   ");
  Serial.println(mybyte,HEX);
  mybyte++;
  delay(dt);
}
void setup() {
  Serial.begin(9600);
}

void loop() {
  convert();
}
