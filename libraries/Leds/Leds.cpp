#include <Leds.h>

Leds::Leds(uint8_t pin){
	this->_pin = pin;
}
void Leds::begin(){
	pinMode(this->_pin, OUTPUT);	
}
void Leds::on(){
	if(!this->isBlock()){
		digitalWrite(this->_pin,HIGH);
	}
}
void Leds::off(){
	if(!this->isBlock()){
		digitalWrite(this->_pin,LOW);
	}
}
void Leds::blink(int timeBlink){
	if(!this->isBlock()){
		this->block();
		digitalWrite(this->_pin,LOW);
		digitalWrite(this->_pin,HIGH);
		delay(timeBlink);
		digitalWrite(this->_pin,LOW);
		this->unblock();
	}
}
void Leds::blinks(uint8_t times,int timeBlink){
	if(times <= 1 || timeBlink <= 1){
		return;
	}
	if(!this->isBlock()){
		this->block();
		for(uint8_t i = 0; i < times; i++){
			digitalWrite(this->_pin,LOW);
			digitalWrite(this->_pin,HIGH);
			delay(timeBlink);
			digitalWrite(this->_pin,LOW);
			if(i < times-1){
				delay(timeBlink);
			}
		}
		this->unblock();
	}
}
void Leds::block(){
	if(!this->isBlock()){
		this->bblock = true;
	}
}
void Leds::unblock(){
	if(this->isBlock()){
		this->bblock = false;
	}
}
bool Leds::isBlock(){
	return this->bblock;
}