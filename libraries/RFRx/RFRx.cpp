#include <RFRx.h>
#include "String.h"


RFRx::RFRx(uint8_t portRH){

}

void RFRx::begin(int baud){
	_askRx.init();
	Serial.println("End RFRx");
}

char* RFRx::inLoop(){
	uint8_t length=12;
	uint8_t msg[length];
	uint8_t msgLen = sizeof(msg);
	
	if(_askRx.recv(msg, &msgLen)){
		lastConnect = millis() + 3000;
		char* output;
		output = (char*)msg;
		this->log(output);
		this->log("\n");
		return output;
	}
	this->log(".");
	delay(10);
	return "";
}

bool RFRx::isWorking(){
	return lastConnect < millis();
}

void RFRx::logs(bool active){
	this->_enableLog = active;
}
void RFRx::log(char *msg){
	if(this->_enableLog){
		Serial.print(msg);
	}
}