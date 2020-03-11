#include <Adafruit_NeoPixel.h>
#include "config.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ400);
int delayval = 250;
int j = 0;

void setupColor(){
  pixels.begin();
  pixels.setBrightness(100);
}




void handleColor(int id){
    if(id == 800){
    //clear sky - yellow
     for(int i = 0; i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(255,255,0));
      pixels.show();
     }
  }
  else if(id == 801){
    //few clouds - yellow gray
    for(int i = 0; i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(182,179,43));
      pixels.show();
     }
  }
  else if(id == 802 || id == 803 || id == 804){
    //cloudy - grey
    for(int i = 0; i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(128,128,128));
      pixels.show();
     }
  }
  else if((id >=300 && id <=321)||(id >= 500 && id <=531)){
    //rain - blue
    for(int i = 0; i<NUMPIXELS;i++){
      //pixels.setPixelColor(i,pixels.Color(93,138,166));
      pixels.setPixelColor(i,pixels.Color(0,0,255));
      pixels.show();
     }
  }
  else if(id >=200 && id <= 232){
    //storm - red
    for(int i = 0; i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(255,0,0));
      pixels.show();
     }
  }
  else if(id >= 600 && id <= 622){
    //snow - white
    for(int i = 0; i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(255,255,255));
      pixels.show();
     }
  }
  else if(id >= 700 && id <= 781){
    //mist - purple
    for(int i = 0; i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(153,37,118));
      pixels.show();
     }
  }
  else{
    for(int i = 0; i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(0,0,0));
      pixels.show();
     }
  }
}





void handleTime(){
  if(dt >= (sunrise + timez) && dt <= (sunset + timez)){
    for(int i = 0; i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(255,255,255));
      pixels.show();
      //delay(1000);
    }
  }
  else{
    for(int i = 0; i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(255,174,0));
      pixels.show();
      //delay(1000);
    }
  }
}




void handleIntensity(){
  j= map(analogRead(sensorPin), 100, 800, 256, 0);
  if (j < 0){
    j = 0;
  }
  for(int i = 0; i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(j,j,j));
    pixels.show();
  }
  //Serial.println(j);
}




void rainbow(){
  while (j<256){
  for(int i = 0; i<NUMPIXELS;i++){
  pixels.setPixelColor(i,pixels.Color(j,0,255));
  pixels.show(); 
  j++;
 }
}

while (j>0){
  for(int i = 0; i<NUMPIXELS;i++){
  pixels.setPixelColor(i,pixels.Color(255,0,j));
  pixels.show(); 
  j--;
  }
}

 while (j<256){
  for(int i = 0; i<NUMPIXELS;i++){
  pixels.setPixelColor(i,pixels.Color(255,j,0));
  pixels.show(); 
  j++;
 }
}
while (j>0){
  for(int i = 0; i<NUMPIXELS;i++){
  pixels.setPixelColor(i,pixels.Color(j,255,0));
  pixels.show(); 
  j--;
 }
}
 while (j<256){
  for(int i = 0; i<NUMPIXELS;i++){
  pixels.setPixelColor(i,pixels.Color(0,255,j));
  pixels.show(); 
  j++;
 }
}
while (j>0){
  for(int i = 0; i<NUMPIXELS;i++){
  pixels.setPixelColor(i,pixels.Color(0,j,255));
  pixels.show(); 
  j--;
 }
}
}
