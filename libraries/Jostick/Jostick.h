/**
** Jostick.h Manage jostick in percentage values
**/
#include "Arduino.h"
#include <Leds.h>
#include <Logs.h>

class Jostick{
	public: 
	    Jostick(uint8_t aPortHorizontal,uint8_t aPortVertical, uint8_t dPortClick, Leds *ledRed, Leds *ledBlue, Leds *ledGreen,Logs *log);
		void begin();
		void setMinPwm(double min);
		void setSerial(bool isActive);
		void read();
		int getHorizontalValue();
		int getVerticalValue();
		bool isClicked();
		bool activeMotor();
		
	private:
		Leds *_ledGreen;
		Leds *_ledBlue;
		Leds *_ledRed;
		Logs *_log;
		int _currentHorizontal = 0;
		int _currentVertical = 0;
		int _currentClick = LOW;
		uint8_t level = 3;
		uint8_t _aPortHorizontal;
		uint8_t _aPortVertical;
		uint8_t _dPortClick;
		const double _maxPwm = 1025.0;
		double _minPwm = 0.0;
		bool _activeCommands = false;
		bool _motor = false;
		long _clickTime = 0;
		uint8_t _clicks = 0;
		uint8_t calculateLinear(unsigned int pwm);
		uint8_t calculatePow(unsigned int pwm);
		void clicks(bool click);
		void clickCommands();
		void clickState();
		int calculateValues(unsigned int pwm);
		int calculateBig(unsigned int pwm);
};