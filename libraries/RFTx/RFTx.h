#ifndef RFTx_h
#define RFTx_h

#include "Arduino.h"
#include <RH_ASK.h>
#include <SPI.h>

class RFTx{
	public:
		RFTx(uint8_t portRH);
		void begin(int baud);
		void inLoop(char* data);
	private:
		RH_ASK* _askTx;
};

#endif