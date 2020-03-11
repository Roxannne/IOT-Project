#include "config.h"
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* host = "api.openweathermap.org";
String api = "92350d56b8c3d479ca2a1b506e7c493c"; //Your API Key
String city = "Amsterdam";

int recuperation(){

  WiFiClient client;
//We connect to the host, which is OpenWheatherMap.
  Serial.printf("\n[Connexion to %s ... ", host);
  delay(500);
  if (client.connect(host, 80))
  {
    Serial.println("Connected!");
    delay(500);
    
    //We are preparing to send the request to the API
    client.print(String("GET /data/2.5/weather?q=" + city + "&APPID=" + api + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                ));
   
    //Here, we retrieve the answer from OpenWeather
     
    char status[32] = {0}; //In this char, we put the answer
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0) { 
      Serial.print(F("Unespected response: "));
      Serial.println(status);
      return 0;
    }
    else{
    delay(500);
    Serial.println("The answer just arrived !");
    delay(500);
    }
   char endOfHeaders[] = "\r\n\r\n";

   
    if (!client.find(endOfHeaders)) {
      Serial.println(F("Error in the answer"));
      return 0;
    }
    else{
      Serial.println("");
      Serial.println("============================================================");
      Serial.println("");
      delay(500);
      Serial.println("Processing request...");
    }

    //Declaration of a dynamic Json document
    const size_t capacity =JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 390;
    DynamicJsonDocument jsonDocument(capacity);
    
    DeserializationError error = deserializeJson(jsonDocument, client);
    if (error) {
    Serial.println("There was an error while deserializing");
    return 0;
    }
    
    JsonObject root = jsonDocument.as<JsonObject>();

   //we take from the Json document the info we need: here, the weather, the average, maximum and minimum temperature.
    const char* temps = root["weather"][0]["main"]; 
    float temperature_av = root["main"]["temp"];
    float temperature_min = root["main"]["temp_min"];
    float temperature_max = root["main"]["temp_max"];
    int id = root["weather"][0]["id"];
    sunrise = root["sys"]["sunrise"];
    sunset = root["sys"]["sunset"];
    timez = root["timezone"];
    dt = root["dt"];
    dt += timez;

  //We convert Fahrenheit to degree
    temperature_av = temperature_av - 273.15;
    temperature_min = temperature_min - 273.15;
    temperature_max = temperature_max - 273.15;

    Serial.print("The average temperature in ");
    Serial.print(city);
    Serial.print(" is ");
    Serial.print(temperature_av);
    Serial.println("°C");


    client.stop();
    return id;
  }
}
