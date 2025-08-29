# Doguino
## IoT Project - Smart dog harness - part of capstone project in Christ (Deemed To Be University)

A comprehensive IoT-based solution for monitoring and enhancing the health, safety, and well-being of dogs through advanced wearable technology.

## Project Overview

The Smart Dog Harness is an innovative pet care solution that integrates cutting-edge technology into a comfortable wearable harness. It provides real-time health monitoring, GPS tracking, geofencing alerts, and wireless communication capabilities to keep your furry companion safe and healthy.

## Features

- **Real-time Heart Rate and Temperature Monitoring**: Continuous pulse monitoring using a non-invasive ear clip sensor
- **GPS Tracking**: Real-time location tracking with Google Maps integration
- **Geofencing Alerts**: SMS notifications when your dog leaves predefined safe zones
- **Emergency Communication**: Push-button emergency calling feature
- **Wireless Connectivity**: GSM/SMS communication for remote monitoring

## Hardware Components

### Main Components
- **Arduino Uno** - Main microcontroller
- **NEO-6M GPS Module** - Location tracking
- **SIM800C GSM Module** - Cellular communication
- **HC-05 Bluetooth Module** - Wireless data transmission
- **Pulse Rate Sensor** - Heart rate monitoring
- **LM35 Temperature Sensor** - Body temperature measurement
- **Push Button** - Emergency calling

### Pin Configuration
```
GPS Module (NEO-6M):
- RX → Pin 8 (AltSoftSerial)
- TX → Pin 9 (AltSoftSerial)

GSM Module (SIM800C):
- RX → Pin 2
- TX → Pin 3

Pulse Sensor:
- Signal → A0

Push Button:
- Signal → Pin 4 (with internal pullup)
```

## Required Libraries

Install these libraries through the Arduino IDE Library Manager:

```cpp
#include <SoftwareSerial.h>  // Built-in library
#include <AltSoftSerial.h>   // For GPS communication
#include <TinyGPS++.h>       // GPS data parsing
```

## Getting Started

### 1. Hardware Setup
1. Connect all components according to the pin configuration
2. Insert a valid SIM card into the SIM800C module
3. Ensure proper power supply for all modules
4. Attach the pulse sensor clip to the dog's ear

### 2. Software Configuration
1. Clone this repository
2. Open `smart_dog_harness.ino` in Arduino IDE
3. Install required libraries
4. Update the following constants in the code:

```cpp
const String PHONE = "XXXXXXXXXX";     // Replace with your phone number
float initialLatitude = XXYY;      // Replace with your home latitude
float initialLongitude = XXYY;      // Replace with your home longitude
const float maxDistance = XXX;            // Geofence radius in meters
```

### 3. Upload and Test
1. Upload the code to Arduino Uno
2. Open Serial Monitor (9600 baud) to view debug information
3. Test GPS signal acquisition
4. Verify SMS functionality
5. Test emergency calling feature

## How It Works

### Initialization Process
1. Power on the device
2. GSM module initializes and connects to network
3. GPS module starts acquiring satellite signals
4. System enters monitoring mode

### Monitoring Features
- **Continuous GPS Tracking**: Updates location every few seconds
- **Heart Rate Monitoring**: Reads pulse sensor data continuously
- **Geofence Monitoring**: Calculates distance from home base
- **Alert System**: Sends SMS when dog exits safe zone

### Emergency Features
- **Push Button**: Instant emergency call to owner
- **Automatic Alerts**: SMS with GPS location and health data
- **Real-time Communication**: Two-way SMS communication

## Data Output

The system provides real-time data through:
- **Serial Monitor**: Debug information and sensor readings
- **SMS Alerts**: Location links and health data
- **Emergency Calls**: Direct voice communication

Sample SMS Alert:
```
Alert! The object is outside the fence.
GPS Location: http://maps.google.com/maps?q=loc:XXXX,XXXX
Pulse: 85 bpm
```

## Configuration Options

### Geofencing
- Adjust `maxDistance` to change safe zone radius
- Modify `initialLatitude` and `initialLongitude` for home base
- Set `alertInterval` to control alert frequency

### Communication
- Update `PHONE` constant with emergency contact
- Modify SMS message format in `sendAlert()` function
- Adjust call duration in `CallNumber()` function

## Safety Features

- **Non-invasive Monitoring**: Comfortable ear clip sensors
- **Emergency Communication**: Direct calling capability
- **Real-time Alerts**: Immediate notifications for safety breaches
- **Health Monitoring**: Continuous vital sign tracking
- **Location Tracking**: Always know your pet's whereabouts

## Technical Specifications

- **Operating Voltage**: 5V DC
- **GPS Accuracy**: ±3 meters
- **Communication Range**: Global (GSM coverage dependent)
- **Battery Life**: 8-12 hours (depending on usage)
- **Geofence Range**: 10-1000 meters (configurable)
- **Update Frequency**: 2-5 seconds


## Authors

- **Susan Mani** 
- **Somya Chibhrani** 
- **Ayush Kumar** 

**Project Supervisor**: Prof. MUKUND N N  
**Institution**: CHRIST (Deemed to be University), Bengaluru


## Important Notes

- Ensure proper SIM card activation and balance for SMS/calling features
- GPS accuracy may vary based on satellite visibility
- Regular calibration of sensors is recommended
- Always test the system before actual deployment
- Ensure waterproofing for outdoor use
