# H2Know (A.W.A.R.E. - Automatic Water Analysis & Real-time Evaluation)

> **An innovative Arduino-based water monitoring solution designed to analyze safety in real-time and optimize personal daily hydration.**

---

##  Project Overview

**H2Know** is an end-to-end ecosystem that addresses two critical health and environmental challenges: the lack of immediate, accessible data regarding water potability and the difficulty of maintaining a scientifically calculated daily hydration goal.

The project seamlessly integrates a **physical hardware device** equipped with chemical/physical sensors and a **modern cross-platform mobile application** built using **FlutterFlow**.

### The Core Problem
* **Water Safety:** Traditional water testing is slow and requires laboratory access. Contaminants can appear suddenly, making physical indicators like turbidity crucial for immediate hazard reporting.
* **Dehydration:** Static water intake goals (e.g., "2 liters a day") fail to account for dynamic physiological and environmental variables such as age, weight, physical activity, and ambient temperature.

### The H2Know Solution
1. **The Arduino Device:** Analyzes water in real-time, checking pH, Total Dissolved Solids (TDS), Turbidity (NTU), and Temperature.
2. **The Cloud:** Real-time synchronization of sensor data via Firebase Realtime Database.
3. **The Mobile App:** Displays live water metrics, issues instant safety verdicts (Potable vs. Non-Potable), maps water quality data, and features an advanced daily hydration calculator based on dynamic user metrics.

---
##  Key Features
*  **Real-Time Monitoring:** Instant analysis of critical water parameters: pH, turbidity, temperature, and TDS.
* **Interactive Map:** Visual tracking of potable, moderate, or hazardous/contaminated zones, hosted on Netlify.
*  **Virtual Assistant (Aqualoo AI):** Integrated smart chatbot designed to answer water quality and environmental questions.
*  **Voice Commands:** Speech-to-Text functionality for natural user interaction.
*  **SOS Emergency Button:** Rapid hazard reporting system (illegal pollution, floods) with support for on-field photo uploads.
*  **Hydration Calculator & Tracking:** Daily, weekly, and monthly water consumption monitoring.

---

##  System Architecture

The H2Know ecosystem bridges hardware components and cloud software solutions seamlessly:

1. **Hardware (Portable Device):**
   * **Arduino R4 WiFi** development board.
   * Integrated sensors: pH Sensor, Turbidity Sensor, TDS Sensor, and Temperature Sensor.
   * Custom-designed enclosure, modeled in *Autodesk Fusion 360* and 3D printed.
2. **Cloud Backend:**
   * **Firebase Realtime Database:** Instant and secure storage of the data streams received from the device.
3. **Mobile & Web Application:**
   * Built using the **FlutterFlow** platform, synchronized via API calls with Firebase.
   * Advanced modules (the Map and Chatbot) built with **Lovable AI** and deployed on **Netlify**.

---

##  Repository Structure
To maintain clean and organized code, files are structured as follows:

├── hardware/               # Source code (.ino) for the Arduino microcontroller
├── web-assets/             # Web views from Lovable AI (hosted on Netlify) &  FlutterFlow custom functions
├── design/                 # CAD files (.stl / .f3d) for the 3D printed enclosure
└── README.md               # Main project overview and documentation

---

##  Mobile Application (FlutterFlow)

The complete mobile application project, built using FlutterFlow low-code, can be viewed and cloned from the following link:
🔗 [Open H2Know on FlutterFlow](https://h2-know-wyot4s.flutterflow.app)


---

##  Installation Guide (Hardware)

To run the source code on your local device, please follow these steps:

1. Clone this repository.
2. Open the `hardware.ino` file inside the **Arduino IDE**.
3. Install the `Firebase_Arduino_Client` library.
4. Input your custom network credentials into the code:
   ```cpp
   #define WIFI_SSID "Your_WiFi_Name"
   #define WIFI_PASSWORD "Your_WiFi_Password"
   #define FIREBASE_HOST "h2know-cce20-default-rtdb.europe-west1.firebasedatabase.app"
