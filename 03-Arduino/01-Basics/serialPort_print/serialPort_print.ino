// int j=1;
int wait=750;
int a =6;
int b=6;
int c;
String mys=" + ";
float r=2;
float pi=3.14;
float area;

void setup() {
  // Serial.begin(9600);
  Serial.begin(115200);


}


void loop() {
  // c =a + b ;
  area = pi*r*r;
  Serial.println(area);
  // Serial.print(a);
  // Serial.print(mys);
  // Serial.print(b);
  // Serial.print(" = ");
  // Serial.println(c );
  delay(wait);
  r = r+0.5;

}
