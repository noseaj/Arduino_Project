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
<img src="https://github.com/noseaj/Arduino_Project/blob/main/Fingerprint%20Recognition%20Automatic%20Attendance%20System/How%20it%20works.png" width="600" height="300">  

### Implementation video
[Video Link](https://www.youtube.com/watch?v=q5QmAOgT_lc&ab_channel=%EC%86%90%EC%9E%AC%EC%84%B1)

****
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
