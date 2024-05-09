#define serial 9600
#define aX 9
#define aY A0
#define dC 16
#include "Arduino.h"
#include "String.h"
#include <ESP8266WiFi.h>
#include <WifiNodeMCU.h>
#include <Jostick.h>


WifiNodeMCU modeMCU;
Jostick jostick(aX,aY,dC);

void setup() {
  Serial.begin(serial);
  modeMCU.begin(); 
  jostick.begin();
  jostick.setSerial(true);
  Serial.println("Ready");
}

void loop() {
 // Serial.println("Inloop");
  jostick.read();
  String send = "X:"+jostick.getHorizontalValue();
  send += ", Y:"+jostick.getVerticalValue();
  send += ", C:"+jostick.isClicked()?1:0;
  modeMCU.send(send);
  delay(3000);
}
