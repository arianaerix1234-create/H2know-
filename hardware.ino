/**
 * PROJECT: H2Know - Smart Water Analysis
 * BOARD: Arduino Uno R4 WiFi
 * COMPETITION: InfoEducatie 2026
 * * FINAL PRODUCTION CODE (MODIFIED FOR 0-5 NTU TURBIDITY)
 */

#define FIREBASE_DISABLE_SSL_CACHE
#define FB_ENABLE_EXTERNAL_SSL_CLIENT
#define FIREBASE_USE_PSRAM

#include <Arduino.h>
#include <WiFiS3.h>
#include <Firebase_ESP_Client.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// --- 1. CREDENTIALS ---
#define WIFI_SSID "(enter wifi_ssid)"
#define WIFI_PASSWORD "(enter wifi_password) "
#define API_KEY "(enter api_key)"
#define DATABASE_URL "(enter database_url)"

// --- 2. HARDWARE PINS ---
const int phPin = A0;
const int tdsPin = A1;
const int turbPin = A2;
const int tempPin = 2;   
const int buttonPin = 3; 

// --- 3. OBJECTS ---
OneWire oneWire(tempPin);
DallasTemperature sensors(&oneWire);
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// --- 4. CALIBRATION CONSTANTS ---
const float PH_CALIBRATION_V = 3.60; // Voltage for pH 7.0

// Praguri rapide pentru Turbiditate (0 - 5 NTU)
const float VOLTAJ_CURAT = 4.2;   // Voltajul în apă complet curată -> Va indica 0 NTU
const float VOLTAJ_MURDAR = 2.5;  // Voltajul în apă foarte tulbure -> Va indica 5 NTU

void setup() {
  Serial.begin(11520); // Setat la valoarea cerută de tine
  sensors.begin();
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\n[SYSTEM] WiFi Connected Successfully.");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.signer.test_mode = true; 
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
  Serial.println("[SYSTEM] H2Know Online & Ready.");
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    delay(50); 
    
    // Safety check: sensor immersion (Folosește noul prag de apă curată)
    float vCheck = (analogRead(turbPin) * 5.0) / 1023.0;
    
    if (vCheck > 4.5) { // Ajustat ușor ca să nu dea eroare dacă senzorul citește valori mari în apă curată
      Serial.println("\n[!] SENSOR ERROR: Please submerge sensors in water.");
    } 
    else {
      Serial.println("\n[H2Know] ANALYSING SAMPLES...");

      // A. TEMPERATURE
      sensors.requestTemperatures();
      float tempC = sensors.getTempCByIndex(0);
      if (tempC < -10) tempC = 25.0; 

      // B. PH (High stability sampling)
      long phSum = 0;
      for (int i = 0; i < 300; i++) { phSum += analogRead(phPin); delay(1); }
      float vPH = (phSum / 300.0) * (5.0 / 1023.0);
      float phFinal = 7.0 - ((vPH - PH_CALIBRATION_V) / 0.18); 
      phFinal = constrain(phFinal, 0, 14);

      // C. TDS (Temp Compensated)
      float vTDS = (analogRead(tdsPin) * 5.0) / 1024.0;
      float tempCoeff = 1.0 + 0.02 * (tempC - 25.0);
      float vTC = vTDS / tempCoeff;
      float tdsFinal = (133.42 * pow(vTC, 3) - 255.86 * pow(vTC, 2) + 857.39 * vTC) * 0.25;
      if (tdsFinal < 0) tdsFinal = 0;

      // D. TURBIDITY (Modificată pentru valori stabile de 0-5 NTU)
      long turbSum = 0;
      for (int i = 0; i < 300; i++) { turbSum += analogRead(turbPin); delay(1); }
      float vTurb = (turbSum / 300.0) * (5.0 / 1023.0);
      
      float ntuFinal = 0.0;
      if (vTurb >= VOLTAJ_CURAT) {
        ntuFinal = 0.0; 
      } else if (vTurb <= VOLTAJ_MURDAR) {
        ntuFinal = 5.0;
      } else {
        // Regula de trei simplă: scalează voltajul invers proporțional între 0.0 și 5.0 NTU
        ntuFinal = (VOLTAJ_CURAT - vTurb) * (5.0 / (VOLTAJ_CURAT - VOLTAJ_MURDAR));
      }

      // E. VERDICT (International Standards)
      String verdict = "POTABLE";
      String reason = "Water is safe for consumption.";
      
      if (phFinal < 6.5 || phFinal > 8.5) {
        verdict = "NOT POTABLE";
        reason = "Abnormal pH levels detected.";
      } else if (tdsFinal > 500) {
        verdict = "NOT POTABLE";
        reason = "High concentration of dissolved solids.";
      } else if (ntuFinal > 5) {
        verdict = "NOT POTABLE";
        reason = "High turbidity (water is cloudy).";
      }

      // F. SERIAL OUTPUT (English)
      Serial.println("---------- WATER REPORT ----------");
      Serial.print("Temperature: "); Serial.print(tempC, 1); Serial.println(" C");
      Serial.print("pH Level:    "); Serial.println(phFinal, 2);
      Serial.print("TDS:         "); Serial.print(tdsFinal, 0); Serial.println(" PPM");
      Serial.print("Turbidity:   "); Serial.print(ntuFinal, 1); Serial.println(" NTU"); // Modificat să afișeze cu o zecimală (ex. 1.5 NTU)
      Serial.println("Verdict:     " + verdict);
      Serial.print("Reason:      "); Serial.println(reason);
      Serial.println("----------------------------------");

     // G. CLOUD SYNC WITH UNITS
      FirebaseJson json;
      json.set("ph", String(phFinal, 2));                      
      json.set("tds", String(tdsFinal, 0) + " PPM");           
      json.set("turbidity", String(ntuFinal, 1) + " NTU");     // Trimite valoarea corectată (0.0 - 5.0) către Firebase
      json.set("temperature", String(tempC, 1) + " °C");       
      json.set("verdict", verdict);
      json.set("reason", reason);

      if (Firebase.RTDB.setJSON(&fbdo, "/dispozitiv_apa/date", &json)) {
        Serial.println(">>> CLOUD SYNC: SUCCESS");
      } else {
        Serial.println(">>> CLOUD SYNC: FAILED");
      }
    }
    while (digitalRead(buttonPin) == LOW) { delay(10); }
  }
}
