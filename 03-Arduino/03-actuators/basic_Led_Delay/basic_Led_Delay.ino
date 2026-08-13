int red_led=10;
int yellow_led=9;
int green_led=8;

void setup()
{
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
}

void red_count(int count){
  int i=0;
  while(i<=count){
  	digitalWrite(red_led,HIGH);
    delay(100);
    digitalWrite(red_led,LOW);
    delay (100);
    i++;
  }
}
void yellow_count(int count){
  int i=0;
  while(i<=count){
  	digitalWrite(yellow_led,HIGH);
    delay(500);
    digitalWrite(yellow_led,LOW);
    delay (500);
    i++;
  }
}
void green_count(int count){
  int i=0;
  while(i<=count){
  	digitalWrite(green_led,HIGH);
    delay(7500);
    digitalWrite(green_led,LOW);
    delay (3000);
    i++;
  }
}

void loop()
{
  red_count(3);
  delay(500);
  
  yellow_count(3);
  delay(500);
  
  green_count(3);
  delay(500);
  
}
