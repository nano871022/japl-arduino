/**
** controller RF Jostic
**/

#include <Controller_jostick_rf.h>
#define baud 9600

uint8_t portRH = 12;
uint8_t aVert = A7;
uint8_t aHorz = A5;
uint8_t click = A4;

uint8_t a_read = A6;
uint8_t d_red = 11;
uint8_t d_green = 9;
uint8_t d_blue = 8;


Controller_jostick_rf controller(aHorz,aVert,click,portRH,a_read,d_red,d_blue,d_green);

void setup() {
  Serial.begin(baud);
  controller.logs(false);
  controller.begin(baud);
}

void loop() {
 controller.loop();
}
