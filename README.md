# Commande-une-LED-et-un-buzzer-avec-le-site
## Étape 1 : Ajouter les boutons dans la page data.php
- il faut rajouter dans la partie body un bouton **"Allumer"**
  Copiez le code dans la partie body

```html
<body>

    <PARTIE MESURE A LAISSER>

    <h1>Commande ESP32</h1>

    <button onclick="fetch('http://IP_ESP32/son')">
        🔆 Allumer la LED
    </button>

</body>
```
## Étape 2 : Ajouter un actionneur sur l’esp32
- Cette étape servira a tester le buzzer avec la LED
### Matériels à utiliser :
-	ESP32.
-	Grove buzzer
-	Une Resistance (à définir plus tard)
-	LED
-	Breadboard 

### 1 Test buzzer
- broche utiliser: VCC - 3.3V/ GND - GND/ SIG - GPIO26
    Copiez ce code dans votre Arduino :
```cpp
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
```
### 2 Test LED
- Brancher la LED avec l’ESP32 de la façon suivante :

![Resistance](images/Resistance.PNG)

Ensuite implémenter le code suivant sur l'ESP32:
```cpp
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
```
###	Étape 3 : Actionner le buzzer et la LED en fonction du bouton de la page web
```cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>

// ===== WIFI =====
const char* ssid = "Nom du Réseau";//parti a modifie
const char* password = "Mot de passe réseau";//parti a modifie

// serveur PHP (envoi valeur)
const char* serverName = "http://Adresse IP UBUNTU/btsciel/data.php"; //parti a modifie

// ===== SERVEUR WEB LOCAL =====
WebServer server(80);

// ===== PIN =====
int ledPin = 23;
int buzzerPin = 26;

// ===== TEMPS ENVOI =====
unsigned long lastSend = 0;
const unsigned long interval = 5000; // 5s

// =====================
// BOUTON LED
// =====================
void handleLED() {
  digitalWrite(ledPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);

  server.send(200, "text/plain", "LED OK");
}

// =====================
// BOUTON SON
// =====================
void handleSON() {
  ledcWriteTone(buzzerPin, 1000);
  delay(300);

  ledcWriteTone(buzzerPin, 500);
  delay(300);

  ledcWriteTone(buzzerPin, 0);

  server.send(200, "text/plain", "BUZZER OK");
}

// =====================
// ENVOI VALEUR ALEATOIRE
// =====================
void sendRandomValue() {
  if (WiFi.status() == WL_CONNECTED) {

    int valeur = random(0, 100);

    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String data = "valeur=" + String(valeur);
    int code = http.POST(data);

    Serial.print("Valeur envoyée: ");
    Serial.println(valeur);

    if (code > 0) {
      Serial.print("HTTP OK: ");
      Serial.println(code);
    } else {
      Serial.print("Erreur HTTP: ");
      Serial.println(code);
    }

    http.end();
  }
}

// =====================
// SETUP
// =====================
void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  // buzzer (comme ton code fonctionnel)
  ledcAttach(buzzerPin, 2000, 8);

  WiFi.begin(ssid, password);

  Serial.print("Connexion WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnecté !");
  Serial.println(WiFi.localIP());

  randomSeed(analogRead(0));

  // routes serveur web
  server.on("/led", handleLED);
  server.on("/son", handleSON);

  server.begin();
}

// =====================
// LOOP
// =====================
void loop() {
  server.handleClient();

  // envoi toutes les 5 secondes sans bloquer le serveur
  if (millis() - lastSend >= interval) {
    lastSend = millis();
    sendRandomValue();
  }
}
```
