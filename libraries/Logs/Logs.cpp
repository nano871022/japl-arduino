#include <Logs.h>
#include <Arduino.h>

void Logs::log(char *msg){
	if(this->_enable){
		Serial.print(msg);
	}
}

void Logs::log(){
	this->log(this->msg);
}

void Logs::setActive(bool active){
	this->_enable = active;
}

bool Logs::isActive(){
	return this->_enable;
}