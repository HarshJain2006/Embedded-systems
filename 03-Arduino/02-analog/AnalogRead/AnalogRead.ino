int myvoltpin = A2;
int readval;
float v2;
int wait = 250;

void setup()
{
  Serial.begin(9600);
  pinMode(myvoltpin,INPUT);
  pinMode(ledpin,OUTPUT);
}

void loop()
{
  readval=analogRead(myvoltpin);
  v2 = (5./1023.)*readval;
  Serial.print("Potentiometer voltage is ");
  Serial.println(v2);
  delay(wait);
}