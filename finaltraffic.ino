

#define BLYNK_TEMPLATE_ID "TMPL3gFNUsaUd"
#define BLYNK_TEMPLATE_NAME "Smart Traffic"
#define BLYNK_AUTH_TOKEN "uwZ7OsO8_iclo2tsvsWmoixBqrNTRGb3"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WebServer.h>

char ssid[] = "pavi";
char pass[] = "veeralak";

// ===== Pin Definitions =====
#define IR_PIN      D1
#define RAIN_PIN    D3
#define LDR_PIN     D4

#define RED_LED     D5
#define YELLOW_LED  D6
#define GREEN_LED   D7
#define STREET_LED  D8

// ===== Variables =====
int vehicleCount = 0;
bool objectDetected = false;
int streetBrightness = 0;
String rainStatus = "Dry";
String lightStatus = "Day";
String trafficStatus = "RED";

// ---- Debounce variables for IR sensor ----
unsigned long lastDetectTime = 0;
const unsigned long debounceDelay = 1000; // 1 second gap between counts

ESP8266WebServer server(80);
BlynkTimer timer;

// ===== Traffic Light Control =====
void setTrafficLight(String color) {
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  if (color == "RED")    { digitalWrite(RED_LED, HIGH);    trafficStatus = "RED"; }
  if (color == "YELLOW") { digitalWrite(YELLOW_LED, HIGH); trafficStatus = "YELLOW"; }
  if (color == "GREEN")  { digitalWrite(GREEN_LED, HIGH);  trafficStatus = "GREEN"; }
}

// ===== Main Sensor Logic =====
void sensorLogic() {
  // ---- IR Vehicle Count (with Debounce) ----
  int irValue = digitalRead(IR_PIN);

  if (irValue == LOW && !objectDetected && (millis() - lastDetectTime > debounceDelay)) {
    vehicleCount++;
    objectDetected = true;
    lastDetectTime = millis();
    Serial.print("Vehicle Detected! Count: ");
    Serial.println(vehicleCount);
  }
  if (irValue == HIGH) {
    objectDetected = false;
  }

  // ---- Rain Sensor ----
  int rainVal = digitalRead(RAIN_PIN);
  rainStatus = (rainVal == LOW) ? "Raining" : "Dry";

  // ---- LDR Sensor (Digital D0) ----
  int ldrVal = digitalRead(LDR_PIN);
  if (ldrVal == HIGH) {
    lightStatus = "Day";
    streetBrightness = 0;
  } else {
    lightStatus = "Night";
    streetBrightness = 255;
  }

  // Rain override - full bright
  if (rainVal == LOW) streetBrightness = 255;
  analogWrite(STREET_LED, streetBrightness);

  // ---- Traffic Light Logic ----
  if (vehicleCount >= 1 && vehicleCount <= 3) {
    setTrafficLight("GREEN"); delay(5000);
    setTrafficLight("YELLOW"); delay(2000);
    setTrafficLight("RED");
  } else if (vehicleCount >= 4 && vehicleCount <= 6) {
    setTrafficLight("GREEN"); delay(10000);
    setTrafficLight("YELLOW"); delay(2000);
    setTrafficLight("RED");
  } else if (vehicleCount >= 7) {
    setTrafficLight("GREEN"); delay(15000);
    setTrafficLight("YELLOW"); delay(2000);
    setTrafficLight("RED");
    vehicleCount = 0;
  } else {
    setTrafficLight("RED");
  }

  // ---- Blynk Update ----
  Blynk.virtualWrite(V0, vehicleCount);
  Blynk.virtualWrite(V1, rainStatus);
  Blynk.virtualWrite(V2, lightStatus);
  Blynk.virtualWrite(V3, streetBrightness);
  Blynk.virtualWrite(V4, trafficStatus);
}

