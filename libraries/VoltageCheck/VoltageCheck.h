/**
** VoltageCheck Header
** Check Voltage Value of pin arduino analog
** Resistencias Used to test is R1 = 33000 and R2 10000
** 245 pwm over 1023 is iqual to 5v, with this we can detected around 20v 
**/
#ifndef VoltageCheck_h
#define VoltageCheck_h

#include "Arduino.h"
#include <Leds.h>
#include <Logs.h>

	class VoltageCheck{
		public:
			VoltageCheck(uint8_t pinRead,Leds *ledRed, Leds *ledBlue, Leds *ledGreen, Logs *log);
			/**
			** config pin and prepared to word
			**/
			void begin();
			/**
			** read value of analog pin to check voltage
			**/
			void read();
			/**
			* allow to set pwm value for 5v
			*/
			void setPwmEq5v(unsigned int pwm = 245);
			/**
			** allow to set warning voltage when led red is on
			** because the value is so low
			**/
			void setVoltageAlert(float warning = 4.0);
			/**
			** allow to set warning voltage when led blue is on
			** because the value is near to change or charge batteries
			**/
			void setVoltageWarning(float alert = 4.0);
			/**
			** allow to set good life voltage batterie when led green is on
			**/
			void setVoltageGood(float good = 4.8);

		private:
			uint8_t _pinRead;
			Leds *_ledRed;
			Leds *_ledBlue; 
			Leds *_ledGreen;
			Logs *_log;
			int _pwm5v;
			bool _enable_log = false;
			float _warning = 4.0;
			float _alert = 4.0;
			float _good = 4.8;
			long _timeRead = 0;
			long _timeLedOn = 0;
			const uint8_t _voltage = 5;
			float calculate(unsigned int pwm);
			void turnOnLed(float voltage);
			void turnOffLeds();
	};

#endif