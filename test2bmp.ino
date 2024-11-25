#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_BMP085.h>

#include "DHT.h"
#define DHTPIN D3
#define DHTTYPE DHT11
#define soil_moisture_pin A0

#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
#include "addons/TokenHelper.h"

#include "addons/RTDBHelper.h"

#define WIFI_SSID "Ben10Moto5G"
#define WIFI_PASSWORD "motopranavg73"

#define API_KEY "AIzaSyBYqrAG5Yd332woLcWFOsk3jOAS-NuCTt4"
#define DATABASE_URL "openlab-44938-default-rtdb.firebaseio.com/" 
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;

void setup(){
  pinMode(DHTPIN, INPUT);
  dht.begin();
  Serial.begin(9600);
  if (!bmp.begin()) {
      Serial.println("Could not find a valid BMP085 sensor, check wiring!");
      while (1) {}
  }
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; 
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
 delay(1000);
  float h = dht.readHumidity();

  float t = dht.readTemperature();

  float m = analogRead(soil_moisture_pin);

   float pa = bmp.readPressure();
  
  if (Firebase.ready() && signupOK ) {
    
    if (Firebase.RTDB.setFloat(&fbdo, "DHT/humidity",h)){
       Serial.print("Humidity: ");
       Serial.println(h);
      
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    if (Firebase.RTDB.setFloat(&fbdo, "DHT/temperature", t)){
       Serial.print("Temperature: ");
       Serial.println(t);
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    if (Firebase.RTDB.setFloat(&fbdo, "DHT/moisture", m)){
       Serial.print("Moisture : ");
       Serial.println(m);
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }

   
    if (Firebase.RTDB.setFloat(&fbdo, "DHT/pressure", pa)){
      Serial.print("Pressure : ");
       Serial.println(pa);
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  

  }
  Serial.println("");
}