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

1.	 Below diagram demonstrates how to connect the LED's to the LILYGO® TTGO T-Lion ESP32-WROVER GPIO pins via the breadboard

![rings_con](https://user-images.githubusercontent.com/18738275/139256348-9b839687-4a4a-446c-91fb-d2a77f8a1234.jpg)

*	Red = 5VDC
*	Green = Ground
*	Blue = Data


2.	 Connect the PIR motion sensor to the ESP-32S ESP32 Development Board as per the diagram below

![esp](https://user-images.githubusercontent.com/18738275/139305163-d7ccd194-0453-413f-b879-ce4612f592e3.png)

	
#### Software Installation ####

***Adafruit Ring And Stick Config***

1.	Assuming Arduino IDE is already installed, connect the LILYGO® TTGO T-Lion ESP32-WROVER via USB
2.	Enter wifi credentials in the SSID and PWD field as seen in below code snippet

```js
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

const char *SSID = "ENTER_SSID_HERE";
const char *PWD = "ENTER_WIFI_PASSWORD_HERE";
```

3.	Upload the sketch and confirm via the serial monitor if the device succesfully connected to the defined SSID
	
***Motion Sensor Config***

More information about ESPHome can be found at https://esphome.io/guides/getting_started_hassio.html

Below Configuration can be added to the config yml file to enable use of the motion sensor

```js
binary_sensor:
  - platform: gpio
    pin: GPIO27
    name: "Pumpkin Motion"
    device_class: motion
```

#### Automation ####

In order to enable the motion sensor to trigger the events, a flow needs to be configured in Node-Red. 
More info regarding Node-Red can be found at https://nodered.org/

To simplify the process, the flow.json can be imported in Node-Red which will automatically create all the nodes

Below is a visual example of the flow

![flow](https://user-images.githubusercontent.com/18738275/139308031-9d19dc17-3cef-4fa1-89f6-7b2722da2537.JPG)



