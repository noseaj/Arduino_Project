# Arduino_Project  
## Fingerprint Recognition Automatic Attendance System
Non-face-to-face fingerprint recognition attendance & Prevent roll call
### Components
- WeMos D1 R2 (ESP8266)
- Fingerprint Sensor (AS608)
- OLED Display
- Adafruit IO (Cloud System)
### Function Description
- WeMos D1 R2 : Data is exchanged with Adafruit IO via WLAN communication.
- Fingerprint Sensor : Fingerprint recognition, registration, deletion.
- OLED Display : Output student information.
- Adafruit IO : Save and research data, Display real-time data online via dashboard.
### How it works
Input : User fingerprint recognition with fingerprint sensor →  
Cloud : Save student information to the cloud that fits the fingerprints →  
User terminal : Check attendance  

## City Forecast  
Get current weather data for a particular city on Earth from "OpenWeatherMap.org."  
### Components
- WeMos D1 R2 (ESP8266)
- OLED Display
### How it works
Connect to the openWeatherMap API https://openweathermap.org/ → You have to sign up and create API key to get current weather data → Use data JSON format  
### Output
```
City : Seoul
Weather : Clouds
Temperature : -5
Humidity : 91
```
