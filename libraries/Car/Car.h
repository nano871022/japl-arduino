/**
**
**/
#ifndef Car_h
#define Car_h

#include "String.h"
#include <MotorPwmOut.h>
#include <RFRx.h>

class Car{
	public:
		Car(uint8_t da_Left,uint8_t da_fLeft,uint8_t da_bLeft,uint8_t da_Right, uint8_t da_fRight,uint8_t da_bRight,uint8_t portRH,uint8_t d_l_red,uint8_t d_l_blue,uint8_t d_l_green);
		void begin(int baud);
		void move(float x, float y);
		void stop();
		void loop();
		void logs(bool enable = false);
	private:
		RFRx *rfRx;
		bool _enableLog = false;
		MotorPwmOut* motorLeft;
		MotorPwmOut* motorRight;
		uint8_t _d_f_Left;
		uint8_t _d_f_Right;
		uint8_t _d_b_Left;
		uint8_t _d_b_Right;
		uint8_t _d_l_red;
		uint8_t _d_l_blue;
		uint8_t _d_l_green;
		uint8_t _x = 0;
		uint8_t _y = 0;
		bool isUp(float value);
		
		float getValue(float value);
		float moveX(float x);
		float moveY(float y);
		uint8_t getPlusValues(float a, float b);
		uint8_t getMinusValues(float a, float b);
		uint8_t minPowerMotor = 85;
		void forward();
		void backward();
		void log(char* msg);
		
		void ledsLow();
		uint8_t getX(String msg);
		uint8_t getY(String msg);
		String get(String msg,uint8_t first, uint8_t second);
};

#endif