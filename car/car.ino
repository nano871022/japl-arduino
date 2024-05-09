#include <Car.h>

uint8_t portRH = 11;

uint8_t aWL = 14;
uint8_t aWR = 15;
uint8_t dFWL = 16;
uint8_t dFWR = 17;
uint8_t dBWL = 18;
uint8_t dBWR = 19;

uint8_t lRed = 7;
uint8_t lBlue = 4;
uint8_t lGreen = 8;


int baud = 9600;

Car car(aWL,dFWL,dBWL,aWR,dFWR,dBWR,portRH,lRed,lBlue,lGreen);

void setup() {
  car.logs(false);
  Serial.begin(baud);
  car.begin(baud);
 }

void loop() {
  car.loop();
}
