#ifndef RFRx_h
#define RFRx_h
#include "Arduino.h"
#include <RH_ASK.h>
#include <SPI.h>
#include "SoftwareSerial.h"
#include <Logs.h>

class RFRx{
	public:
		RFRx(uint8_t portRH, Logs *log);
		void begin(int baud);
		char* inLoop();
		bool isWorking();
	private:
		long lastConnect = 0;
		RH_ASK _askRx;
		bool _enable = false;
		Logs *_log;
};

#endif