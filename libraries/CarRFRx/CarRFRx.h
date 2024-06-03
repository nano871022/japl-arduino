#ifndef CarRFRx_h
#define CarRFRx_h

#include <RFRx.h>
#include <Logs.h>
#include <Leds.h>
#include "String.h"

class CarRFRx {
	public:
		CarRFRx(uint8_t portRH,Leds *ledBlue, Logs *logs);
		void readRF();
		int getX();
		int getY();
		void setX(int x);
		void setY(int y);
		uint8_t getLevel();
		bool isActiveMotor();
		void begin(int baund);
		bool isWorking();
		long getTime();
	private:
		RFRx *_rf;
		Leds *_led_blue;
		Logs *_log;
		bool _enable_log = true;
		bool _activeMotor = false;
		uint8_t _level = 0;
		int _x = 0;
		int _y = 0;
		unsigned long _time = 0;
		int getX(String msg);
		int getY(String msg);
		bool getActiveMotor(String msg);
		uint8_t getClick(String msg);
		String get(String msg,uint8_t first, uint8_t second);
		

};

#endif