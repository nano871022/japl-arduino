/**
** MotorPwdOut.h manage per percentage motor power to simplify it
** since April 21 2024 by Alejandro Parra
**/
#include "Arduino.h"

class MotorPwmOut{
	public:
		MotorPwmOut(uint8_t aPort);
		void begin();
		void setMinPower(uint8_t minPowerPwm);
		void setMaxVoltage(float maxVoltage);
		void setSerial(bool isActive);
		void move(uint8_t power);
		void stop();
		double power();
	private:
		bool _enableLog = false;
	    uint8_t _aPort;
		uint8_t _minPowerPwm = 0;
		const uint8_t _maxPowerPwm = 254;
		uint8_t _currentPower;
		float _maxVoltage = 5.0;
		void log(char *msg);
};