// ===== Colorful Web Page =====
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='3'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Smart Traffic System</title>";
  html += "<style>";
  html += "*{margin:0;padding:0;box-sizing:border-box;font-family:Arial,sans-serif;}";
  html += "body{background:linear-gradient(135deg,#0f2027,#203a43,#2c5364);min-height:100vh;padding:20px;}";
  html += ".header{background:linear-gradient(135deg,#1a2a3a,#2c5364);border-radius:15px;padding:20px;text-align:center;margin-bottom:20px;box-shadow:0 4px 15px rgba(0,0,0,0.3);}";
  html += ".header h1{color:#00d4ff;font-size:24px;margin-bottom:5px;}";
  html += ".header p{color:#7fdbff;font-size:12px;}";
  html += ".badge{display:inline-block;background:#00ff8820;border:1px solid #00ff88;color:#00ff88;font-size:11px;padding:4px 14px;border-radius:20px;margin-top:8px;}";
  html += ".grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(150px,1fr));gap:15px;margin-bottom:20px;}";
  html += ".card{border-radius:15px;padding:20px;text-align:center;box-shadow:0 4px 15px rgba(0,0,0,0.3);}";
  html += ".card .icon{font-size:32px;margin-bottom:8px;}";
  html += ".card .val{font-size:26px;font-weight:bold;}";
  html += ".card .lbl{font-size:11px;margin-top:5px;text-transform:uppercase;letter-spacing:1px;opacity:0.8;}";
  html += ".blue{background:linear-gradient(135deg,#0a1628,#16325c);border:1px solid #1a4a8a;}";
  html += ".blue .val{color:#4da6ff;}.blue .lbl{color:#4da6ff;}";
  html += ".green{background:linear-gradient(135deg,#0a1a0f,#0f3a1f);border:1px solid #1a5a2a;}";
  html += ".green .val{color:#00e676;}.green .lbl{color:#00e676;}";
  html += ".amber{background:linear-gradient(135deg,#1a1200,#3a2a00);border:1px solid #5a4a00;}";
  html += ".amber .val{color:#ffcc00;}.amber .lbl{color:#ffcc00;}";
  html += ".cyan{background:linear-gradient(135deg,#001a1a,#003a3a);border:1px solid #005a5a;}";
  html += ".cyan .val{color:#00d4ff;}.cyan .lbl{color:#00d4ff;}";
  html += ".panel{background:linear-gradient(135deg,#16213e,#1a2a4a);border-radius:15px;padding:20px;margin-bottom:15px;box-shadow:0 4px 15px rgba(0,0,0,0.3);}";
  html += ".panel-title{color:#7fdbff;font-size:13px;text-transform:uppercase;letter-spacing:1px;margin-bottom:15px;}";
  html += ".lights{display:flex;justify-content:center;gap:15px;margin-bottom:15px;}";
  html += ".light{width:45px;height:45px;border-radius:50%;border:3px solid #333;opacity:0.25;}";
  html += ".light.on.r{background:#ff4444;border-color:#ff4444;opacity:1;box-shadow:0 0 20px #ff4444;}";
  html += ".light.on.y{background:#ffcc00;border-color:#ffcc00;opacity:1;box-shadow:0 0 20px #ffcc00;}";
  html += ".light.on.g{background:#00e676;border-color:#00e676;opacity:1;box-shadow:0 0 20px #00e676;}";
  html += ".status-text{text-align:center;font-size:16px;font-weight:bold;}";
  html += ".bright-bar{height:16px;border-radius:8px;background:linear-gradient(90deg,#1a1a00,#ffcc00);position:relative;margin:10px 0;}";
  html += ".bright-fill{position:absolute;top:-3px;width:20px;height:22px;background:white;border-radius:50%;border:3px solid #ffcc00;}";
  html += ".footer{text-align:center;color:#7fdbff80;font-size:11px;margin-top:10px;}";
  html += "</style></head><body>";

  html += "<div class='header'><h1>Smart Street & Traffic System</h1>";
  html += "<p>ESP8266 IoT Dashboard</p><div class='badge'>LIVE</div></div>";

  html += "<div class='grid'>";
  html += "<div class='card blue'><div class='icon'>&#128663;</div><div class='val'>" + String(vehicleCount) + "</div><div class='lbl'>Vehicle Count</div></div>";
  String rCls = (rainStatus == "Raining") ? "blue" : "green";
  html += "<div class='card " + rCls + "'><div class='icon'>&#127783;</div><div class='val'>" + rainStatus + "</div><div class='lbl'>Rain Status</div></div>";
  html += "<div class='card amber'><div class='icon'>&#9728;</div><div class='val'>" + lightStatus + "</div><div class='lbl'>Light Condition</div></div>";
  html += "<div class='card cyan'><div class='icon'>&#128161;</div><div class='val'>" + String(streetBrightness * 100 / 255) + "%</div><div class='lbl'>Street Light</div></div>";
  html += "</div>";

  html += "<div class='panel'><div class='panel-title'>Traffic Light Status</div>";
  html += "<div class='lights'>";
  html += "<div class='light " + String(trafficStatus=="RED"?"on r":"") + "'></div>";
  html += "<div class='light " + String(trafficStatus=="YELLOW"?"on y":"") + "'></div>";
  html += "<div class='light " + String(trafficStatus=="GREEN"?"on g":"") + "'></div>";
  html += "</div>";
  String sColor = (trafficStatus=="RED") ? "#ff4444" : (trafficStatus=="GREEN") ? "#00e676" : "#ffcc00";
  html += "<div class='status-text' style='color:" + sColor + "'>" + trafficStatus + "</div></div>";

  html += "<div class='panel'><div class='panel-title'>Street Light Brightness</div>";
  html += "<div class='bright-bar'><div class='bright-fill' style='left:" + String(streetBrightness * 100 / 255) + "%;'></div></div>";
  html += "<div style='display:flex;justify-content:space-between;color:#7fdbff;font-size:11px;'><span>OFF</span><span>FULL BRIGHT</span></div></div>";

  html += "<div class='footer'>Auto refresh every 3 seconds | Smart Street & Traffic System</div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// ===== Setup =====
void setup() {
  Serial.begin(115200);

  pinMode(IR_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(STREET_LED, OUTPUT);

  setTrafficLight("RED");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  server.on("/", handleRoot);
  server.begin();

  timer.setInterval(2000L, sensorLogic);

  Serial.println("System Started!");
  Serial.print("Web IP: ");
  Serial.println(WiFi.localIP());
}

// ===== Loop =====
void loop() {
  Blynk.run();
  timer.run();
  server.handleClient();
}