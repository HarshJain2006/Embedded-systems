const int buzzer = 8;

void setup() {
}

void loop() {

    for (int frequency = 500; frequency <= 2000; frequency += 100) {
        tone(buzzer, frequency);
        delay(100);
    }

    noTone(buzzer);
    delay(1000);
}