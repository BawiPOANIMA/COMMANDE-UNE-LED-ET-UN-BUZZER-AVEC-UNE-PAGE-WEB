const int led = 23; // broche de la LED

void setup() {
pinMode(led, OUTPUT);
}

void loop() {

digitalWrite(led, HIGH); // allumer la LED
delay(2000); // attendre 2 secondes

digitalWrite(led, LOW); // éteindre la LED
delay(2000); // attendre 2 secondes
}
