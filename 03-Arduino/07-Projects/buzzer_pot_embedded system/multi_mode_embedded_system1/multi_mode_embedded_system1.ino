int readPin=A4;
int buzzpin=12;

int mynum;
bool beepConfigured = false;
bool beepDone = false;
int value=0;
float volt;
int toneval;
int dt =300;

String mode="";

void playtone(String cmd){

  static int count = 0;

  // Ask user input
  if(!beepConfigured){
    Serial.println("Enter number of beeps: ");

    if(cmd != ""){
      mynum = cmd.toInt();

      if(mynum > 0){
        beepConfigured = true;
        beepDone = false;
      }
      else{
        Serial.println("Invalid number");
      }
    }
    return;
  }

  // Execute beeps
  if(!beepDone){
    if(count < mynum){
      digitalWrite(buzzpin, HIGH);
      delay(dt);
      digitalWrite(buzzpin, LOW);
      delay(dt);
      count++;
    }
    else{
      Serial.println("Beep complete");

      count = 0;
      beepConfigured = false;
      beepDone = false;
    }
  }
}
void readpot(){
  value = analogRead(readPin); 
  // Convert ADC to voltage
  volt = (5./1023.)*value;
  Serial.print("voltage  is ");
  Serial.println(volt);
}
void alertvolt(){
// voltage alert system
  readpot(); 
  if(volt>2.5){
  	digitalWrite(buzzpin,HIGH); 
  }
  else{
  digitalWrite(buzzpin,LOW);
  }
  delay(dt);
}

void generatetone(){
  value=analogRead(readPin);
  /*
  9toneval=(9940./1023.)*value+60;
  Serial.print("Tone value: ");
  Serial.println(toneval);
  digitalWrite(buzzpin, HIGH);
  delayMicroseconds(toneval);
  digitalWrite(buzzpin, LOW);
  delayMicroseconds(toneval);
  */
  toneval = map(value, 0, 1023, 100, 2000);

  Serial.print("Frequency: ");
  Serial.println(toneval);

  tone(buzzpin, toneval);
  delay(100);
}


void setup()
{
  pinMode(buzzpin, OUTPUT);
  pinMode(readPin, INPUT);
  Serial.begin(9600);
}
void loop()
{
  String cmd = "";

  //Read input once
  if(Serial.available() > 0){
    cmd = Serial.readStringUntil('\n');
    cmd.trim();
    cmd.toLowerCase();
  }

  //Mode selection
  if(mode == ""){
    Serial.println("Select mode: beep | alert | tone");

    if(cmd != ""){
      mode = cmd;
    }
    return;
  }

  // Exit works globally
  if(cmd == "exit"){
    Serial.println("Exiting mode...");
    mode = "";
    noTone(buzzpin);
    digitalWrite(buzzpin, LOW);

    beepConfigured = false;
    beepDone = false;
    return;
  }

  // Run modes
  if(mode == "beep"){
    playtone(cmd);
  }
  else if(mode == "alert"){
    alertvolt();
  }
  else if(mode == "tone"){
    generatetone();
  }
  else{
    Serial.println("Invalid mode");
    mode = "";
  }
}