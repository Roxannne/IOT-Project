#include "LedControl.h"

//For the 8x8 matrix
LedControl lc=LedControl(D1,D3,D2,1);

//cloud
byte n[8]= {B00000000,B00011000,B00100100,B00100100,B01000010,B01000010,B00111100,B00000000};
//sun
byte s[8]= {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
//thunderstrike
byte ts[8]= {B00000100,B00001000,B00010000,B00111110,B0000010,B00001000,B00100000,B00100000};
//sun-cloud
byte sc[8]= {B01001010,B00111100,B11111111,B00111100,B01111110,B10000001,B10000001,B01000010};
//mist
byte m[8]= {B00000000,B00111100,B11110000,B00111110,B01111000,B00111110,B01111000,B00000000};
//snow
byte snow[8]= {B01111110,B11111111,B01111110,B01010000,B00100100,B00001000,B01010010,B00000000};
//r
byte r[8]= {B01111110,B11111111,B01111111,B01111110,B01000000,B10010010,B00100100,B00000000};

void setupMatrix(){
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,8);
  // Clear the display
  lc.clearDisplay(0); 
}


void drawweather(int id){
//  Display cloud

if(id == 800){
  lc.setRow(0,0,s[0]);
  lc.setRow(0,1,s[1]);
  lc.setRow(0,2,s[2]);
  lc.setRow(0,3,s[3]);
  lc.setRow(0,4,s[4]);
  lc.setRow(0,5,s[5]);
  lc.setRow(0,6,s[6]);
  lc.setRow(0,7,s[7]);
}
else if(id == 801){
  lc.setRow(0,0,sc[0]);
  lc.setRow(0,1,sc[1]);
  lc.setRow(0,2,sc[2]);
  lc.setRow(0,3,sc[3]);
  lc.setRow(0,4,sc[4]);
  lc.setRow(0,5,sc[5]);
  lc.setRow(0,6,sc[6]);
  lc.setRow(0,7,sc[7]);
}
else if(id == 802 || id == 803 || id == 804){
  lc.setRow(0,0,n[0]);
  lc.setRow(0,1,n[1]);
  lc.setRow(0,2,n[2]);
  lc.setRow(0,3,n[3]);
  lc.setRow(0,4,n[4]);
  lc.setRow(0,5,n[5]);
  lc.setRow(0,6,n[6]);
  lc.setRow(0,7,n[7]);
}
else if((id >=300 && id <=321)||(id >= 500 && id <=531)){
  lc.setRow(0,0,r[0]);
  lc.setRow(0,1,r[1]);
  lc.setRow(0,2,r[2]);
  lc.setRow(0,3,r[3]);
  lc.setRow(0,4,r[4]);
  lc.setRow(0,5,r[5]);
  lc.setRow(0,6,r[6]);
  lc.setRow(0,7,r[7]);
}
else if(id >=200 && id <= 232){
  lc.setRow(0,0,ts[0]);
  lc.setRow(0,1,ts[1]);
  lc.setRow(0,2,ts[2]);
  lc.setRow(0,3,ts[3]);
  lc.setRow(0,4,ts[4]);
  lc.setRow(0,5,ts[5]);
  lc.setRow(0,6,ts[6]);
  lc.setRow(0,7,ts[7]);
}
else if(id >= 600 && id <= 622){
  lc.setRow(0,0,snow[0]);
  lc.setRow(0,1,snow[1]);
  lc.setRow(0,2,snow[2]);
  lc.setRow(0,3,snow[3]);
  lc.setRow(0,4,snow[4]);
  lc.setRow(0,5,snow[5]);
  lc.setRow(0,6,snow[6]);
  lc.setRow(0,7,snow[7]);
}
else if(id >= 700 && id <= 781){
  lc.setRow(0,0,m[0]);
  lc.setRow(0,1,m[1]);
  lc.setRow(0,2,m[2]);
  lc.setRow(0,3,m[3]);
  lc.setRow(0,4,m[4]);
  lc.setRow(0,5,m[5]);
  lc.setRow(0,6,m[6]);
  lc.setRow(0,7,m[7]);
}
}
