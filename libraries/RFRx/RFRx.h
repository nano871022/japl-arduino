#ifndef RFRx_h
#define RFRx_h
#include "Arduino.h"
#include <RH_ASK.h>
#include <SPI.h>
#include "SoftwareSerial.h"

class RFRx{
	public:
		RFRx(uint8_t portRH);
		void begin(int baud);
		char* inLoop();
		bool isWorking();
		void logs(bool active);
	private:
		bool _enableLog = false;
		long lastConnect = 0;
		RH_ASK _askRx;
		void log(char *msg);
	
};

#endif