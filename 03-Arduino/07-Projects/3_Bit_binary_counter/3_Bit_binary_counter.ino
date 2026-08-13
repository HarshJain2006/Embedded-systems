// apporach 1 --> 
// int led1=8;
// int led2=9;
int waitime =1000;

// void setup()
// {
//   pinMode(led1, OUTPUT);
//   pinMode(led2, OUTPUT);
// }

// void loop()
// {
//   // LED1 
//   digitalWrite(led1, HIGH);
//   digitalWrite(led2, LOW);
//   delay(waitime);

//   // LED2
//   digitalWrite(led1, LOW);
//   digitalWrite(led2, HIGH);
//   delay(waitime);

//   // BOTH
//   digitalWrite(led1, HIGH);
//   digitalWrite(led2, HIGH);
//   delay(waitime);

//   // OFF
//   digitalWrite(led1, LOW);
//   digitalWrite(led2, LOW);
//   delay(waitime);
// }



// Apporach 2 -->
// int leds[]={8,9,10};

// void setstats(int s0,int s1,int s2){
// 	digitalWrite(leds[2],s0);
//   	digitalWrite(leds[1],s1);
//   	digitalWrite(leds[0],s2);
// }
// void setup()
// {
//   for(int i = 0; i < 3; i++){
//     pinMode(leds[i], OUTPUT);
//   }
// }

// void loop()
// {
//   // 000
//   setstats(LOW,LOW,LOW);
//   delay(waitime);

//   // 001
//   setstats(LOW,LOW,HIGH);
//   delay(waitime);

//   // 010
//   setstats(LOW,HIGH,LOW);
//   delay(waitime);

//   // 011
//   setstats(LOW,HIGH,HIGH);
//   delay(waitime);
//   // 100
//   setstats(HIGH,LOW,LOW);
//   delay(waitime);
//   // 101
//   setstats(HIGH,LOW,HIGH);
//   delay(waitime);
//   // 110
//   setstats(HIGH,HIGH,LOW);
//   delay(waitime);
//    // 111
//   setstats(HIGH,HIGH,HIGH);
//   delay(waitime);
 
// }
// Apporach 3-->
int leds[]={8,9,10};

void setup()
{
  for(int i = 0; i < 3; i++){
    pinMode(leds[i], OUTPUT);
  }
}
 void loop()
{
  for(int i = 0; i < 8; i++){
    for(int bit = 0; bit < 3; bit++){
      digitalWrite(leds[bit], (i >> bit) & 1);
    }
    delay(waitime);
  }
}
