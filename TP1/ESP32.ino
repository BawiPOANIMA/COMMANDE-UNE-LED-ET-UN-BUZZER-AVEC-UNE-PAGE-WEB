const int buzzer = 23;

void setup() {
  ledcAttach(buzzer, 2000, 8); // attach pin to channel
}

void loop() {
  ledcWriteTone(buzzer, 262); // Do
  delay(300);

  ledcWriteTone(buzzer, 294); // Ré
  delay(300);

  ledcWriteTone(buzzer, 330); // Mi
  delay(300);

  ledcWriteTone(buzzer, 0);   // stop
  delay(1000);
}
