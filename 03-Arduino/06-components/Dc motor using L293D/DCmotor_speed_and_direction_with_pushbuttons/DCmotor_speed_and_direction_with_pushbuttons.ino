int speedpin = 5;     
int dir1 = 4;           
int dir2 = 3;          
int bp1 = 8;            
int bp2 = 9;            
int b1val;
int b2val;
int mspeed = 0;
int dt = 500;


void speedcontrol(int speed) {

  if (speed > 255) speed = 255;
  if (speed < -255) speed = -255;

  if (speed == 0) {
    // Stop: choose both dir pins LOW for a defined stop state
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
    analogWrite(speedpin, 0);
  } else if (speed > 0) {
    // Forward
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, HIGH);
    analogWrite(speedpin, speed);
  } else { // speed < 0
    // Reverse
    digitalWrite(dir1, HIGH);
    digitalWrite(dir2, LOW);
    analogWrite(speedpin, abs(speed));
  }
}

void setup() {
  pinMode(speedpin, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);

  // Use internal pull-ups for the pushbuttons
  pinMode(bp1, INPUT_PULLUP);
  pinMode(bp2, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  b1val = digitalRead(bp1);
  b2val = digitalRead(bp2);

  if (b1val == LOW) {
    mspeed = mspeed - 10;
    delay(dt);
  }
  if (b2val == LOW) {
    mspeed = mspeed + 10;
    delay(dt);
  }

  // Ensure mspeed remains in valid range before applying
  if (mspeed > 255) mspeed = 255;
  if (mspeed < -255) mspeed = -255;

  // Apply motor control
  speedcontrol(mspeed);

  Serial.print("mspeed = ");
  Serial.println(mspeed);
}

}
