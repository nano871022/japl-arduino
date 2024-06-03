#include <CarRFRx.h>

CarRFRx::CarRFRx(uint8_t portRH,Leds *ledBlue, Logs *logs){
	this->_log = logs;
	this->_rf = new RFRx(portRH,this->_log);
	this->_led_blue = ledBlue;
}

void CarRFRx::begin(int baund){
	this->_rf->begin(baund);

}
void CarRFRx::readRF(){
	char* response = this->_rf->inLoop();
	if( strlen(response)>0){
		if(!this->_led_blue->isBlock()){
    		this->_led_blue->on();
    	}
    	this->_time = millis() + 5000;
    	String value = String(response);
    	this->_x = this->getX(value);
    	this->_y = this->getY(value);
    	if(this->_enable_log && this->_log->isActive()){
    		sprintf(this->_log->msg,"\nREADRF:: X %04d Y %04d \n",this->_x,this->_y);
    		this->_log->log();
    	}
    	if(this->getClick(value) == 1){
    		if(this->_level+1 < 5){
    			this->_level++;
    		}else{
    			this->_level = 0;
    		}
    	}
    	this->_activeMotor = getActiveMotor(value);
    	
    	
    	if(!this->_led_blue->isBlock()){
    		this->_led_blue->on();
    	}
  	}
}

int CarRFRx::getX(String msg){
  String value = get(msg,1,5);
  int out= value.toInt();
  if(this->_enable_log && this->_log->isActive()){
   		this->_log->log("\nX ");
		this->_log->log(value.c_str());
		sprintf(this->_log->msg," O: %04d",out);
		this->_log->log();
	}
	return out;
}

int CarRFRx::getY(String msg){
  String value = get(msg,6,10);
   int out = value.toInt();
   if(this->_enable_log && this->_log->isActive()){
   		this->_log->log("\nY ");
		this->_log->log(value.c_str());
		sprintf(this->_log->msg," O: %04d",out);
		this->_log->log();
	}
  return out; 
}

bool CarRFRx::getActiveMotor(String msg){
	String value = get(msg,13,14);
	
   	return value.toInt() == 1;	
}

uint8_t CarRFRx::getClick(String msg){
	String value = get(msg,11,12);
	
   	return value.toInt();	
}

String CarRFRx::get(String msg,uint8_t first, uint8_t second){
  String value = msg.substring(first,second);
  return value;
}

int CarRFRx::getX(){
	return this->_x;
}
int CarRFRx::getY(){
	return this->_y;
}
uint8_t CarRFRx::getLevel(){
	return this->_level;
}
bool CarRFRx::isActiveMotor(){
	return this->_activeMotor;
}
bool CarRFRx::isWorking(){
	return this->_rf->isWorking();
}
long CarRFRx::getTime(){
	return this->_time;
}
void CarRFRx::setX(int x){
	this->_x = x;
}
void CarRFRx::setY(int y){
	this->_y = y;
}