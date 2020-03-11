#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiManager.h>  
#include <DNSServer.h>


#include "binary.h"
#include "color.h"
#include "apiConnection.h"
#include "matrix.h"
#include "webpage.h"

ESP8266WebServer server(80); 

//Variables
int variableColor = 1;
int variableIntensity = 0;
int variableTime = 0;
unsigned long previousMillis = 0; 
int id = 1;


//Declaration of the parameters for the wifi
//const char* ssid = "RoxanesiPhone";
//const char* password = "louissss";



//interruptions
ICACHE_RAM_ATTR void detectsButtonColor(){
  variableColor= 1;
  variableIntensity= 0;
  variableTime= 0;
}

ICACHE_RAM_ATTR void detectsButtonIntensity(){
  variableColor= 0;
  variableIntensity= 1;
  variableTime= 0;
}

ICACHE_RAM_ATTR void detectsButtonTime(){
  variableColor= 0;
  variableIntensity= 0;
  variableTime= 1;
}



//Functions for the webpage
void handleRoot() {
   server.send(201, "text/html", page);
}

void handleCity() {
  if( ! server.hasArg("ville")|| server.arg("ville") == NULL){
    server.send(400, "text/plain", "400: Invalid Request");         // The request is invalid, so send HTTP status 400
    return;
  }
  else{
    city = server.arg("ville");
    previousMillis = 0; 
    handleRoot();
  }
}

void handleCol(){
  variableColor= 1;
  variableIntensity= 0;
  variableTime= 0;
  handleRoot();
}

void handleInten(){
  variableColor= 0;
  variableIntensity= 1;
  variableTime= 0;
  handleRoot();
}

void handleTemp(){
  variableColor= 0;
  variableIntensity= 0;
  variableTime= 1;
  handleRoot();
}



void setup()
{
  
  Serial.begin(115200);
  Serial.println();
  pinMode(ButtonColor, INPUT);
  pinMode(ButtonIntensity, INPUT);
  pinMode(ButtonTime, INPUT);

 /* if (!WiFi.config(ip, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }*/
  
  setupMatrix();
  setupColor();
  attachInterrupt(digitalPinToInterrupt(ButtonColor), detectsButtonColor, RISING);
  attachInterrupt(digitalPinToInterrupt(ButtonIntensity), detectsButtonIntensity, RISING);
  attachInterrupt(digitalPinToInterrupt(ButtonTime), detectsButtonTime, RISING);
  server.on("/", HTTP_GET, handleRoot);
  server.on("/Validate", HTTP_POST, handleCity);
  server.on("/Color", HTTP_POST, handleCol);
  server.on("/Intensity", HTTP_POST, handleInten);
  server.on("/Time", HTTP_POST, handleTemp);

  server.begin();
}





void wifi(){
//Wifi connection
  /*Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) //While the device is not connected, print ...
  {
    delay(500);
    Serial.print(".");
   
  }
  //Serial.println(" connected");*/
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  rainbow();
  
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());               // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); 
}




void loop () {
  server.handleClient(); 
  if(WiFi.status() != WL_CONNECTED){  //If we are not connected to the wifi, we call the function to connect
    wifi();
  }
  else{                               //If we are connected, we can connect to openWeatherMap
  unsigned long currentMillis = millis();


  if(variableColor == 1){
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      id = recuperation();
      drawweather(id);
    }
    handleColor(id);
  }
  else if(variableIntensity == 1){
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      id = recuperation();
      drawweather(id);
    }
    handleIntensity();
  }
  else if(variableTime == 1){
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      id = recuperation();
      drawweather(id);
    }
    handleTime();
  }



  if (id == 0){
    Serial.println("Error");
    id = recuperation();
  }
  else if (id == 1){
    id = recuperation();
    drawweather(id);
    handleColor(id);
  }
 }
}
