# Maleficent Pumpkin 

#### Description ####
Which started out as an interest to understand how addressable LED's work, the interest quickly evolved in a "smart" pumpkin idea with colour changing eyes, creepy 
sounds and porch lights changing colour.

In order to keep my interest, interesting, I decided to used various different types of technology. The eyes and backlight are configured with C++ using Arduino 
libraries. The motion sensor is connected to a ESP32, flashed with ESPHome firmware which integrates seamlesly with Home Assistant.

What is Home Assistant?

Home Assistant is a free and open-source software for home automation that is designed to be the central control system for smart home devices with focus on local control and privacy. More info can be found at https://www.home-assistant.io/

To give the pumpkin a bit of personallity and for the motion sensor to trigger a string of events, it was a no brainer to use Node-Red for the automation.

What is Node-Red?

Node-Red is a flow-based development tool for visual programming developed originally by IBM for wiring together hardware devices, APIs and online services as part of the Internet of Things. Node-RED provides a web browser-based flow editor, which can be used to create JavaScript functions.

More info can be found at https://nodered.org/

#### Components Used ####
*	NeoPixel Ring - 12 x 5050 RGB LED with Integrated Drivers x 2 (https://thepihut.com/products/adafruit-neopixel-ring-12-x-5050-rgb-led-with-integrated-drivers)
*	NeoPixel Stick - 8 x 5050 RGB LED with Integrated Drivers (https://thepihut.com/products/adafruit-neopixel-stick-8-x-5050-rgb-led-with-integrated-drivers)
*	ESP-32S ESP32 Development Board (https://thepihut.com/products/esp32-s2-saola-1r-dev-kit-featuring-esp32-s2-wrover)
*	LILYGO® TTGO T-Lion ESP32-WROVER 4MB SPI Flash And 8MB PSRAM 0.96OLED Five-Way Button 18650 Battery Holder (https://www.aliexpress.com/i/32970371816.html)
* 	Mini PIR Motion Sensor with 3 Pin Header (https://thepihut.com/products/breadboard-friendly-mini-pir-motion-sensor-with-3-pin-header?variant=39749999788227)
*	Jumper Wires (https://thepihut.com/products/premium-female-male-extension-jumper-wires-40-x-12-300mm)
*	Breadboard and no, not one from the kitchen :=) (https://thepihut.com/products/raspberry-pi-breadboard-half-size)
*	Kasa Smart Bulb by TP-link (https://www.amazon.co.uk/gp/product/B07KXHDCVF/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1)
*	Google Nest Mini (https://store.google.com/gb/config/google_nest_mini?hl=en-GB)


#### Software Required ####
*	Arduino IDE 
*	Home Assistant 
*	Node-Red add-on installed in Home Assistant
*	ESPHome add-on installed in Home Assistant

#### Hardware Installation ####

1.	 Below diagram demonstrates how to connect the Adafruit LED's to the LILYGO® TTGO T-Lion ESP32-WROVER GPIO pins via the breadboard.

![rings_con](https://user-images.githubusercontent.com/18738275/139256348-9b839687-4a4a-446c-91fb-d2a77f8a1234.jpg)

*	Red = 5VDC
*	Green = Ground
*	Blue = Data


2.	 Connect the PIR motion sensor to the ESP-32S ESP32 Development Board as per the diagram below.

![esp](https://user-images.githubusercontent.com/18738275/139305163-d7ccd194-0453-413f-b879-ce4612f592e3.png)

	
#### Software Installation ####

***Adafruit Ring And Stick Config***

1.	Assuming Arduino IDE is already installed, connect the LILYGO® TTGO T-Lion ESP32-WROVER via USB.
2.	Import the pumpkin.ino sketch into Arduino IDE
3.	Enter wifi credentials in the SSID and PWD field as seen in below code snippet.

```js
const char *SSID = "ENTER_SSID_HERE";
const char *PWD = "ENTER_WIFI_PASSWORD_HERE";
```

3.	Upload the sketch and confirm via the serial monitor if the device succesfully connected to the defined SSID.
	
***Motion Sensor Config***

More information about ESPHome can be found at https://esphome.io/guides/getting_started_hassio.html.

Below Configuration can be added to the config yml file to enable use of the motion sensor.

```js
binary_sensor:
  - platform: gpio
    pin: GPIO27
    name: "Pumpkin Motion"
    device_class: motion
```

***Porch Light Config***

To enable access to the porch light in Node-Red, the standard porch light was replaced with a Kasa Smart Bulb and configured through the Kasa integration which will 
make the light available as an entity in Node-Red.

More information can be found at https://www.home-assistant.io/integrations/tplink/

#### Automation ####

In order to enable the motion sensor to trigger the events, a flow needs to be configured in Node-Red.

To simplify the process, the flows.json can be imported in Node-Red which will automatically create all the required nodes.

Below is a visual example of the flow.

![flow](https://user-images.githubusercontent.com/18738275/139308031-9d19dc17-3cef-4fa1-89f6-7b2722da2537.JPG)

Because we are using Home Assistant with ESPHome integration, the motion sensor will become available as an entity in Node-Red. 
This entity will be used in the first node name Motion On in the visual.

Below is a brief description of all the nodes used.

| Node  | Description |
| ------------- | ------------- |
| Motion On | Polls the motion sensor for any state changes  |
| Trigger 1 Min  | Will only send the first message if it matches the string and wait 1 min before sending another request |
| Porch Light on Red | Adjusts the porch light to red with low brightness |
| Rings On | Calls the endpoint on the LILYGO ESP to switch on the Adafruit Rings |
| Cast Rob Zombie | Casts media defined in the Media URL field to the available device e.g. in this case a Google Home |
| Delay 55s | Delays the flow for the defined amount of seconds before executing the next node |
| Porch Light On White | Adjusts the porch light back to white |

