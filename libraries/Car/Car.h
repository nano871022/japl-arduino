/**
**
**/
#ifndef Car_h
#define Car_h

#include "String.h"
#include <RFRx.h>
#include <VoltageCheck.h>
#include <Leds.h>
#include <CarRFRx.h>
#include <Logs.h>
#include <MoveCar.h>


class Car{
	public:
		Car(uint8_t da_Left,uint8_t da_fLeft,uint8_t da_bLeft,uint8_t da_Right, uint8_t da_fRight,uint8_t da_bRight,uint8_t portRH,uint8_t d_l_red,uint8_t d_l_blue,uint8_t d_l_green,uint8_t a_v_read1,uint8_t d_l1_red,uint8_t d_l1_blue,uint8_t d_l1_green,uint8_t a_v_read2,uint8_t d_l2_red,uint8_t d_l2_blue,uint8_t d_l2_green, uint8_t d_l13);
		void begin(int baud);
		void loop();
		void logs(bool enable = false);
	private:
		VoltageCheck* _vCheck1;
		VoltageCheck* _vCheck2; 

		uint8_t _step = 0;
		
		Leds *_led_red;
		Leds *_led_blue;
		Leds *_led_green;
		Leds *_led1_red;
		Leds *_led1_blue;
		Leds *_led1_green;
		Leds *_led2_red;
		Leds *_led2_blue;
		Leds *_led2_green;
		Leds *_led13;

		Logs *_log;
		CarRFRx *_rf;
		MoveCar *_move;
		bool _enable_log = false;

		bool isUp(uint8_t value);
		void ledsLow();
		void ledOn(Leds *led,bool on);
		void voltageCheck();
		void defaultOption();
		void stepsCount();
};

#endif