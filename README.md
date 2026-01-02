# 💧 Smart Water Management System (IoT Project)

<div align="center">

![Status](https://img.shields.io/badge/Status-Functional-success?style=for-the-badge)
![ESP32](https://img.shields.io/badge/Hardware-ESP32-blue?style=for-the-badge&logo=espressif)
![MQTT](https://img.shields.io/badge/Protocol-MQTT-green?style=for-the-badge)
![Node-RED](https://img.shields.io/badge/Dashboard-Node--RED-red?style=for-the-badge)
![Wokwi](https://img.shields.io/badge/Simulation-Wokwi-orange?style=for-the-badge)

**An intelligent IoT solution for automated water management in agriculture and smart homes**

[📺 Watch Demo](#-project-videos) • [📖 Documentation](#-project-overview) • [🚀 Quick Start](#-quick-start-guide) • [👥 Team](#-team)

</div>

---

## 🎥 Project Videos

### 🎬 System Demo & Live Functionality

<div align="center">

[![Watch Demo](https://img.youtube.com/vi/jz0VtURfFew/maxresdefault.jpg)](https://youtu.be/jz0VtURfFew)

**▶️ [Watch on YouTube](https://youtu.be/jz0VtURfFew)**

📹 **Local File**: `h1st02tr.mp4` (included in repository)

</div>

**What you'll see in this demo:**
- ⚡ Real-time system operation
- 📊 Live sensor data visualization
- 🎛️ Manual and automatic control modes
- 🚨 Fire detection and alert system
- 📡 MQTT communication in action
- 🖥️ Node-RED dashboard interface

---

### 📚 Complete Project Explanation (For Beginners)

> 🎓 **Educational video explaining the entire IoT concept and project architecture**

**This tutorial covers:**
- 🌐 Introduction to Internet of Things (IoT)
- 🔌 Role of ESP32 microcontroller
- 📡 How sensors and actuators work together
- 🔄 MQTT protocol explained simply
- ⚙️ Automatic vs Manual operation modes
- 🖥️ Node-RED dashboard functionality
- 💡 Real-world applications in agriculture and smart homes

---

## 📖 Project Overview

### 🎯 Mission Statement

This project delivers a complete **IoT (Internet of Things)** solution for **smart agriculture** and **home automation**, enabling automated water management for tank filling and irrigation while monitoring environmental conditions and ensuring safety through intelligent alerts.

The system is built on an **ESP32 microcontroller** (simulated on **Wokwi**) communicating via **MQTT protocol** with a web interface developed in **Node-RED**.

---

## ✨ Key Features

### 📊 Real-Time Monitoring
- 💧 **Water tank level** tracking
- 🌱 **Soil moisture** measurement  
- 🌡️ **Temperature** monitoring
- 💨 **Air humidity** detection

### ⚙️ Intelligent Automation
- 🤖 **Auto mode**: Pumps activate based on sensor thresholds
- 🎯 **Smart algorithms** prevent overflow and waste
- 🔄 **Self-adjusting** irrigation cycles

### 🌐 Remote Control
- 🖥️ **Web dashboard** accessible from anywhere
- ✋ **Manual override** for direct pump control
- 📱 **Responsive interface** for mobile and desktop

### 🚨 Safety & Alerts
- 🔥 **Fire detection** (temperature > 65°C)
- 📢 **Overflow warnings** (water level > 95%)
- ⚠️ **Low water alerts** (level < 20%)
- 🚨 **Buzzer activation** for critical events

---

## 🏗️ System Architecture

```
┌─────────────────┐         ┌──────────────┐         ┌─────────────────┐
│   WOKWI ESP32   │  WiFi   │     MQTT     │  MQTT   │   NODE-RED      │
│   Simulation    │────────▶│    Broker    │◀────────│   Dashboard     │
│                 │         │mqtt.cool:1883│         │  localhost:1880 │
│ • DHT22         │         │              │         │                 │
│ • HC-SR04       │         │  QoS Levels  │         │ • Gauges        │
│ • Soil Sensor   │         │  Topics      │         │ • Charts        │
│ • 2x Relays     │         │  Routing     │         │ • Controls      │
│ • Buzzer        │         │              │         │ • Alerts        │
└─────────────────┘         └──────────────┘         └─────────────────┘
```

---

## 🔧 Hardware Components (Wokwi Simulation)

### 🎛️ Microcontroller
| Component | Model | Purpose |
|-----------|-------|---------|
| MCU | **ESP32 DevKit V1** | Main controller with WiFi |

### 📡 Sensors
| Sensor | Model | Measures | Interface |
|--------|-------|----------|-----------|
| Temperature/Humidity | **DHT22** | 🌡️ Temp & 💨 Humidity | Digital (GPIO 15) |
| Distance | **HC-SR04** | 💧 Water Level | Ultrasonic (GPIO 5/18) |
| Soil Moisture | **Custom Chip** | 🌱 Soil Moisture | Analog (GPIO 34) |

### ⚡ Actuators
| Component | Type | Function | Pin |
|-----------|------|----------|-----|
| Relay 1 | Module | 🚰 Tank Fill Pump | GPIO 2 |
| Relay 2 | Module | 💦 Irrigation Pump | GPIO 13 |
| Buzzer | Passive | 🔔 Audio Alerts | GPIO 4 |
| LEDs | Status | 💡 Visual Indicators | Various |

---

## 📍 Complete Pinout Diagram

```
ESP32 DevKit V1 Pinout
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

         ┌─────────────────────┐
         │      ESP32          │
         │                     │
GPIO 15 ─┤ DHT22 Data          │
GPIO 34 ─┤ Soil Moisture       │
GPIO 5  ─┤ HC-SR04 Trigger     │
GPIO 18 ─┤ HC-SR04 Echo        │
GPIO 2  ─┤ Pump 1 (Tank)       │
GPIO 13 ─┤ Pump 2 (Irrigation) │
GPIO 4  ─┤ Buzzer              │
3.3V    ─┤ Sensor Power        │
GND     ─┤ Common Ground       │
         │                     │
         └─────────────────────┘
```

---

## 💻 Software Stack

| Layer | Technology | Version | Purpose |
|-------|-----------|---------|---------|
| **Firmware** | Arduino C++ | 1.8+ | ESP32 programming |
| **Protocol** | MQTT | 3.1.1 | IoT messaging |
| **Broker** | Mosquitto (Cloud) | - | Message routing |
| **Dashboard** | Node-RED | 3.0+ | Web interface |
| **Simulation** | Wokwi | Latest | Hardware emulation |
| **Libraries** | DHT, NewPing, PubSubClient | - | Sensor & MQTT |

---

## 🚀 Quick Start Guide

### ✅ Prerequisites

```bash
# Required Software
- Web Browser (Chrome/Firefox)
- Node.js (v18+)
- Node-RED (v3.0+)
- Internet connection

# Optional
- Wokwi account (for simulation editing)
- MQTT Explorer (for debugging)
```

---

### 📥 Step 1: Clone Repository

```bash
git clone https://github.com/yourusername/smart-water-iot.git
cd smart-water-iot
```

---

### 🧪 Step 2: Launch Wokwi Simulation

1. **Open the project**: [Wokwi Simulation Link](https://wokwi.com/projects/448337889213816833)

2. **Verify files are present**:
   ```
   ✓ sketch.ino          (ESP32 firmware)
   ✓ diagram.json        (Circuit design)
   ✓ libraries.txt       (Dependencies)
   ✓ soil-moisture-sensor.chip.c
   ✓ soil-moisture-sensor.chip.json
   ```

3. **Click "Start Simulation"** ▶️

4. **Open Serial Monitor** to verify:
   ```
   ✓ WiFi connected
   ✓ MQTT connected
   ✓ Sensors publishing data
   ```

---

### 🖥️ Step 3: Setup Node-RED Dashboard

#### Install Node-RED
```bash
# Install globally
npm install -g --unsafe-perm node-red

# Start Node-RED
node-red
```

#### Configure Dashboard
```bash
# 1. Open browser
http://localhost:1880

# 2. Install dashboard (Menu → Manage Palette)
node-red-dashboard

# 3. Import flow
- Menu (☰) → Import
- Select nodes.json from repository
- Click Deploy

# 4. Access dashboard
http://localhost:1880/ui
```

#### Configure MQTT Broker
```
Broker: broker.mqtt.cool
Port: 1883
Client ID: nodered_smartwater
Clean Session: true
```

---

### ✅ Step 4: Verify Everything Works

**Checklist:**
```
□ Wokwi simulation is running
□ Serial monitor shows "MQTT Connected"
□ Node-RED shows "Connected" status
□ Dashboard displays live sensor values
□ Water level gauge updates every second
□ Temperature shows realistic values
□ Pumps can be controlled manually
□ Mode toggle works (Auto/Manual)
```

---

## 📡 MQTT API Documentation

### 📤 Published Topics (ESP32 → Dashboard)

| Topic | Data Type | Range | Unit | Update Rate |
|-------|-----------|-------|------|-------------|
| `smartwater/waterlevel` | Integer | 0-100 | % | 1 Hz |
| `smartwater/waterheight` | Float | 0-400 | cm | 1 Hz |
| `smartwater/soilmoisture` | Integer | 0-100 | % | 1 Hz |
| `smartwater/temperature` | Float | -40 to 80 | °C | 1 Hz |
| `smartwater/humidity` | Float | 0-100 | % | 1 Hz |
| `smartwater/pump1` | String | ON/OFF | - | On change |
| `smartwater/pump2` | String | ON/OFF | - | On change |
| `smartwater/fire` | String | Alert message | - | On trigger |
| `smartwater/alert` | String | Warning message | - | On trigger |

### 📥 Subscribed Topics (Dashboard → ESP32)

| Topic | Value | Effect |
|-------|-------|--------|
| `smartwater/mode_auto` | `1` | 🤖 Enable Auto Mode |
| `smartwater/mode_auto` | `2` | ✋ Enable Manual Mode |
| `smartwater/manual/pump1` | `0` | 🔴 Turn OFF Pump 1 |
| `smartwater/manual/pump1` | `1` | 🟢 Turn ON Pump 1 |
| `smartwater/manual/pump2` | `0` | 🔴 Turn OFF Pump 2 |
| `smartwater/manual/pump2` | `1` | 🟢 Turn ON Pump 2 |

---

## ⚙️ System Logic & Algorithms

### 🤖 Automatic Mode (mode = 1)

#### Pump 1: Tank Fill Control
```cpp
if (waterLevel <= 20%) {
    pump1 = ON;  // Start filling
}
else if (waterLevel >= 90%) {
    pump1 = OFF; // Stop filling
}
// Hysteresis prevents rapid switching
```

#### Pump 2: Irrigation Control
```cpp
if (soilMoisture <= 30%) {
    pump2 = ON;  // Start irrigation
}
else if (soilMoisture >= 70%) {
    pump2 = OFF; // Stop irrigation
}
```

#### Overflow Protection
```cpp
if (waterLevel >= 95%) {
    buzzer = ON;
    mqtt.publish("alert", "DANGER: Water too high!");
}
```

---

### ✋ Manual Mode (mode = 2)

```cpp
// All automation disabled
// Direct control from Node-RED dashboard

pump1 = manual_pump1_state; // 0 or 1
pump2 = manual_pump2_state; // 0 or 1
```

---

### 🔥 Fire Detection (Priority Override)

```cpp
if (temperature > 65°C) {
    // EMERGENCY MODE
    buzzer = ON;
    pump1 = OFF; // Stop all pumps
    pump2 = OFF;
    mqtt.publish("fire", "🔥 FIRE WARNING!");
    return; // Exit normal operation
}
```

**This takes priority over all other modes!**

---

## 🎛️ Threshold Configuration

| Parameter | Low | Normal | High | Danger |
|-----------|-----|--------|------|--------|
| **Water Level** | < 20% | 20-90% | 90-95% | > 95% |
| **Soil Moisture** | < 30% | 30-70% | 70-90% | > 90% |
| **Temperature** | < 15°C | 15-40°C | 40-65°C | > 65°C |

**Modify these in `sketch.ino`:**
```cpp
#define LOW_THRESHOLD  20
#define HIGH_THRESHOLD 90
#define DANGER_THRESHOLD 95
#define SOIL_DRY_THRESHOLD 30
#define SOIL_WET_THRESHOLD 70
```

---

## 📊 Node-RED Dashboard Features

### 📈 Visualization Components
- **Gauges**: Real-time sensor values
- **Charts**: Historical data trends
- **Status LEDs**: System state indicators
- **Text Displays**: Numeric readings

### 🎮 Control Elements
- **Toggle Switch**: Auto/Manual mode
- **Buttons**: Manual pump control
- **Sliders**: Threshold adjustment (optional)

### 🚨 Alert System
- **Toast Notifications**: Pop-up warnings
- **Audio Alerts**: Browser notifications
- **Color-Coded Status**: Visual feedback

---

## 🔒 Security Considerations

> ⚠️ **Current Setup Uses Public Broker**

For **production deployment**, implement:

```yaml
Security Measures:
  ✓ Use private MQTT broker
  ✓ Enable TLS/SSL encryption
  ✓ Add username/password authentication
  ✓ Implement access control lists (ACL)
  ✓ Use secure WiFi (WPA2/WPA3)
  ✓ Regular firmware updates
```

---

## 🐛 Troubleshooting

### Common Issues

#### ❌ ESP32 Won't Connect to MQTT
```bash
# Check Serial Monitor
- Verify WiFi connection
- Ping broker.mqtt.cool
- Check firewall settings
- Try alternative broker (test.mosquitto.org)
```

#### ❌ Dashboard Shows No Data
```bash
# Verify connection chain
1. Is Wokwi simulation running? ▶️
2. Check MQTT broker status
3. Verify Node-RED is connected
4. Check topic names match exactly
```

#### ❌ Sensors Show "--" or Wrong Values
```bash
# In Wokwi
- Click on sensors
- Adjust sliders to change values
- Check wiring in diagram.json
- Verify pin assignments in code
```

#### ❌ Pumps Don't Respond
```bash
# Checklist
- System must be in Manual mode
- Check MQTT publish is working
- Verify ESP32 receives commands
- Check relay wiring
```

---

## 📁 Project Structure

```
smart-water-iot/
├── 📂 wokwi/
│   ├── sketch.ino                      # ESP32 firmware
│   ├── diagram.json                    # Circuit design
│   ├── libraries.txt                   # Dependencies
│   ├── soil-moisture-sensor.chip.c     # Custom sensor
│   └── soil-moisture-sensor.chip.json  # Sensor config
│
├── 📂 nodered/
│   ├── flows.json                      # Node-RED flow
│   └── settings.js                     # Configuration
│
├── 📂 docs/
│   ├── architecture.md                 # System design
│   ├── api.md                          # MQTT API docs
│   └── deployment.md                   # Production guide
│
├── 📂 videos/
│   └── h1st02tr.mp4                    # Demo video
│
├── README.md                           # This file
├── LICENSE                             # MIT License
└── .gitignore                          # Git ignore rules
```

---

## 🚀 Future Enhancements

### 🔮 Planned Features
- [ ] 📱 Mobile app (React Native)
- [ ] 💾 Database integration (MongoDB)
- [ ] 📊 Advanced analytics & ML predictions
- [ ] ☁️ Cloud deployment (AWS/Azure)
- [ ] 🔔 SMS/Email notifications
- [ ] 📅 Scheduling & automation rules
- [ ] 🌦️ Weather API integration
- [ ] 🤖 AI-powered optimization

---

## 📚 Additional Resources

### 📖 Documentation
- [ESP32 Official Docs](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [MQTT Protocol Specification](https://mqtt.org/mqtt-specification/)
- [Node-RED User Guide](https://nodered.org/docs/user-guide/)
- [Wokwi Documentation](https://docs.wokwi.com/)

### 🎓 Learning Materials
- [IoT Fundamentals](https://www.coursera.org/learn/iot)
- [Arduino Programming](https://www.arduino.cc/en/Tutorial/HomePage)
- [MQTT Essentials](https://www.hivemq.com/mqtt-essentials/)

---

## 👥 Team

<div align="center">

### 🎓 ENSAM Meknès – IoT Project 2025/2026

| Team Member | Role |
|-------------|------|
| **Ziyter Fatima-Ezzahrae** | Hardware & Firmware |
| **En-Najjari Meryem** | Dashboard & UI |
| **Lahboub Wijdane** | Integration & Testing |

**Course**: Internet of Things (IoT)  
**Institution**: École Nationale Supérieure d'Arts et Métiers  
**Location**: Meknès, Morocco 🇲🇦

</div>

---

## 🙏 Acknowledgments

- **ENSAM Meknès** for project facilities
- **Wokwi** for excellent simulation platform
- **Node-RED** community for dashboard tools
- **MQTT.org** for protocol documentation
- All open-source library contributors


<div align="center">

**Made with ❤️ by Meryem En-Najjari - Wijdane Lahboub - Fatima Zahra Ziyter**

</div>
