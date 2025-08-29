// ARDUINO CODE FOR THE PROJECT

// LIBRARIES
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
#include <TinyGPS++.h>

// DEFINING PINS
#define rxPin 2 // GSM Module RX pin to Arduino 3
#define txPin 3 // GSM Module TX pin to Arduino 2
#define pulsePin A0 // pulse sensor to this analog pin
#define buttonPin 4 // Pin for the push button

SoftwareSerial sim800(rxPin, txPin);
AltSoftSerial neogps;
TinyGPSPlus gps;

// phone number to receive sms alerts.
const String PHONE = "XXXXXXXXXX"; //ENTER YOUR NUMBER HERE!!!

bool buttonState = false;
bool lastButtonState = false;

// Size of the geo-fence (in meters)
const float maxDistance = 50;

//ENTER YOUR COORDINATES HERE TO CENTER THE GEOFENCE!!!
float initialLatitude = XXYY;
float initialLongitude = XXYY;
float latitude, longitude;

unsigned long lastAlertTime = 0;
const unsigned long alertInterval = 120000; // 2 minutes in milliseconds

void getGps(float& latitude, float& longitude);
float getDistance(float flat1, float flon1, float flat2, float flon2);
float getPulse();
void sendAlert(float pulse);
void CallNumber();




void setup() {
  Serial.begin(9600);
  sim800.begin(9600);
  neogps.begin(9600);
  
  pinMode(buttonPin, INPUT_PULLUP); // Set the push button pin as input with internal pull-up resistor
  
  sim800.println("AT");
  delay(1000);
  sim800.println("ATE1");
  delay(1000);
  sim800.println("AT+CPIN?");
  delay(1000);
  sim800.println("AT+CMGF=1");
  delay(1000);
  sim800.println("AT+CNMI=1,1,0,0,0");
  delay(1000);
  
  delay(20000);
}




void loop() {
  // Read the button state
  buttonState = digitalRead(buttonPin);
  
  // Check if the button state has changed from HIGH to LOW (indicating a button press)
  if (buttonState == LOW && lastButtonState == HIGH) {
    Serial.println("Button pressed!");
    CallNumber();
  }
  lastButtonState = buttonState;
  
  getGps(latitude, longitude);
  float distance = getDistance(latitude, longitude, initialLatitude, initialLongitude);
  float pulse = getPulse();
  
  Serial.print("Latitude= "); Serial.println(latitude, 6);
  Serial.print("Longitude= "); Serial.println(longitude, 6);
  Serial.print("Initial Latitude= "); Serial.println(initialLatitude, 6);
  Serial.print("Initial Longitude= "); Serial.println(initialLongitude, 6);
  Serial.print("Current Distance= "); Serial.println(distance);
  Serial.print("Pulse: "); Serial.println(pulse);
  
  if (distance > maxDistance && millis() - lastAlertTime >= alertInterval) {
    sendAlert(pulse);
    lastAlertTime = millis(); // Update last alert time
    delay(5000);
  }
  
  while (sim800.available()) {
    delay(1000);
    Serial.println(sim800.readString());
  }
  
  while (Serial.available()) {
    delay(1000);
    sim800.println(Serial.readString());
  }
}



// OTHER FUNCTIONS 


float getDistance(float flat1, float flon1, float flat2, float flon2) {
  float dist_calc=0;
  float dist_calc2=0;
  float diflat=0;
  float diflon=0;
  
  diflat = radians(flat2-flat1);
  flat1 = radians(flat1);
  flat2 = radians(flat2);
  diflon = radians((flon2)-(flon1));
  
  dist_calc = (sin(diflat/2.0)*sin(diflat/2.0));
  dist_calc2 = cos(flat1);
  dist_calc2 *= cos(flat2);
  dist_calc2 *= sin(diflon/2.0);
  dist_calc2 *= sin(diflon/2.0);
  dist_calc += dist_calc2;
  
  dist_calc = (2*atan2(sqrt(dist_calc),sqrt(1.0-dist_calc)));
  dist_calc *= 6371000.0;
  
  return dist_calc;
}




void getGps(float& latitude, float& longitude) {
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;) {
    while (neogps.available()) {
      if (gps.encode(neogps.read())) {
        newData = true;
        break;
      }
    }
  }
  
  if (newData) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    newData = false;
  } else {
    Serial.println("No GPS data is available");
    latitude = 0;
    longitude = 0;
  }
}



float getPulse() {
  int sensorValue = analogRead(pulsePin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float pulse = (voltage - 0.5) * 100;
  return pulse;
}




void sendAlert(float pulse) {
  String sms_data;
  sms_data = "Alert! The object is outside the fence.\r";
  sms_data += "GPS Location: http://maps.google.com/maps?q=loc:";
  sms_data += String(latitude) + "," + String(longitude) + "\r";
  sms_data += "Pulse: " + String(pulse) + " bpm";
  
  sim800.print("AT+CMGF=1\r");
  delay(1000);
  sim800.print("AT+CMGS=\""+PHONE+"\"\r");
  delay(1000);
  sim800.print(sms_data);
  delay(100);
  sim800.write(0x1A); // ascii code for ctrl-26
  delay(1000);
  Serial.println("SMS Sent Successfully.");
}



String readSerial() {
  delay(100);
  if (sim800.available()) {
    return sim800.readString();
  }
}



void CallNumber() {
  sim800.println("ATD+XXXXXXXXXX;"); // IF YOU'RE SEEING THIS, DON'T FORGET TO CHANGE THE NUMBER HERE AS WELL
  delay(500); // Short delay before checking response
  Serial.println(readSerial());
  delay(20000);
  sim800.println("ATH");
  delay(200);
  Serial.println(readSerial());
}



// Feed it to your arduino and voilaa!
