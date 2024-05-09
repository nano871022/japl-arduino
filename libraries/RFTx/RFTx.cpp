#include <RFTx.h>

RFTx::RFTx(uint8_t portRH){
	_askTx = new RH_ASK (2000, 11,portRH, 10, false);
}

void RFTx::begin(int baud){
	_askTx->init();
	Serial.println("End Begin RFTx");
}

void RFTx::inLoop(char* data){
	Serial.print(".");
	_askTx->send((uint8_t *)data,strlen(data));
	_askTx->waitPacketSent();
	delay(10);
}