/**
** Jostick implementation Jostick,h
** _current* valor interno in pwm value_comp
** return values in percentage
** 0 - 1023
** 0 - 100%
** (_current* X 100) / 1023 
** (700 X 100) / 68
**/
#include "Arduino.h"
#include <Jostick.h>

Jostick::Jostick(uint8_t aPortHorizontal,uint8_t aPortVertical, uint8_t dPortClick){
	_aPortHorizontal = aPortHorizontal;
	_aPortVertical   = aPortVertical;
	_dPortClick      = dPortClick; 
}

void Jostick::read(){
	int horizontal = analogRead(_aPortHorizontal);
	if(horizontal != _currentHorizontal){
		_currentHorizontal = horizontal;
		log("X: ");
		log(_currentHorizontal);
	}
	int vertical = analogRead(_aPortVertical);
	if(vertical != _currentVertical){
		_currentVertical = vertical;
		log(" Y: ");
		log(_currentVertical);
	}
	int click = digitalRead(_dPortClick);
	if(click != _currentClick){
		_currentClick = click;
		log(" C: ");
		log(_currentClick);
	}

	
	
}

bool Jostick::isClicked(){
	return _currentClick != HIGH;
}

void Jostick::begin(){
	//Serial.println("Start Setting ports");
	pinMode(_aPortHorizontal, INPUT);	
	pinMode(_aPortVertical  , INPUT);	
	pinMode(_dPortClick     , INPUT);
	digitalWrite(_dPortClick, HIGH);
	//Serial.println("Setting ports..");
}

void Jostick::setMinPwm(double min){
	_minPwm = min;
}
int Jostick::getHorizontalValue(){
	double value = (_currentHorizontal * 100.0) / _maxPwm;
	return value;
}
int Jostick::getVerticalValue(){
	double value = (_currentVertical * 100.0) / _maxPwm;
	return value;
}
void Jostick::setSerial(bool isActive){
	_isSerial = isActive;
}
void Jostick::log(char* msg){
	if(_isSerial){
		Serial.print(msg);
	}
}