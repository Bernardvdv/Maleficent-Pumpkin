#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

// Variables
#define RING_PIN 15
#define STRIP_PIN 2
#define NUMPIXELS 24
#define NUMPIXELSSTRIP 8

int wait_in_between_led = 20;

// Web server running on port 80
WebServer server(80);

// JSON data buffer
StaticJsonDocument<250> jsonDocument;
char buffer[250];

//LED Ring Init
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RING_PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel pixels_strip = Adafruit_NeoPixel(NUMPIXELSSTRIP, STRIP_PIN, NEO_GRB + NEO_KHZ800);

const char *SSID = "";
const char *PWD = "";

void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PWD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}

void setup_routing() {
  server.on("/ringon", motionOn);
  server.on("/ringoff", ringOff);
  server.on("/strip_on_orange", stripOnOrange);
  server.on("/strip_on_purple", stripOnPurple);
  server.on("/strip_on_green", stripOnGreen);
  
  
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
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Red
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(wait_in_between_led);
  }
  delay(5000);
  for(int i=0;i<NUMPIXELS;i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,165,0)); // Orange.
    pixels.show();
    delay(wait_in_between_led);
  }
  delay(5000);
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0,255,0)); // Green
    pixels.show();
    delay(wait_in_between_led);
  }
  delay(5000);
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // green.
    pixels.show();
    delay(wait_in_between_led);
  }

  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Red.
    pixels.show();
    delay(wait_in_between_led);
  }
  delay(10000);;
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // off 
    pixels.show();
    delay(wait_in_between_led);
  }

  create_json("Ring Status", 1, "Running");
  server.send(200, "application/json", buffer);
}

void ringOff() {
  Serial.println("Turn off ring");
  for(int i=0;i<NUMPIXELS;i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
  }
  create_json("Ring Status", 0, "Stopped");
  server.send(200, "application/json", buffer);
}

void stripOnOrange() {
  Serial.println("Strip on with orange");
  int r_orange = 226, g_orange = 121, b_orange = 35;
  for(int i=0; i<pixels_strip.numPixels(); i++) {
    int flicker = random(0,55);
    int r1 = r_orange-flicker;
    int g1 = g_orange-flicker;
    int b1 = b_orange-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    pixels_strip.setPixelColor(i,r1,g1, b1);
    pixels_strip.show();
  }
  create_json("Strip Status", 0, "Started");
  server.send(200, "application/json", buffer);
}

void stripOnPurple() {
  Serial.println("Strip on with purple");
  int r_purple = 158, g_purple = 8, b_purple = 148;
  for( ; ; ){
    for(int i=0; i<pixels_strip.numPixels(); i++) {
      int flicker = random(0,55);
      int r1 = r_purple-flicker;
      int g1 = g_purple-flicker;
      int b1 = r_purple-flicker;
      if(g1<0) g1=0;
      if(r1<0) r1=0;
      if(b1<0) b1=0;
      pixels_strip.setPixelColor(i,r1,g1, b1);
      pixels_strip.show();
    }
    break;
  }
  create_json("Strip Status", 0, "Started");
  server.send(200, "application/json", buffer);
}

void stripOnGreen() {
  Serial.println("Strip on with green");
  int r_green = 74, g_green = 150, b_green = 12;
  
  for(int i=0; i<pixels_strip.numPixels(); i++) {
    int flicker = random(0,55);
    int r1 = r_green-flicker;
    int g1 = g_green-flicker;
    int b1 = b_green-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    pixels_strip.setPixelColor(i,r1,g1, b1);
    pixels_strip.show();
  }
  create_json("Strip Status", 0, "Started");
  server.send(200, "application/json", buffer);
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  setup_routing();
  pixels.begin();
  pixels_strip.begin();
  pinMode(RING_PIN, INPUT);
  pinMode(STRIP_PIN, INPUT);
}

void loop() 
{
  server.handleClient();

  int r_orange = 226, g_orange = 121, b_orange = 35;
  for(int i=0; i<pixels_strip.numPixels(); i++) {
    int flicker = random(0,55);
    int r1 = r_orange-flicker;
    int g1 = g_orange-flicker;
    int b1 = b_orange-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    pixels_strip.setPixelColor(i,r1,g1, b1);
    pixels_strip.show();
  }
}
