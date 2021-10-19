#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <HTTPClient.h>

// Variables
#define RING_PIN 15
#define NUMPIXELS 12
#define MOTION_PIN 6

String response;

// Web server running on port 80
WebServer server(80);

// JSON data buffer
StaticJsonDocument<250> jsonDocument;
char buffer[250];

//LED Ring Init
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RING_PIN, NEO_GRB + NEO_KHZ800);

const char *SSID = "Midian";
const char *PWD = "0829688988#";

void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PWD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    // we can even make the ESP32 to sleep
  }

  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}

void setup_routing() {
  server.on("/motion", motionOn);
  server.on("/ringoff", ringOff); 
  // start server
  server.begin();
}

void add_json_object(char *tag, char *value, char *unit) {
  JsonObject obj = jsonDocument.createNestedObject();
  obj["type"] = tag;
  obj["value"] = value;
  obj["unit"] = unit;
}

void create_json(char *tag, int value, char *unit) {
  jsonDocument.clear();
  jsonDocument["type"] = tag;
  jsonDocument["value"] = value;
  jsonDocument["unit"] = unit;
  serializeJson(jsonDocument, buffer);
}

void motionOn() {
  Serial.println("Motion Function Called");
  for(int i=0;i<NUMPIXELS;i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 255, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    //    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  create_json("Fan Status", 1, "Running");
  server.send(200, "application/json", buffer);
}

void ringOff() {
  Serial.println("Turn off ring");
  for(int i=0;i<NUMPIXELS;i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    //    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  create_json("Fan Status", 1, "Running");
  server.send(200, "application/json", buffer);
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  setup_routing();
  pixels.begin();
  pinMode(RING_PIN, INPUT);
}

void loop() 
{
  server.handleClient();
  HTTPClient http;
  //The API URL
  String serverName = "http://bernard:Taniam072@192.168.1.106:1880/endpoint/test";
  bool isDetected = digitalRead(MOTION_PIN);
  delay(50);
  const char* motion;
  motion = "off";
  if (isDetected) {
    Serial.print("Motion Detected");
    motion = "on";
  }

  //Start the request
  http.begin(serverName + "?temperature=" + motion);
  //Use HTTP GET request
  delay(5000);
  http.GET();
  //Response from server
  response = http.getString();
}
