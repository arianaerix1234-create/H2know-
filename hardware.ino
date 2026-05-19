#include <Arduino.h>
#include <WiFiS3.h>
#include <Firebase_ESP_Client.h>

// 1. Date rețea
#define WIFI_SSID "Diana mau"
#define WIFI_PASSWORD "maumaumau"

// 2. Date Firebase (fără https:// și fără / la final)
#define API_KEY "AIzaSyBf-lu6lDokU9xh04cNQb5sewJoLHOf6zY"
#define DATABASE_URL "h2know-cce20-default-rtdb.europe-west1.firebasedatabase.app"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectare la WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectat!");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // MODUL TEST: Ignoră erorile de autentificare și tokens
  config.signer.test_mode = true; 

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
  Serial.println("Sistem pregătit pentru test!");
}

void loop() {
  // Citim pinul gol A0
  int testValue = analogRead(A0);
  
  Serial.print("Trimit valoare test către Firebase: ");
  Serial.println(testValue);

  // Trimitem valoarea în Firebase sub eticheta "test_conexiune"
  if (Firebase.RTDB.setInt(&fbdo, "/test_conexiune", testValue)) {
    Serial.println("Succes! Verifică consola Firebase.");
  } else {
    Serial.print("Eroare la trimitere: ");
    Serial.println(fbdo.errorReason());
  }

  delay(5000); // Trimite la fiecare 5 secunde
}
