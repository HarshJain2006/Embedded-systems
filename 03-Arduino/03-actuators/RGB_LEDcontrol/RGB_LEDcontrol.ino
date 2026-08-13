int redpin=10;
int greenpin=9 ;
int bluepin= 8;
String mycolor;
String msg="what color do you want? ";
int wt =500;


void rgb(int r,int g,int b){
	analogWrite(redpin,r);
    analogWrite(greenpin,g);
    analogWrite(bluepin,b);
}
void setup()
{
  Serial.begin(9600);
  pinMode(redpin,OUTPUT);
  pinMode(greenpin,OUTPUT);
  pinMode(bluepin,OUTPUT);
}

  
void loop()
{
  //Serial.println(msg);
  //while(Serial.available()==0){}
  
  //mycolor=Serial.readString();
  //mycolor.trim();
  //mycolor.toLowerCase();
  
  // if(mycolor=="red"){
  //   digitalWrite(redpin,HIGH);
  //   digitalWrite(greenpin,LOW);
  //   digitalWrite(bluepin,LOW);
  // }
  // else if(mycolor=="green"){
  	
  //   digitalWrite(redpin,LOW);
  //   digitalWrite(greenpin,HIGH);
  //   digitalWrite(bluepin,LOW);
  // }
  // else if(mycolor=="blue"){
  	
  //   digitalWrite(redpin,LOW);
  //   digitalWrite(greenpin,LOW);
  //   digitalWrite(bluepin,HIGH);
  // }
  // else if(mycolor=="aqua"){
  	
  //   analogWrite(redpin,0);
  //   analogWrite(greenpin,255);
  //   analogWrite(bluepin,255);
  // }
  // else if(mycolor=="off"){
  	
  //   digitalWrite(redpin,LOW);
  //   digitalWrite(greenpin,LOW);
  //   digitalWrite(bluepin,LOW);
  // }
  
  // else{
  // 	Serial.println("INVAILD INPUT");
  // }
  rgb(0,255,255);
  delay(wt);
  rgb(102,0,102);
  delay(wt);
  rgb(255,255,0);
  delay(wt);
  rgb(128,0,0);
  delay(wt);
  
}
