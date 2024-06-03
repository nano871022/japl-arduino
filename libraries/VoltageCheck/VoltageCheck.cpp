#include <VoltageCheck.h>


#define time_check 30000
#define time_led_on 3000

VoltageCheck::VoltageCheck(uint8_t pinRead,Leds *ledRed, Leds *ledBlue, Leds *ledGreen, Logs *log){
	this->_log = log;
	this->_pinRead = pinRead;
	this->_ledRed = ledRed;
	this->_ledBlue = ledBlue; 
	this->_ledGreen = ledGreen;
	this->setPwmEq5v();
	this->setVoltageAlert();
	this->setVoltageWarning();
	this->setVoltageGood();
}

void VoltageCheck::begin(){
	if(this->_pinRead > 0){
		pinMode(this->_pinRead,INPUT);
	}else{
		this->_log->log("ERR: Pin Read is not set\n\r");
	}	
}

void VoltageCheck::read(){
	if(this->_timeRead < millis()){
		unsigned int pwm = analogRead(this->_pinRead);
		float value = calculate(pwm);
		if(this->_enable_log && this->_log->isActive()){
			sprintf(this->_log->msg,"\n\rINF: pwm: %04d voltate: %d v.  5v = %d\n\r",pwm,(uint8_t)value,this->_pwm5v);
			this->_log->log();
		}
		turnOnLed(value);
		this->_timeLedOn = millis() + time_led_on;
		this->_timeRead = millis() + time_check;
		
	}else if(this->_timeLedOn == 0 || this->_timeLedOn < millis()){
		if(this->_enable_log && this->_log->isActive()){
			this->_log->log("TurnOff leds");
		}
		this->turnOffLeds();
		this->_timeLedOn = 0;
	}
	if(this->_enable_log && this->_log->isActive()){
		this->_log->log("\n\r leds check ");
		this->_log->log(this->_timeLedOn > 0?" AVAILABLE ": " DISABLED ");
		this->_log->log(this->_timeLedOn < millis() ? " WAITING ": "TURNOFF");
		this->_log->log("\n\r");
	}
}

void VoltageCheck::turnOnLed(float voltage){
	this->turnOffLeds();
	if(voltage/10 > this->_good && !this->_ledGreen->isBlock()){
		this->_ledGreen->on();
	}else if(voltage/10 >= this->_warning && !this->_ledBlue->isBlock()){
		this->_ledBlue->on();
	}else if(voltage/10 < this->_alert && !this->_ledRed->isBlock()){
		this->_ledRed->on();
	}else{
		this->_log->log("WRN: It doesn't turn on any led.\n\r");
	}
}

void VoltageCheck::turnOffLeds(){
	if(!this->_ledGreen->isBlock()){
		this->_ledGreen->off();
	}
	if(!this->_ledBlue->isBlock()){
		this->_ledBlue->off();
	}
	if(!this->_ledRed->isBlock()){
		this->_ledRed->off();
	}
}

float VoltageCheck::calculate(unsigned int pwm){
	float value = (((float)pwm * (float)this->_voltage) / (float)this->_pwm5v)*10.0;
	return value;
}

void VoltageCheck::setPwmEq5v(unsigned int pwm = 245){
	this->_pwm5v = pwm;
}
			
void VoltageCheck::setVoltageAlert(float warning = 4.0){
	this->_warning = warning;
}
			
void VoltageCheck::setVoltageWarning(float alert = 4.0){
	this->_alert = alert;
}
			
void VoltageCheck::setVoltageGood(float good = 4.8){
	this->_good = good;
}