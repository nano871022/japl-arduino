#include <Controller_jostick_rf.h>

Controller_jostick_rf::Controller_jostick_rf(uint8_t a_x,uint8_t a_y,uint8_t d_click,uint8_t portRH){
	this->_jostick = new Jostick(a_x,a_y,d_click);
	this->_rfTx = new RFTx(portRH);
}

void Controller_jostick_rf::logs(bool enable){
	this->_enableLog = enable;
	this->_jostick->setSerial(enable);
}

void Controller_jostick_rf::begin(int baud){
  this->_rfTx->begin(baud);  
  this->_jostick->begin();
 
}

void Controller_jostick_rf::loop(){
  this->_jostick->read();
  char values[10];
  sprintf(values,"X%04dY%04dC%01d",this->_jostick->getHorizontalValue(),this->_jostick->getVerticalValue(),this->_jostick->isClicked()?1:0);
  
  this->log("Send: ");
  this->log(values);
  this->log("\n\r");
  
  this->_rfTx->inLoop(values);
}
	
 void Controller_jostick_rf::log(char *msg){
  if(this->_enableLog){
    Serial.print(msg);
  }
 }