String msg = "Enter the number of blinks: ";
String msg2 = " led is blinking:";
int numblinks;
int ledpin = 13;
int wt = 500;

float r;
String msgAr="what is the radius of circle: ";
float area;
String msgAr2=" your circle area is : ";
float pi=3.14;
void asknum(){
  Serial.println(msg);
  while (Serial.available() == 0) {}
  numblinks = Serial.parseInt();
}
void blinkled(int numblinks) {

  for (int j = 1; j <= numblinks; j++) {
    digitalWrite(ledpin, HIGH);
    delay(wt);
    digitalWrite(ledpin, LOW);
    delay(wt);
  }
}

void findarea(){
  Serial.println(msgAr);
  while (Serial.available() == 0) {}
  r = Serial.parseFloat();
  area = pi*r*r;
  Serial.print(msgAr2);
  Serial.println(area);
  
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledpin,OUTPUT);
}

void loop() {
  // asknum(); 
  // Serial.println(msg2);
  // blinkled(numblinks);

  findarea();
}
