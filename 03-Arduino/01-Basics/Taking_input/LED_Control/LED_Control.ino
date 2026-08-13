String msg="what color of the Led ?";
String mycolor;

String msg2="your Led color is: ";
int redpin=12;
int greenpin=11;
int bluepin=10;
void setup()
{
  Serial.begin(9600);
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
}
void loop()
{
  Serial.println(msg);
  while(Serial.available()==0){}
  mycolor=Serial.readString();
  mycolor.trim();          // remove newline
  mycolor.toLowerCase();   // make lowercase
  Serial.print(msg2);
  Serial.println(mycolor);
  
  
  if(mycolor=="red"){
     digitalWrite(redpin,HIGH);
     digitalWrite(greenpin,LOW);
     digitalWrite(bluepin,LOW);
   }
  else if(mycolor=="green"){
     digitalWrite(redpin,LOW);
     digitalWrite(greenpin,HIGH);
     digitalWrite(bluepin,LOW);
   }
  else if(mycolor=="blue"){
     digitalWrite(redpin,LOW);
     digitalWrite(greenpin,LOW);
     digitalWrite(bluepin,HIGH);
   }
  else{
  	 Serial.println("Invalid input");
  }
}