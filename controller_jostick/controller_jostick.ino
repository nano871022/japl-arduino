/**
** controller RF Jostic
**/

#include <Controller_jostick_rf.h>
#define baud 9600

uint8_t portRH = 12;
uint8_t aVert = A0;
uint8_t aHorz = A1;
uint8_t click = 8;

Controller_jostick_rf controller(aHorz,aVert,click,portRH);

void setup() {
  Serial.begin(baud);

  controller.logs(false);
  controller.begin(baud);
}

void loop() {
 controller.loop();
}
