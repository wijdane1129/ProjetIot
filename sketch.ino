#include <WiFi.h>
#include <PubSubClient.h>

#include <DHTesp.h>
#include <Wire.h> 
#include <NewPing.h>

// ----------------------------
// WIFI + MQTT CONFIG
// ----------------------------
const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.mqtt.cool";
const int   mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// ----------------------------
// SENSORS + PINS
// ----------------------------
#define DHTPIN  15
#define DHTTYPE DHT11
const int SOIL_MOISTURE_PIN = 34;

#define TRIGGER_PIN  5
#define ECHO_PIN     18
#define MAX_DISTANCE 400 

#define BuzzerPin 4

#define PUMP_PIN 2
#define PUMP2_PIN 13

#define LOW_THRESHOLD  20
#define HIGH_THRESHOLD 90
#define DANGER_THRESHOLD 95

#define SOIL_DRY_THRESHOLD 30
#define SOIL_WET_THRESHOLD 70

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
DHTesp dht;

// ----------------------------
// GLOBAL VARIABLES
// ----------------------------
int system_mode = 1;  // 1 = auto, 2 = manual
int manual_pump1 = 0; // 0=OFF, 1=ON
int manual_pump2 = 0; // 0=OFF, 1=ON

// ----------------------------
// MQTT CALLBACK
// ----------------------------
void mqtt_callback(char* topic, byte* message, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) msg += (char)message[i];

  Serial.print("MQTT: ");
  Serial.print(topic);
  Serial.print(" -> ");
  Serial.println(msg);

  // MODE AUTO / MANUAL
  if (String(topic) == "smartwater/mode_auto") {
    system_mode = msg.toInt();
    Serial.print("Mode changed to: ");
    Serial.println(system_mode == 1 ? "AUTO" : "MANUAL");
  }

  // MANUAL CONTROL PUMP 1
  if (String(topic) == "smartwater/manual/pump1") {
    manual_pump1 = msg.toInt();
  }

  // MANUAL CONTROL PUMP 2
  if (String(topic) == "smartwater/manual/pump2") {
    manual_pump2 = msg.toInt();
  }
}

// ----------------------------
// MQTT RECONNECT
// ----------------------------
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32_SMARTWATER")) {
      Serial.println("Connected.");

      client.subscribe("smartwater/mode_auto");
      client.subscribe("smartwater/manual/pump1");
      client.subscribe("smartwater/manual/pump2");

    } else {
      Serial.print("Failed. State=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

// ----------------------------
// WIFI SETUP
// ----------------------------
void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ----------------------------
// MAIN SETUP
// ----------------------------
void setup() {
  Serial.begin(9600);

  pinMode(PUMP_PIN, OUTPUT);
  pinMode(PUMP2_PIN, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);

  dht.setup(DHTPIN, DHTesp::DHT22);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqtt_callback);
}

// ----------------------------
// MAIN LOOP
// ----------------------------
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  // ===== SENSOR READING =====
  int distance = sonar.ping_cm();
  if (distance == 0) return;

  float hight = 400 - distance;
  int waterquantity = map(distance, 0, 400, 100, 0);
  int soilMoisturePercentage = map(analogRead(SOIL_MOISTURE_PIN), 0, 4095, 0, 100);

  float h = dht.getHumidity();
  float t = dht.getTemperature();

  if (isnan(h) || isnan(t)) return;

  // ===== FIRE DETECTION =====
  if (t > 65) {
    digitalWrite(BuzzerPin, HIGH);

    client.publish("smartwater/fire", "🔥 FIRE WARNING! Temperature above 65C!");
    client.publish("smartwater/temperature", String(t).c_str());

    // stop pumps during fire danger
    digitalWrite(PUMP_PIN, LOW);
    digitalWrite(PUMP2_PIN, LOW);

    delay(1000);
    return; // Stop all processing if fire detected
  }

  // ===== MQTT PUBLISH =====
  client.publish("smartwater/waterlevel", String(waterquantity).c_str());
  client.publish("smartwater/waterheight", String(hight).c_str());
  client.publish("smartwater/soilmoisture", String(soilMoisturePercentage).c_str());
  client.publish("smartwater/humidity", String(h).c_str());
  client.publish("smartwater/temperature", String(t).c_str());

  // ---------------------------------------------------
  // =============== MODE AUTOMATIQUE ==================
  // ---------------------------------------------------
  if (system_mode == 1) {

    // PUMP 1 WATER TANK
    if (waterquantity <= LOW_THRESHOLD) {
      digitalWrite(PUMP_PIN, HIGH);
      client.publish("smartwater/pump1", "ON");
    }
    else if (waterquantity >= HIGH_THRESHOLD) {
      digitalWrite(PUMP_PIN, LOW);
      client.publish("smartwater/pump1", "OFF");
    }

    // Buzzer alert
    if (waterquantity >= DANGER_THRESHOLD) {
      digitalWrite(BuzzerPin, HIGH);
      client.publish("smartwater/alert", "DANGER: WATER TOO HIGH!");
    } else {
      digitalWrite(BuzzerPin, LOW);
    }

    // PUMP 2 SOIL
    if (soilMoisturePercentage <= SOIL_DRY_THRESHOLD) {
      digitalWrite(PUMP2_PIN, HIGH);
      client.publish("smartwater/pump2", "ON");
    }
    else if (soilMoisturePercentage >= SOIL_WET_THRESHOLD) {
      digitalWrite(PUMP2_PIN, LOW);
      client.publish("smartwater/pump2", "OFF");
    }
  }

  // ---------------------------------------------------
  // =============== MODE MANUEL =======================
  // ---------------------------------------------------
  if (system_mode == 2) {

    // Pump 1 manual
    digitalWrite(PUMP_PIN, manual_pump1 ? HIGH : LOW);

    // Pump 2 manual
    digitalWrite(PUMP2_PIN, manual_pump2 ? HIGH : LOW);

    client.publish("smartwater/pump1", manual_pump1 ? "ON" : "OFF");
    client.publish("smartwater/pump2", manual_pump2 ? "ON" : "OFF");
  }

  delay(1000);
}

// ----------------------------
// VOLUME CALCULATOR
// ----------------------------
void mesured_volume(float h, float r) {
  float volume = (3.14 * (r * r) * h);
  Serial.println(volume);
}
