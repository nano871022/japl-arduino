#define serial 9600
#include "String.h"
#include <SoftwareSerial.h>
#include <Car.h>
#include <Wifi.h>

bool enableSerial = true;
uint8_t aMFL = 11;
uint8_t aMFR = 10;
uint8_t aMBL = 9;
uint8_t aMBR = 6;
uint8_t wifiRst = 8;
uint8_t red = 7;
uint8_t blue = 5; 
uint8_t green = 4;
uint8_t rx = 3;
uint8_t tx = 2;

void(* resetSoftware)(void) = 0;

Wifi wifi(rx,tx);
Car car(aMFL,aMBL,aMFR,aMBR);

void setup() {
  
  Serial.begin(serial);
  wifi.leds(red,blue,green);
  wifi.begin(serial);
  car.begin();
  Serial.println("READY");
}

void loop() {
  String value = wifi.waitUDPConnection();
  carMove(value);
  closeAndOpenUdp(value);

  writeOnWifiFromSerial();  
  showWifiOnSerial();
}

void writeOnWifiFromSerial(){
  if(enableSerial){
    while(Serial.available()){
      wifi.print((char)Serial.read());
    }
  }
}

void showWifiOnSerial(){
  if(enableSerial){
    while(wifi.available()){
      Serial.print((char)wifi.read());
      delay(5);
    }
  }
}

void carMove(String value){
  if(value.indexOf("Y")>=0 && value.indexOf("X")>=0){
    uint8_t xpos = value.indexOf("X");
    uint8_t ypos = value.indexOf("Y");
    uint8_t moveX = value.substring(xpos+1,ypos).toInt();
    uint8_t moveY = value.substring(ypos+1).toInt();
    car.move(moveX,moveY);
  }
}

void closeAndOpenUdp(String value){
  if(value.length() > 0){
    wifi.closeAndOpenUDP();
  }
  if(wifi.getResets()>2){
    Serial.println("...HARD RESET...");
    resetSoftware();
  }
}

