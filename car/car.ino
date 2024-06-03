#include <Car.h>

uint8_t portRH = 11;

uint8_t aWL = 6;
uint8_t aWR = 5;

uint8_t dFWL = 7;
uint8_t dFWR = 3;
uint8_t dBWL = 8;
uint8_t dBWR = 4;

uint8_t l1Red = 2;
uint8_t l1Blue = 10;
uint8_t l1Green = 9;

uint8_t l2Red = A3;
uint8_t l2Blue = A5;
uint8_t l2Green = A4;

uint8_t l3Red = A0;
uint8_t l3Blue = A2;
uint8_t l3Green = A1;

uint8_t l13 = 13;

uint8_t vRead1 = A6;
uint8_t vRead2 = A7;

int baud = 9600;

Car car(aWL,dFWL,dBWL,aWR,dFWR,dBWR,portRH,l1Red,l1Blue,l1Green,vRead1,l2Red,l2Blue,l2Green,vRead2,l3Red,l3Blue,l3Green,l13);

void setup() {
  car.logs(false);
  Serial.begin(baud);
  car.begin(baud);
 }

void loop() {
  car.loop();
  
}
