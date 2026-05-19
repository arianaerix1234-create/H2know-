# 💧 H2Know (A.W.A.R.E. - Automatic Water Analysis & Real-time Evaluation)

> Un ecosistem tehnologic inovator ce oferă acces în timp real la date despre siguranța apei, integrând un dispozitiv hardware propriu și o platformă digitală avansată.

---

## 🚀 Caracteristici principale (Features)
* 📊 **Monitorizare în timp real:** Analiza instantanee a parametrilor critici ai apei: pH, turbiditate, temperatură și TDS.
* 🗺️ **Hartă Interactivă:** Localizarea vizuală a zonelor cu apă potabilă, moderată sau periculoasă/contaminată, găzduită pe Netlify.
* 🤖 **Asistent Virtual (Aqualoo AI):** Chatbot inteligent integrat pentru a răspunde la întrebări legate de calitatea apei și mediu.
* 🗣️ **Comenzi Vocale:** Funcționalitate de tip Speech-to-Text pentru interacțiune naturală.
* 🚨 **Buton de Urgență SOS:** Sistem rapid de raportare a pericolelor (poluare ilegală, inundații) cu suport pentru fotografii de pe teren.
* 📈 **Calculator de Hidratare & Tracking:** Monitorizarea consumului zilnic, săptămânal și lunar de apă.

---

## 🛠️ Arhitectura Sistemului (Architecture)

Ecosistemul H2Know conectează strâns componentele hardware și soluțiile software din cloud:

1. **Hardware (Dispozitiv Portabil):**
   * Placă de dezvoltare **Arduino R4 WiFi**
   * Senzori integrați: Senzor pH, Senzor Turbiditate, Senzor TDS, Senzor Temperatură.
   * Carcasă personalizată, proiectată în *Autodesk Fusion 360* și printată 3D.
2. **Cloud Backend:**
   * **Firebase Realtime Database:** Stocarea instantanee și securizată a fluxului de date primite de la dispozitiv.
3. **Aplicația Mobilă & Web:**
   * Dezvoltată în platforma **Thunkable**, sincronizată prin chei API cu Firebase.
   * Module avansate (Harta și Chatbotul) construite cu **Lovable AI** și deployate prin **Netlify**.

---

## 📦 Structura Repository-ului (Repository Structure)

Pentru a menține codul curat, organizați folderele astfel:

├── hardware/               # Codul sursă (.ino) pentru microcontrolerul Arduino
├── web-assets/             # Codul sursă generat de Lovable AI (pentru Hartă și Chatbot)
├── design/                 # Fișierele CAD (.stl / .f3d) pentru carcasa printată 3D
└── README.md               # Prezentarea generală a proiectului
