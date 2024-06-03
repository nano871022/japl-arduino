#ifndef RFTx_h
#define RFTx_h

#include "Arduino.h"
#include <RH_ASK.h>
#include <SPI.h>
#include <Logs.h>

class RFTx{
	public:
		RFTx(uint8_t portRH, Logs *log);
		void begin(int baud);
		void inLoop(char* data);
	private:
		RH_ASK* _askTx;
		Logs *_log;
};

#endif