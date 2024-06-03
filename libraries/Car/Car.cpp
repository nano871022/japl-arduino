/**
**
**/
#include "Car.h"
#include "Arduino.h"



Car::Car(uint8_t da_Left,uint8_t da_fLeft,uint8_t da_bLeft,uint8_t da_Right, uint8_t da_fRight,uint8_t da_bRight,uint8_t portRH,uint8_t d_l_red,uint8_t d_l_blue,uint8_t d_l_green,uint8_t a_v_read1,uint8_t d_l1_red,uint8_t d_l1_blue,uint8_t d_l1_green,uint8_t a_v_read2,uint8_t d_l2_red,uint8_t d_l2_blue,uint8_t d_l2_green,uint8_t led13){
	this->_log = new Logs();
	
	this->_led_red = new Leds(d_l_red);
	this->_led_blue = new Leds(d_l_blue);
	this->_led_green = new Leds(d_l_green);

	this->_rf = new CarRFRx(portRH,this->_led_blue,this->_log);

	this->_led1_red = new Leds(d_l1_red);
	this->_led1_blue = new Leds(d_l1_blue);
	this->_led1_green = new Leds(d_l1_green);

	this->_led2_red = new Leds(d_l2_red);
	this->_led2_blue = new Leds(d_l2_blue);
	this->_led2_green = new Leds(d_l2_green);

	this->_led13 = new Leds(led13);

	this->_move = new MoveCar(da_Left,da_Right, da_fLeft,  da_fRight, da_bLeft, da_bRight, this->_log, this->_rf,this->_led_red,this->_led1_red,this->_led1_blue,this->_led1_green,this->_led2_red,this->_led2_blue,this->_led2_green);

	this->_vCheck1 = new VoltageCheck(a_v_read1,_led1_red,_led1_blue,_led1_green,this->_log);
	this->_vCheck1->setPwmEq5v(245);
	this->_vCheck1->setVoltageGood(7.2);
	this->_vCheck1->setVoltageWarning(6.8);
	this->_vCheck1->setVoltageAlert(6.6);
	this->_vCheck2 = new VoltageCheck(a_v_read2,_led2_red,_led2_blue,_led2_green,this->_log);
	this->_vCheck2->setPwmEq5v(245);
	this->_vCheck2->setVoltageGood(3.7);
	this->_vCheck2->setVoltageWarning(3.5);
	this->_vCheck2->setVoltageAlert(3.3);

}

void Car::begin(int baud){
	this->_rf->begin(baud);
	this->_move->begin();
	this->_vCheck1->begin();
	this->_vCheck2->begin();

	this->_led_green->begin();
	this->_led_blue->begin();
	this->_led_red->begin();
	this->_led1_green->begin();
	this->_led1_blue->begin();
	this->_led1_red->begin();
	this->_led2_green->begin();
	this->_led2_blue->begin();
	this->_led2_red->begin();
	this->_led13->begin();
	
	this->_led1_red->blink(1000);
	this->_led2_blue->blink(1000);
	this->_led_green->blink(1000);
}


void Car::ledsLow(){
  this->ledOn(this->_led_red,false);
}

void Car::loop(){
	
	switch(this->_step){
		case 0:
			this->ledsLow();
			break;
		case 1:
			this->_rf->readRF(); 	
			break;
		case 2:
			this->_move->motor();		
			break;
		case 3:
			this->voltageCheck();
			break;
		default: 
			this->defaultOption();			
			break;
	}
	this->stepsCount();
}

void Car::stepsCount(){
	if(this->_step < 3){
		this->_step++;
	}else{
		this->_step = 0;
	}
	if(this->_enable_log && this->_log->isActive()){
		sprintf(this->_log->msg,"\nCar::INF:Step: %d ",this->_step);
		this->_log->log();
	}
}

void Car::defaultOption(){
	this->ledOn(this->_led_red, true);	
	this->_move->stop();
}

void Car::voltageCheck(){
	this->_vCheck1->read();
	this->_vCheck2->read();
}

void Car::logs(bool enable = false){
	this->_log->setActive(enable);
}

void Car::ledOn(Leds *led,bool on){
	this->_led_green->off();
	this->_led_blue->off();
	this->_led_red->off();
	if(on){
		led->on();
	}else{
		led->off();
	}
}