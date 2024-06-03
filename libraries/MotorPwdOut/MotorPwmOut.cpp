/**
** MotorPwdOut implementation 
**/
#include "Arduino.h"
#include <MotorPwmOut.h>
#include "Math.h"



MotorPwmOut::MotorPwmOut(uint8_t aPort, Logs *log){
	_aPort = aPort;
	this->_log = log;
	
}

void MotorPwmOut::begin(){
	pinMode(_aPort, OUTPUT);
	this->_log->log((char)_aPort);
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
	float multiply = 1.0;
if(this->_state){
	if(power >= 0 && power <= 100){
		_currentPower = calcLineal2(power);
		switch(this->_level){
			case 0: multiply = 0.5;break;
			case 1: multiply = 0.6;break;
			case 2: multiply = 0.7;break;
			case 3: multiply = 0.8;break;
			case 4: multiply = 0.9;break;
		}
		
	}else if(power > 100){
		_currentPower = _maxPowerPwm;
	}else if(power < 0){
		_currentPower = _minPowerPwm;
	}

	//_currentPower = _currentPower * multiply;


	if(power == 0){
		stop();
	}else{
		sprintf(this->_log->msg,"Motor::INF: Origin: %d Power: %d Multiply %d \n\r",power,_currentPower, multiply*10);
		this->_log->log();
		analogWrite(_aPort,_currentPower);
	}
}
}

void MotorPwmOut::stop(){
	if(this->_state){
		_currentPower = _minPowerPwm;
		analogWrite(_aPort,0);
	}
}


void MotorPwmOut::setLevel(uint8_t level){
	this->_level = level;
}

uint8_t MotorPwmOut::calcLineal(uint8_t power){
	return map(power,0,100,80,254);	
}
uint8_t MotorPwmOut::calcLineal2(uint8_t power){
	return (252 / 99) * (power-1); 
}
uint8_t MotorPwmOut::calcLowPowL1(uint8_t power){
	return (pow(power ,2.5) * 0.00099) + 85;
}
uint8_t MotorPwmOut::calcLowPowL2(uint8_t power){
	return (pow(power , 3.5) * 0.0000099) + 85;	
}
uint8_t MotorPwmOut::calcLowPowL3(uint8_t power){
	return (pow(power , 4.5) * 0.000000099) + 85;
}
uint8_t MotorPwmOut::calcLowPowH1(uint8_t power){
	return (log10(power) * 1.1158 * 25) + 85;
}
void MotorPwmOut::on(){
	this->_state = true;
}
void MotorPwmOut::off(){
	this->_state = false;
}