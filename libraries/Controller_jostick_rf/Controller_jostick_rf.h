#ifndef Controller_jostick_rf_h
#define Controller_jostick_rf_h

#include <RFTx.h>
#include <Jostick.h>

class Controller_jostick_rf{
	public:
		Controller_jostick_rf(uint8_t a_x,uint8_t a_y,uint8_t d_click,uint8_t portRH);
		void logs(bool enable);
		void begin(int baud);
		void loop();
	private:
		bool _enableLog = false;
		RFTx *_rfTx;
		Jostick *_jostick;
		void log(char *msg);
	
	
};

#endif