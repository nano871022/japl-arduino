#include <RFTx.h>

RFTx::RFTx(uint8_t portRH, Logs *log){
	_askTx = new RH_ASK (2000, 11,portRH, 10, false);
	this->_log = log;
}

void RFTx::begin(int baud){
	_askTx->init();
	this->_log->log("End Begin RFTx");
}

void RFTx::inLoop(char* data){
	if(strlen(data) > 0){
		this->_log->log(".");
		bool sent = _askTx->send((uint8_t *)data,strlen(data));
		if(this->_log->isActive()){
			this->_log->log("\n\rRFTx::INF:Msg in buffer?");
			this->_log->log(sent?" TRUE ":" FALSE ");
			this->_log->log("\n\r");
		}
		sent = _askTx->waitPacketSent();
		if(this->_log->isActive()){
			this->_log->log("\n\rRFTx::INF:Msg sent?");
			this->_log->log(sent?" TRUE ":" FALSE ");
			this->_log->log("\n\r");
		}
	}else{
		this->_log->log("\n\rRFTx::ERR:Value MSG to send is empty.\n\r");
	}
}
