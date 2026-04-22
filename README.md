# 🚨 ESP32-CAM Smart Security System 📷

## 📌 Overview

This project is a **smart security system** built using the ESP32-CAM and a PIR motion sensor.
It detects motion, captures images, streams live video, and sends alerts via the Blynk app.

---

## 🎯 Features

* 🚨 Motion detection using PIR sensor
* 📸 Automatic image capture on detection
* 📡 Live video streaming via browser
* 📲 Real-time alerts using Blynk
* ⚡ Lightweight and low-cost security solution

---

## 🖼️ Project Preview

### 📷 ESP32-CAM Module

![ESP32-CAM](https://upload.wikimedia.org/wikipedia/commons/3/38/ESP32-CAM_Module.jpg)

### 🔌 Circuit Setup

![Circuit Diagram](https://upload.wikimedia.org/wikipedia/commons/8/87/Arduino_PIR_Sensor_Diagram.png)

### 📱 Blynk Notification Example

![Blynk App](https://upload.wikimedia.org/wikipedia/commons/6/6d/Smartphone_icon.png)

---

## 🛠️ Components Used

* ESP32-CAM (AI Thinker)
* PIR Motion Sensor
* Jumper Wires
* Power Supply (5V)
* WiFi Network
* Blynk IoT Platform

---

## ⚙️ How It Works

1. PIR sensor detects motion
2. ESP32-CAM triggers image capture
3. Image is available via web server
4. Notification sent to Blynk app
5. User can view live stream anytime

---

## 🌐 Live Access

After uploading code, open in browser:

### 🎥 Live Stream

```
http://YOUR-IP:81/stream
```

### 📸 Capture Image

```
http://YOUR-IP/capture
```

---

## 🚀 Installation & Setup

### 1️⃣ Upload Code

* Open Arduino IDE
* Select **ESP32-CAM board**
* Upload the code

### 2️⃣ Configure WiFi & Blynk

Replace:

```
YOUR_WIFI
YOUR_PASSWORD
YOUR_BLYNK_TOKEN
```

### 3️⃣ Run the System

* Open Serial Monitor
* Copy IP address
* Paste into browser

---

## ⚠️ Important Notes

* Do NOT use GPIO 3 for PIR (causes instability)
* Use GPIO 13 or 12 instead
* Ensure proper power supply (5V recommended)

---

## 🔐 Security Tip

Never upload:

* WiFi password
* Blynk Auth Token

Use placeholders before uploading to GitHub.

---

## 📈 Future Improvements

* 📩 Send images via Telegram
* ☁️ Cloud storage integration
* 🔊 Alarm system with buzzer
* 🧠 AI-based face detection

---

## 👨‍💻 Author

**Your Name**

---

## ⭐ Support

If you like this project:

* ⭐ Star this repository
* 🍴 Fork it
* 📢 Share with others

---
