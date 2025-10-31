# Smart Fan Control System (ESP32 + DHT11 + Blynk)

## Overview
This project is a Smart Fan Control System that automatically adjusts the fan speed based on room temperature while also offering manual control through the Blynk IoT app.  
The system uses a DHT11 sensor to monitor temperature and humidity, and controls the fan with PWM using the ESP32.  
Users can switch between **Automatic Mode** (temperature-based control) and **Manual Mode** (slider-based control).

## Features
- Real-time temperature & humidity monitoring  
- Automated fan speed control based on temperature thresholds  
- Manual fan speed control via Blynk slider  
- Auto/Manual mode switching  
- Live temperature-humidity data on Blynk  
- Fully remote control  
- Smooth PWM fan speed control  

## Hardware Components
- ESP32 Development Board  
- DHT11 Temperature & Humidity Sensor  
- DC Fan (5V/12V)  
- Motor Driver / MOSFET (L298N )  
- External Power Supply  
- Jumper Wires  

## Software Components
- Arduino IDE  
- Blynk IoT Platform  
- Libraries Required:  
  - `DHT.h`  
  - `WiFi.h`  
  - `BlynkSimpleEsp32.h`

## Installation
1. Connect DHT11 sensor to ESP32 (e.g., DATA → GPIO 4).  
2. Connect Fan driver MOSFET/Relay to PWM pin (e.g., GPIO 5).  
3. Configure PWM channel, frequency, and resolution in code.  
4. Create a Blynk Template and obtain Auth Token.  
5. Install required libraries in Arduino IDE.  
6. Upload the program to ESP32.  
7. Configure thresholds or adjust fan speed in Blynk.

## Working Video Demo

[![Smart Fan Control Demo](https://img.youtube.com/vi/YOUR_VIDEO_ID/maxresdefault.jpg)](https://youtu.be/YOUR_VIDEO_ID)

## Usage
- Monitor temperature and humidity via Blynk.  
- Fan automatically changes speed based on temperature thresholds.  
- Switch to Manual Mode for custom fan speed using slider.  
- Adjust slider (0–255) for PWM output control.  

## Future Scope
- OLED display for offline monitoring  
- Time-based scheduling  
- Home automation integration  
- Energy-efficient control algorithms  
- PID-based precision fan control  

## Contribution
Contributions, issues, and feature requests are welcome.  
Feel free to open issues or submit pull requests.

## License
This project is licensed under the MIT License.

## Contact
For queries or support, email: **mohasinmulla861@gmail.com**
