/**
**/
#define pinPortInAX A0
#define pinPortInAY A1
#define pinPortInDC 8
#define pinPortInDE 7
#define pinPortA 9
#define serial 4800

#include <SoftwareSerial.h>
#include <Wifi.h>
//#include <MotorPwmOut.h>
//#include <Jostick.h>


SoftwareSerial ss(0,1);
/*Jostick jostick(pinPortInAX,pinPortInAY,pinPortInDC);
MotorPwmOut motor(pinPortA);
Wifi wifi(0,1);
*/
void setup() {
 // pinMode(pinPortInDE,OUTPUT);
 // digitalWrite(pinPortInDE,HIGH);
  Serial.begin(serial); 
  ss.begin(serial);
  delay(1000);
  ss.write("AT+CWJAP=\"");
  ss.write("Lore-Alejo");
  ss.write("\",\"");
  ss.write("AL3j0_L0r30228_2016");
  ss.write("\"\r\n");

  delay(4000);

  ss.write("AT+CIPMUX=1\r\n");

  delay(2000);

  ss.write("AT+CIPSERVER=1, 80\r\n");

  delay(2000);

  ss.write(acknowledge);
  /*
  jostick.begin();
  jostick.setSerial(false);
  motor.begin();
  motor.setMinPower(75);
  motor.setMaxVoltage(5.0);
  motor.setSerial(false);
  */
}

// the loop function runs over and over again forever
void loop() {
  //ss.write(acknowledge);
  if(ss.available()){
    Serial.print((char)ss.read());
  }
/* jostick.read();
 
 if(jostick.isClicked()){
  motor.move(0);
 }else{
  motor.move(jostick.getVerticalValue());
 }
 */
 //Serial.print(motor.power());
 if(Serial.available()){
  Serial.print((char)Serial.read());
 }
}
