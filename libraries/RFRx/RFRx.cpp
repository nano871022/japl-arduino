#include <RFRx.h>
#include "String.h"


RFRx::RFRx(uint8_t portRH,Logs *log){
	this->_log = log;
}

void RFRx::begin(int baud){
	_askRx.init();
	this->_log->log("End RFRx");
}

char* RFRx::inLoop(){
	uint8_t length=14;
	uint8_t msg[length];
	uint8_t msgLen = sizeof(msg);
	bool recv  = _askRx.recv(msg, &msgLen);
	if(recv){
		lastConnect = millis() + 2000;
		char* output;
		output = (char*)msg;
		if(this->_enable && this->_log->isActive()){
			this->_log->log("RFRx::INF: ");
			this->_log->log(output);
			this->_log->log("\n");
		}
		return output;
	}else if(this->_enable && this->_log->isActive()){
		this->_log->log("\n\rRFRx::ERR: No messge receive.");
		this->_log->log(recv?"TRUE ":"FALSE /");
		this->_log->log((char*)msg);
		this->_log->log("/\n\r");
	}
	if(lastConnect < millis() && this->_log->isActive()){
		this->_log->log(".");
	}
	return "";
}

bool RFRx::isWorking(){
	if(this->_enable && this->_log->isActive()){
		this->_log->log("\n\rRFRx::WRN:Working ");
		this->_log->log(lastConnect > millis()?"TRUE":"FALSE");
		this->_log->log("\n\r");
	}
	return lastConnect > millis();
}
