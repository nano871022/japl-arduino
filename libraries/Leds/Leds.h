/**
** class to manage a led and others clases can use this class to use the leds but it allowed to main class
**/
#ifndef Leds_h
#define Leds_h

#include "Arduino.h"

class Leds{
	private:
		uint8_t _pin;
		bool bblock = false;
	public:
	    Leds(uint8_t pin);
		void begin();
		void on();
		void off();
		void blink(int timeBlink);
		void blinks(uint8_t times,int timeBlink);
		void block();
		void unblock();
		bool isBlock();
};

#endif