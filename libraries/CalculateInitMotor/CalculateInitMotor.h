#ifndef CalculateInitMotor_h
#define CalculateInitMotor_h

#include <Arduino.h>
#include <Logs.h>

class CalculateInitMotor{
	private:
		Logs *_log;
		bool _enable = false;
		uint8_t getValue(int value);
	public:
		CalculateInitMotor(Logs *log);
		uint8_t getPlusValues(uint8_t a, uint8_t b);
		uint8_t getMinusValues(uint8_t a, uint8_t b);
		uint8_t moveX(int x);
		uint8_t moveY(int y);
};

#endif