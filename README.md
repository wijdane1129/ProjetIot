# 💧 Système Intelligent de Gestion de l'Eau (Smart Water IoT)

![Badge Statut](https://img.shields.io/badge/Status-Functional-success)
![Badge ESP32](https://img.shields.io/badge/Hardware-ESP32-blue)
![Badge Protocol](https://img.shields.io/badge/Protocol-MQTT-green)
![Badge Interface](https://img.shields.io/badge/Dashboard-Node--RED-red)

## 📖 Description du Projet

Ce projet est une solution **IoT (Internet of Things)** complète destinée à l'agriculture intelligente ou à la domotique ("Smart Home"). Il vise à automatiser la gestion de l'eau (remplissage de réservoir et irrigation) tout en surveillant les conditions environnementales et en assurant la sécurité via des alertes.

Le système repose sur un microcontrôleur **ESP32** simulé sur Wokwi, communiquant via le protocole **MQTT** avec un Dashboard de supervision **Node-RED**.

### 🎯 Objectifs Principaux
1.  **Surveillance en temps réel** : Niveau d'eau du réservoir, humidité du sol, température et humidité de l'air.
2.  **Automatisation** : Activation des pompes selon des seuils critiques (sol sec, réservoir vide).
3.  **Contrôle à distance** : Possibilité de passer en mode manuel pour piloter les actuateurs depuis une interface web.
4.  **Sécurité** : Détection d'incendie (Temp > 65°C) et alerte de débordement.

---

## 🛠️ Architecture Technique

### 1. Matériel (Simulation Wokwi)
* **Microcontrôleur** : ESP32 DevKit V1.
* **Capteurs** :
    * `DHT22` : Température et Humidité.
    * `HC-SR04` : Capteur Ultrason (Mesure du niveau d'eau dans la cuve).
    * `Soil Moisture Sensor` : Capteur d'humidité du sol (Simulé par potentiomètre/chip custom).
* **Actuateurs** :
    * 2x **Relais** : Contrôle des pompes (Pompe Remplissage & Pompe Irrigation).
    * **Buzzer** : Alarme sonore (Incendie ou niveau d'eau critique).
    * **LEDs** : Indicateurs d'état visuels.

### 2. Logiciel & Protocoles
* **Langage** : C++ (Arduino Framework).
* **Protocole de Communication** : MQTT (Message Queuing Telemetry Transport).
* **Broker MQTT** : `broker.mqtt.cool` (Public).
* **Interface Homme-Machine (IHM)** : Node-RED (Dashboard UI).

---

## 🔌 Câblage (Pinout)

Voici la correspondance des broches (Pins) définies dans le code `sketch.ino` :

| Composant | Pin ESP32 | Description |
| :--- | :--- | :--- |
| **DHT22** | GPIO 15 | Capteur Temp/Hum |
| **Soil Moisture** | GPIO 34 | Entrée Analogique (ADC) |
| **HC-SR04 (Trig)**| GPIO 5 | Déclencheur Ultrason |
| **HC-SR04 (Echo)**| GPIO 18 | Réception Ultrason |
| **Pompe 1 (Relais)**| GPIO 2 | Pompe Réservoir |
| **Pompe 2 (Relais)**| GPIO 13 | Pompe Irrigation |
| **Buzzer** | GPIO 4 | Alarme Sonore |

---

## 🚀 Installation et Utilisation

### Prérequis
* Un navigateur web (pour Wokwi).
* **Node-RED** installé localement (`npm install -g node-red`) OU une instance Node-RED en ligne.

### Étape 1 : Simulation Wokwi
1.  Ouvrez le projet sur [Wokwi.com](https://wokwi.com).
2.  Assurez-vous que les fichiers suivants sont présents :
    * `sketch.ino` (Le code principal).
    * `diagram.json` (Le schéma de câblage).
    * `libraries.txt` (Liste des dépendances : `WiFi`, `PubSubClient`, `DHTesp`, `NewPing`).
3.  Lancez la simulation (Bouton vert **Play**).
4.  Vérifiez dans le moniteur série que l'ESP32 se connecte bien au WiFi ("Connected") et au Broker MQTT.

### Étape 2 : Configuration Node-RED
1.  Lancez Node-RED dans votre terminal :
    ```bash
    node-red
    ```
2.  Accédez à l'interface via `http://localhost:1880`.
3.  Importez le flux (Flow) :
    * Menu (en haut à droite) -> **Import**.
    * Collez le code JSON de votre Dashboard Node-RED.
4.  Vérifiez que les nœuds MQTT sont configurés sur le broker `broker.mqtt.cool` (port 1883).
5.  Cliquez sur **Deploy**.
6.  Ouvrez le Dashboard via `http://localhost:1880/ui`.

---

## 📡 Documentation API MQTT

Le système utilise les "Topics" suivants pour communiquer. Vous pouvez utiliser n'importe quel client MQTT (MQTT Explorer, Smartphone) pour interagir.

### Topics de Publication (Sorties de l'ESP32)
* `smartwater/waterlevel` : Niveau de remplissage du réservoir (0-100%).
* `smartwater/soilmoisture` : Humidité du sol (0-100%).
* `smartwater/temperature` : Température ambiante (°C).
* `smartwater/humidity` : Humidité de l'air (%).
* `smartwater/fire` : **ALERTE** en cas d'incendie (Message texte).
* `smartwater/alert` : **ALERTE** niveau d'eau critique.

### Topics de Souscription (Commandes vers l'ESP32)
* `smartwater/mode_auto` :
    * `1` = Mode Automatique (Gestion autonome par seuils).
    * `2` = Mode Manuel (Contrôle utilisateur).
* `smartwater/manual/pump1` : `1` (ON) ou `0` (OFF) - Contrôle Pompe Réservoir.
* `smartwater/manual/pump2` : `1` (ON) ou `0` (OFF) - Contrôle Pompe Irrigation.

---

## ⚙️ Logique de Fonctionnement

### 1. Mode Automatique (`system_mode = 1`)
* **Remplissage** : La Pompe 1 s'active si le niveau d'eau < 20% et s'arrête à > 90%.
* **Irrigation** : La Pompe 2 s'active si l'humidité du sol < 30% et s'arrête à > 70%.

### 2. Mode Manuel (`system_mode = 2`)
* L'automatisme est désactivé. L'utilisateur doit utiliser les commutateurs (Switches) sur le Dashboard Node-RED pour allumer ou éteindre les pompes.

### 3. Sécurité Incendie (Prioritaire)
* Si la **Température > 65°C** :
    * Le Buzzer sonne en continu.
    * Les deux pompes sont coupées immédiatement (sécurité électrique).
    * Une notification est envoyée sur le Dashboard.

---

## 👥 Auteurs

Projet réalisé dans le cadre du module **IoT** à l'**ENSAM Meknès** (Année 2025-2026).

* **Ziyter Fatima-Ezzahrae**
* **En-Najjari Meryem**
* **Lahboub Wijdane**

---

*Pour toute question sur le code ou le déploiement, merci de consulter le rapport technique PDF inclus dans l'archive.*
