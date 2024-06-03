#ifndef MoveCar_h
#define MoveCar_h

#include <CalculateInitMotor.h>
#include <CarRFRx.h>
#include <Logs.h>
#include <Leds.h>
#include <MotorPwmOut.h>

class MoveCar{
	private:
		uint8_t _minPowerMotor = 120;
		MotorPwmOut* motorLeft;
		MotorPwmOut* motorRight;
		CalculateInitMotor *_calc;
		Logs *_log;
		CarRFRx *_rf;
		uint8_t _d_f_Left;
		uint8_t _d_f_Right;
		uint8_t _d_b_Left;
		uint8_t _d_b_Right;

		bool _enable_log = true;

		Leds *_led1_red;
		Leds *_led1_blue;
		Leds *_led1_green;
		Leds *_led2_red;
		Leds *_led2_blue;
		Leds *_led2_green;
		Leds *_led_red;

		void forward();
		void backward();
		void moveMotor();
		void move(int x, int y);
		bool isUp(int value);
		void moveForward(int x, int y, uint8_t mx , uint8_t my);
		void moveBackward(int x, int y, uint8_t mx , uint8_t my);
		void moveLeft(int x, int y, uint8_t mx , uint8_t my);
		void moveRight(int x, int y, uint8_t mx , uint8_t my);
		void moveLeftForward(int x, int y, uint8_t mx , uint8_t my);
		void moveLeftBackward(int x, int y, uint8_t mx , uint8_t my);
		void moveRightForward(int x, int y, uint8_t mx , uint8_t my);
		void moveRightBackward(int x, int y, uint8_t mx , uint8_t my);
	public: 
		MoveCar(uint8_t da_left, uint8_t da_Right, uint8_t da_fLeft, uint8_t da_fRight, uint8_t da_bLeft, uint8_t da_bRight, Logs *log, CarRFRx *rf,Leds *ledRed,Leds *led1Red,Leds *led1Blue,Leds *led1Green,Leds *led2Red,Leds *led2Blue,Leds *led2Green);
		void stop();
		void motor();
		void begin();

};

#endif