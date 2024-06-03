/**
** Jostick implementation Jostick,h
** _current* valor interno in pwm value_comp
** return values in percentage
** 0 - 1023
** 0 - 100%
** (_current* X 100) / 1023 
** (700 X 100) / 68
**/
#define clickTimeWait 800
#include "Arduino.h"
#include <Jostick.h>
#include "Math.h"

Jostick::Jostick(uint8_t aPortHorizontal,uint8_t aPortVertical, uint8_t dPortClick, Leds *ledRed, Leds *ledBlue, Leds *ledGreen, Logs *log){
	this->_log = log;
	_aPortHorizontal = aPortHorizontal;
	_aPortVertical   = aPortVertical;
	_dPortClick      = dPortClick; 
	this->_ledRed = ledRed;
	this->_ledBlue = ledBlue;
	this->_ledGreen = ledGreen;
	
}

void Jostick::read(){
	
	int horizontal = analogRead(_aPortHorizontal);
	if(horizontal != _currentHorizontal){
		_currentHorizontal = horizontal;
		if(this->_log->isActive()){
			sprintf(this->_log->msg,"X %04d",this->_currentHorizontal);
			this->_log->log();
		}
	}
	
	
	int vertical = analogRead(_aPortVertical);
	if(vertical != _currentVertical){
		_currentVertical = vertical;
		sprintf(this->_log->msg,"Y %d",this->_currentVertical);
		this->_log->log();
	}
	

	int click = digitalRead(_dPortClick);
	if(click != _currentClick){
		this->_currentClick = click;
		if(this->_log->isActive()){
			sprintf(this->_log->msg,"C %d",_currentClick);
			this->_log->log();
		}
	}
	
	clicks(click == HIGH);
	

}

void Jostick::clicks(bool click){
	if(click){
		this->_ledRed->off();
	}else{
		this->_ledRed->on();
	}
	unsigned long time = millis();

	

	if(!click && this->_clickTime > time){
		if(this->_clicks > 2){
			this->_clicks = 0;
		}else{
			this->_clicks++;
		}
		this->_clickTime = time + clickTimeWait;
	}else if(!click && this->_clickTime < time && !this->_activeCommands){
		this->_clicks = 0;
		this->_clickTime = time + clickTimeWait;
	}
	
	this->clickState();
	this->clickCommands();
}

void Jostick::clickCommands(){
		switch(this->_clicks){
			case 2: 
				this->_motor = !this->_motor;
				this->_ledBlue->unblock();
				this->_ledBlue->off();
				this->_ledGreen->blink(1000);
				this->_clicks = 0;
				this->_activeCommands = false;
				break;
			case 3: 
				if(this->level > 2){
					this->level = 0;
				}else{
					this->level++;
				}
				this->_ledRed->unblock();
				this->_ledRed->off();
				this->_ledGreen->blink(1000);
				this->_clicks = 0;
				this->_activeCommands = false;
				break;
		}
}

void Jostick::clickState(){
   switch(this->_clicks){
   		case 2: 
   			this->_ledBlue->on();
   			this->_ledBlue->block();
   			this->_activeCommands = true;
   			break;
   		case 3: 
   			this->_ledRed->on();
   			this->_ledRed->block();
   			this->_activeCommands = true;
   			break;
   }
}

bool Jostick::isClicked(){
	return _currentClick != HIGH;
}

bool Jostick::activeMotor(){
	return this->_motor;
}

void Jostick::begin(){
	this->_log->log("\nJostick::Begin");
	pinMode(_aPortHorizontal, INPUT);	
	pinMode(_aPortVertical  , INPUT);	
	pinMode(_dPortClick     , INPUT);
	digitalWrite(_dPortClick, HIGH);
	//Serial.println("Setting ports..");

	this->_ledGreen->unblock();
	this->_ledGreen->blink(1000);
	this->_ledBlue->unblock();
	this->_ledBlue->blink(1000);
	this->_ledRed->unblock();
	this->_ledRed->blink(1000);
	this->_log->log("\nJostick::End");
}

void Jostick::setMinPwm(double min){
	_minPwm = min;
}
int Jostick::getHorizontalValue(){
	return calculateValues(this->_currentHorizontal);
}
int Jostick::getVerticalValue(){
	return calculateValues(this->_currentVertical);
}


int Jostick::calculateValues(unsigned int pwm){
	
	int value = pwm;
	switch(this->level ){
		case 1:
			value = this->calculatePow(pwm);
			break;
		case 2:
			value = this->calculateLinear(pwm);
			break;
		case 3:
			value = calculateBig(pwm);
			break;
	}
	if(value < 0){
		value = value * -1;
	}
	return value;
}

int Jostick::calculateBig(unsigned int pwm){
	int out = map(pwm,1,1023,1,1023);
	if(this->_log->isActive()){
		sprintf(this->_log->msg , "\n\rCalcBig:: PWM: %d Out: %d",pwm,out);
		this->_log->log();
	}
	return out;
}

uint8_t Jostick::calculateLinear(unsigned int pwm){
	uint8_t out = map(pwm,1,1023,1,100);
	if(this->_log->isActive()){
		sprintf(this->_log->msg , "\n\rCalcLnr:: PWM: %d Out: %d",pwm,out);
		this->_log->log();
	}
	return out;
}
uint8_t Jostick::calculatePow(unsigned int pwm){
	uint8_t out = pow(((pwm-500)*0.007368),3) + 50;
	if(this->_log->isActive()){
		sprintf(this->_log->msg , "\n\rCalcPOW:: PWM: %d Out: %d",pwm,out);
		this->_log->log();
	}
	return out;
}