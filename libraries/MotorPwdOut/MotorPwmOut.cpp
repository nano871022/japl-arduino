/**
** MotorPwdOut implementation 
**/
#include "Arduino.h"
#include <MotorPwmOut.h>



MotorPwmOut::MotorPwmOut(uint8_t aPort){
	_aPort = aPort;
	
}

void MotorPwmOut::begin(){
	pinMode(_aPort, OUTPUT);
	this->log((char)_aPort);
}

void MotorPwmOut::setMinPower(uint8_t minPowerPwm){
		_minPowerPwm = minPowerPwm;
}
/**
** 0v - 5v
** 0  - 254
** 254 - 5v
** 125 - ?
** 125 * 5 / 254 = 2.45v
**/
double MotorPwmOut::power(){
	double first = (_currentPower * _maxVoltage);
    return first / _maxPowerPwm;
}

void MotorPwmOut::setMaxVoltage(float maxVoltage){
	_maxVoltage = maxVoltage;
}
/**
** Range     : 0 - 254
** Percentage: 0 - 100
** 100 - 254
**  50 -  ?
** Ex::
** Power     : (((254 - 0) / (100 - 0)) X Value) + 105 = 127 PWD
**/
void MotorPwmOut::move(uint8_t power){

	if(power > 0 && power < 100){
		double first = _maxPowerPwm - _minPowerPwm;
		double second = first / 100;
		double third = second * power;
		double four = third + _minPowerPwm;
		_currentPower = four;
	}else if(power >= 100){
		_currentPower = _maxPowerPwm;
	}else {
		_currentPower = _minPowerPwm;
	}

		this->log("P: ");
		this->log(_maxPowerPwm - _minPowerPwm);
		this->log(" / ");
		this->log(" 100 X ");
		this->log(power);
		this->log(" + ");
		this->log(_minPowerPwm);
		this->log(" = ");
		this->log(_currentPower);
		this->log("\n");

	if(power == 0){
		stop();
	}else{
		analogWrite(_aPort,_currentPower);
	}
	
}

void MotorPwmOut::stop(){
	_currentPower = _minPowerPwm;
	analogWrite(_aPort,0);
}
void MotorPwmOut::setSerial(bool isActive){
	_enableLog = isActive;
}

void MotorPwmOut::log(char *msg){
	if(_enableLog){
		Serial.print(msg);
	}
}