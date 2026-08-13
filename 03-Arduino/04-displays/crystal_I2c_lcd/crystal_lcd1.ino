#include <LiquidCrystal.h>
int rs=12;
int en=11;
int d4=5;
int d5=4;
int d6=3;
int d7=2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
int seconds =0;

float firstnum;
float secnum;
float ans;

String op;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2); // Set up the number of columns and rows on the LCD.

  // Print a message to the LCD.
  lcd.print("Hello world!");
  delay(2000);
  
}
void counter(){
  delay(1000);	 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Harsh jain");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(seconds);
  delay(1000); 
  seconds += 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Watch the count");
  for(int j=1;j<=10;j++){
    lcd.setCursor(0,1);
    lcd.print(j);
    delay(500);
  }
}
void calculator(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Input num1");
  while(Serial.available()==0){
  Serial.println("enter num1: ");
  };
  
  firstnum= Serial.parseFloat();
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Input num2");
  while(Serial.available()==0){
  Serial.println("enter num2: ");
  };
  
  secnum= Serial.parseFloat();
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Input(+,-,*,/)");
  while(Serial.available()==0){
  	Serial.println("Select operator: ");
  };
  op= Serial.readString();
  if(op=="+"){
  	ans=firstnum+secnum;
  }
  if(op=="-"){
  	ans=firstnum-secnum;
  }
  if(op=="*"){
  	ans=firstnum*secnum;
  }
  if(op=="/"){
  	ans=firstnum/secnum;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(firstnum);
  lcd.print(op);
  lcd.print(secnum);
  lcd.print("=");
  lcd.print(ans);
  delay(5000);
  lcd.clear();
}
void loop()
{
  //counter();
  calculator();
}