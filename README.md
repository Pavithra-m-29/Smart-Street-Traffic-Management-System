# 🚦 Smart Street & Traffic Management System

## 📌 Project Description

The Smart Street & Traffic Management System is an IoT-based solution designed to improve traffic management and street lighting efficiency. The system uses ESP8266 NodeMCU along with IR, Rain, and LDR sensors to monitor traffic density, weather conditions, and ambient light levels in real time.

Based on sensor inputs, the system automatically controls traffic signals and street light brightness. Real-time monitoring is provided through both the Blynk IoT platform and a web-based dashboard.

---

## ✨ Features

- Real-Time Vehicle Detection and Counting
- Adaptive Traffic Signal Control
- Automatic Street Light Control
- Rain Detection and Monitoring
- Day and Night Detection
- Weather-Based Street Light Brightness Adjustment
- Blynk IoT Cloud Integration
- Live Web Dashboard Monitoring
- Energy Efficient Smart Lighting
- Real-Time Traffic Status Display

---

## 🛠 Hardware Components

- ESP8266 NodeMCU
- IR Sensor
- Rain Sensor Module
- LDR Sensor Module
- Red LED
- Yellow LED
- Green LED
- White LED (Street Light)
- Breadboard
- Jumper Wires
- USB Cable

---

## 💻 Software Requirements

- Arduino IDE
- ESP8266 Board Package
- Blynk IoT Platform
- HTML
- CSS

---

## ⚙️ Working Principle

### Vehicle Detection

The IR sensor detects passing vehicles and increases the vehicle count.

### Traffic Signal Control

Traffic signals are automatically adjusted based on the number of detected vehicles.

| Vehicle Count | Green Signal Duration |
|--------------|----------------------|
| 1 - 3 | 5 Seconds |
| 4 - 6 | 10 Seconds |
| 7 or More | 15 Seconds |

Traffic Signal Sequence:

RED → GREEN → YELLOW → RED

---

### Smart Street Light Control

The LDR sensor continuously monitors surrounding light intensity.

- During Daytime → Street Light OFF
- During Nighttime → Street Light ON

This helps reduce unnecessary power consumption.

---

### Rain Detection

The Rain Sensor detects rainfall conditions.

When rain is detected:

- Rain Status changes to "Raining"
- Street Light Brightness increases to Maximum
- Road visibility improves during bad weather

---

## ☁️ Blynk IoT Monitoring

The system sends live data to the Blynk Cloud Platform.

### Virtual Pins

| Virtual Pin | Description |
|------------|-------------|
| V0 | Vehicle Count |
| V1 | Rain Status |
| V2 | Day/Night Status |
| V3 | Street Light Brightness |
| V4 | Traffic Signal Status |

---

## 🌐 Web Dashboard Features

The ESP8266 hosts a responsive web dashboard displaying:

- Vehicle Count
- Rain Status
- Light Condition
- Street Light Brightness
- Traffic Signal Status
- Live Updates

The dashboard refreshes automatically every 3 seconds.

---

## 📊 Project Benefits

- Reduces Traffic Congestion
- Improves Road Safety
- Enhances Visibility During Rain
- Saves Electrical Energy
- Enables Remote Monitoring
- Supports Smart City Applications

---

## 🚀 Future Enhancements

- Emergency Vehicle Priority System
- AI-Based Traffic Prediction
- GSM Notification Alerts
- Cloud Database Storage
- Mobile Application Integration
- Multi-Junction Traffic Management

---

## 📸 Output Screenshots

### Hardware Setup
<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/a579879b-f1b6-45f4-b116-87e2b6c182a2" />


### Blynk Dashboard
<img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/25841afb-0167-423f-a756-9652b0c81027" />


### Web Dashboard
<img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/d957d989-76f2-4cb8-9c66-be8f9963f692" />


---

## 🎯 Applications

- Smart Cities
- Intelligent Transportation Systems
- Automated Street Lighting
- Traffic Monitoring Systems
- Urban Infrastructure Management

---

## 👩‍💻 Author

**Pavithra M**

Electronics and Communication Engineering

---

## 📜 License

This project is developed for educational and learning purposes.

---

⭐ If you like this project, don't forget to give this repository a Star.
