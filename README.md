# Pumpkin


#### Components Used ####
*	NeoPixel Ring - 12 x 5050 RGB LED with Integrated Drivers x 2 (https://thepihut.com/products/adafruit-neopixel-ring-12-x-5050-rgb-led-with-integrated-drivers)
	* NeoPixel Stick - 8 x 5050 RGB LED with Integrated Drivers (https://thepihut.com/products/adafruit-neopixel-stick-8-x-5050-rgb-led-with-integrated-drivers)
	* ESP-32S ESP32 Development Board (https://thepihut.com/products/esp32-s2-saola-1r-dev-kit-featuring-esp32-s2-wrover)
	* LILYGO® TTGO T-Lion ESP32-WROVER 4MB SPI Flash And 8MB PSRAM 0.96OLED Five-Way Button 18650 Battery Holder (https://www.aliexpress.com/i/32970371816.html)
	* Mini PIR Motion Sensor with 3 Pin Header (https://thepihut.com/products/breadboard-friendly-mini-pir-motion-sensor-with-3-pin-header?variant=39749999788227)
	* Jumper Wires (https://thepihut.com/products/premium-female-male-extension-jumper-wires-40-x-12-300mm)
	* Breadboard and no, not one from the kitchen :=) (https://thepihut.com/products/raspberry-pi-breadboard-half-size)
	* Google Home Mini


#### Software Required ####
	* Arduino IDE 
	* Home Assistant 
	* Node-Red add-on installed in Home Assistant
	* ESPHome add-on installed in Home Assistant

#### Hardware Installation ####

	1. Solder the jumperwires to the Neopixel ring as per the example below 
	![image](https://user-images.githubusercontent.com/18738275/139216322-377f1baa-dcc2-4f82-b0f7-d8fbd45642f7.png)
	2. Solder the jumperwires to the Neopixel Stick as per the example below
	// add image
	3. Connect the wires soldered to the Neopixel ring to the LILYGO® TTGO T-Lion ESP32-WROVER GPIO pins as per the diagram below
	//add image
	4. Connect the wires soldered to the Neopixel stick to the LILYGO® TTGO T-Lion ESP32-WROVER GPIO pins as per the diagram below
	// add image
	5. Connect the PIR motion sensor to the ESP-32S ESP32 Development Board as per the diagram below
	// add image
	
#### Software Installation ####
	1. Assuming Arduino IDE is already installed, connect the LILYGO® TTGO T-Lion ESP32-WROVER to the computer via USB and upload the 
	   pumpkin.ino sketch

