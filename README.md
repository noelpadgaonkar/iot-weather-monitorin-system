The proposed system has basic components i.e. Arduino Micro-Controller, Sensors, ESP 8266 Node MCU Wi-Fi Module, SD Card Module, Real Time Clock (RTC) and LCD.

# Hardware
a) The Arduino Micro-Controller is the main controller for this proposed system. All the components are connected to this Micro-Controller. The sensors used are rain sensor, temperature and humidity sensor.

b) The Rain Sensor determines the intensity of the rainfall i.e. heavy rain or light rain or no rain. The droplets of water make contact with the rain sensor pad and send the data to the controller. 

c) The Temperature and Humidity sensor determines the temperature and humidity of the atmosphere. This sensor is a single sensor which detects both, temperature and humidity. The above described sensors will be connected to the Arduino as well as the ESP 8266 Node MCU. 

d) The Arduino unit will focus on collection of data from the sensors, as well as the date and time from RTC as well as store data on the Micro SD Card. 

e) The LCD connected will display the real time readings on the go.

f) The ESP 8266 Node MCU is also connected to the sensors and will send the data collected from the sensors over the internet to ThingSpeak Portal by connecting to a Wi-Fi network. 

# Software 
The data will be obtained from the ThingSpeak Cloud Server and will be formulated and displayed to the user on the portal’s graphic user interface (GUI) via a Web Browser

# Files
1) Arduino_SD.ino - The Arduino code consisiting of the RTC, SD Card, Sensors and LCD Functionality
2) ESP_8266_Node_MCU - The Arduino code consisting of the WiFi and ThingSpeak functionality
