#include <Controller_jostick_rf.h>

Controller_jostick_rf::Controller_jostick_rf(uint8_t a_x,uint8_t a_y,uint8_t d_click,uint8_t portRH,uint8_t pinRead,uint8_t pinRed, uint8_t pinBlue, uint8_t pinGreen){
  this->_log = new Logs();
  this->_ledGreen = new Leds(pinGreen);
  this->_ledBlue = new Leds(pinBlue);
  this->_ledRed = new Leds(pinRed);
  this->_jostick = new Jostick(a_x,a_y,d_click,this->_ledRed,this->_ledBlue,this->_ledGreen,this->_log);
  this->_rfTx = new RFTx(portRH, this->_log);
  this->_voltageCheck = new VoltageCheck(pinRead,this->_ledRed,this->_ledBlue,this->_ledGreen, this->_log);
}

void Controller_jostick_rf::logs(bool enable){
	this->_log->setActive(enable);
}

void Controller_jostick_rf::begin(int baud){
  this->_rfTx->begin(baud);  
  this->_jostick->begin();
  this->_voltageCheck->begin();
  this->_ledRed->blink(500);
  this->_ledBlue->blink(500);
  this->_ledGreen->blink(500);

}

void Controller_jostick_rf::loop(){
  switch(this->_steps){
    case 0: this->_jostick->read();break;
    case 1: this->sendRx();break;
    case 2: this->_voltageCheck->read();break;
    default: break;
  }
  this->countSteps();
}

void Controller_jostick_rf::countSteps(){
  if(this->_steps <3){
    this->_steps++;
  }else{
    this->_steps=0;
  }
}
void Controller_jostick_rf::sendRx(){
  sprintf(this->_log->msg,"X%04dY%04dC%01dM%01d",this->_jostick->getHorizontalValue(),this->_jostick->getVerticalValue(),this->_jostick->isClicked()?1:0,this->_jostick->activeMotor());
  if(this->_log->isActive()){
    this->_log->log("\nSend: ");
    this->_log->log(this->_log->msg);
    this->_log->log("\n\r");
  }
  
  this->_rfTx->inLoop(this->_log->msg);
}
