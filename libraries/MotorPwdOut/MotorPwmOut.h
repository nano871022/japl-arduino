/**
** MotorPwdOut.h manage per percentage motor power to simplify it
** since April 21 2024 by Alejandro Parra
**/
#include "Arduino.h"
#include <Logs.h>

class MotorPwmOut{
	public:
		MotorPwmOut(uint8_t aPort, Logs *log);
		void begin();
		void setMinPower(uint8_t minPowerPwm);
		void setMaxVoltage(float maxVoltage);
		void setLevel(uint8_t level);
		void move(uint8_t power);
		void stop();
		double power();
		void on();
		void off();
	private:
		Logs *_log;
		bool _state = false;
	    uint8_t _aPort;
		uint8_t _minPowerPwm = 0;
		const uint8_t _maxPowerPwm = 225;
		uint8_t _currentPower;
		float _maxVoltage = 5.0;
		uint8_t _level = 0;
		uint8_t calcLineal(uint8_t power);
		uint8_t calcLineal2(uint8_t power);
		uint8_t calcLowPowL1(uint8_t power);
		uint8_t calcLowPowL2(uint8_t power);
		uint8_t calcLowPowL3(uint8_t power);
		uint8_t calcLowPowH1(uint8_t power);
};