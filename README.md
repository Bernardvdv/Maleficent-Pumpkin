# Pumpkin


#### Components Used ####
*	NeoPixel Ring - 12 x 5050 RGB LED with Integrated Drivers x 2 (https://thepihut.com/products/adafruit-neopixel-ring-12-x-5050-rgb-led-with-integrated-drivers)
*	NeoPixel Stick - 8 x 5050 RGB LED with Integrated Drivers (https://thepihut.com/products/adafruit-neopixel-stick-8-x-5050-rgb-led-with-integrated-drivers)
*	ESP-32S ESP32 Development Board (https://thepihut.com/products/esp32-s2-saola-1r-dev-kit-featuring-esp32-s2-wrover)
*	LILYGO® TTGO T-Lion ESP32-WROVER 4MB SPI Flash And 8MB PSRAM 0.96OLED Five-Way Button 18650 Battery Holder (https://www.aliexpress.com/i/32970371816.html)
* 	Mini PIR Motion Sensor with 3 Pin Header (https://thepihut.com/products/breadboard-friendly-mini-pir-motion-sensor-with-3-pin-header?variant=39749999788227)
*	Jumper Wires (https://thepihut.com/products/premium-female-male-extension-jumper-wires-40-x-12-300mm)
*	Breadboard and no, not one from the kitchen :=) (https://thepihut.com/products/raspberry-pi-breadboard-half-size)
*	Google Home Mini


#### Software Required ####
*	Arduino IDE 
*	Home Assistant 
*	Node-Red add-on installed in Home Assistant
*	ESPHome add-on installed in Home Assistant

#### Hardware Installation ####

	1. Solder the jumperwires to the Neopixel ring as per the example below 
![ring](https://user-images.githubusercontent.com/18738275/139252725-07899b87-e1be-4a13-8b11-579c8e1bfbaf.png)

	2. Solder the jumperwires to the Neopixel Stick as per the example below
![stick](https://user-images.githubusercontent.com/18738275/139253722-446a7b0a-0dd9-4230-89f7-d38753adb4dd.jpg)

	3. Connect the jumper wires as per the below diagram to the LILYGO® TTGO T-Lion ESP32-WROVER GPIO pins
![rings_con](https://user-images.githubusercontent.com/18738275/139256348-9b839687-4a4a-446c-91fb-d2a77f8a1234.jpg)
*	Red = 5VDC
*	Green = Ground
*	Blue = Data

5. Connect the PIR motion sensor to the ESP-32S ESP32 Development Board as per the diagram below
	// add image
	
#### Software Installation ####
1.	Assuming Arduino IDE is already installed, connect the LILYGO® TTGO T-Lion ESP32-WROVER to the computer
2.	Enter wifi credentials in the SSID and PWD field as seen in below code snippet
	<pre><code>#include <WiFi.h>
<pre><code>#include <WebServer.h>
<pre><code>#include <ArduinoJson.h>
<pre><code>#include <Adafruit_NeoPixel.h>

<pre><code>// Variables
<pre><code>#define RING_PIN 15
<pre><code>#define STRIP_PIN 2
<pre><code>#define NUMPIXELS 24
<pre><code>#define NUMPIXELSSTRIP 8

<pre><code>int wait_in_between_led = 20;

<pre><code>// Web server running on port 80
<pre><code>WebServer server(80);

<pre><code>// JSON data buffer
<pre><code>StaticJsonDocument<250> jsonDocument;
<pre><code>char buffer[250];
<pre><code>
<pre><code>//LED Ring Init
<pre><code>Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RING_PIN, NEO_GRB + NEO_KHZ800);
<pre><code>
Adafruit_NeoPixel pixels_strip = Adafruit_NeoPixel(NUMPIXELSSTRIP, STRIP_PIN, NEO_GRB + NEO_KHZ800);

<pre><code>const char *SSID = "ENTER_SSID_HERE";
<pre><code>const char *PWD = "ENTER_WIFI_PASSWORD_HERE";

	

