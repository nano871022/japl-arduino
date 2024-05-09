#define pinLedBoard 2
#include <SoftwareSerial.h>
const int delayTimeMls = 1000;

 void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinLedBoard,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinLedBoard,HIGH);
  delay(delayTimeMls);
  digitalWrite(pinLedBoard,LOW);
  Serial.println("I Live");
}
