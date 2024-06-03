#ifndef Controller_jostick_rf_h
#define Controller_jostick_rf_h

#include <RFTx.h>
#include <Jostick.h>
#include <VoltageCheck.h>
#include <Leds.h>
#include <Logs.h>

class Controller_jostick_rf{
	public:
		Controller_jostick_rf(uint8_t a_x,uint8_t a_y,uint8_t d_click,uint8_t portRH,uint8_t pinRead,uint8_t pinRed, uint8_t pinBlue, uint8_t pinGreen);
		void logs(bool enable);
		void begin(int baud);
		void loop();
	private:
		Logs *_log;
		RFTx *_rfTx;
		Leds *_ledRed;
		Leds *_ledGreen;
		Leds *_ledBlue;
		Jostick *_jostick;
		uint8_t _steps = 0;
		VoltageCheck *_voltageCheck;
		void countSteps();
		void sendRx();

};

#endif