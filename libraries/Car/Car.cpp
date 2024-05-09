/**
**
**/
#include "Car.h"
#include "Arduino.h"



Car::Car(uint8_t da_Left,uint8_t da_fLeft,uint8_t da_bLeft,uint8_t da_Right, uint8_t da_fRight,uint8_t da_bRight,uint8_t portRH,uint8_t d_l_red,uint8_t d_l_blue,uint8_t d_l_green){
	this->rfRx = new RFRx(portRH);
	this->motorLeft = new MotorPwmOut(da_Left);
	this->motorRight = new MotorPwmOut(da_Right);
	
	this->motorLeft->setMinPower(minPowerMotor);
	this->motorRight->setMinPower(minPowerMotor);
	
	this->_d_f_Left = da_fLeft;
	this->_d_f_Right = da_fRight;
	this->_d_b_Left = da_bLeft;
	this->_d_b_Right = da_bRight;
	
	this->_d_l_red = d_l_red;
	this->_d_l_blue = d_l_blue;
	this->_d_l_green = d_l_green;
}

void Car::begin(int baud){
	this->rfRx->begin(baud);
	this->motorLeft->begin();
	this->motorRight->begin();
	pinMode(this->_d_f_Left,OUTPUT);
	pinMode(this->_d_f_Right,OUTPUT);
	pinMode(this->_d_b_Left,OUTPUT);
	pinMode(this->_d_b_Right,OUTPUT);
	
	pinMode(this->_d_l_green,OUTPUT);
	pinMode(this->_d_l_blue,OUTPUT);
	pinMode(this->_d_l_red,OUTPUT);
	
	digitalWrite(this->_d_l_green,HIGH);
	delay(1000);
	digitalWrite(this->_d_l_green,LOW);
	delay(1000);
	digitalWrite(this->_d_l_green,HIGH);
	delay(1000);
	digitalWrite(this->_d_l_green,LOW);
}

/**
** moving on X axial
** when it said left and right
**  left motor left strong motor right weak
**  right motor left weak motor right strong
** x: 60 . 19%
** y: 90 . 79%
** 
**/
float Car::moveX(float x){
	
	if(this->isUp(x)){
		return this->getValue(x);
	}else if(x == 0){
		return 0;
	}else{
		return this->getValue(x);
	}
	
}
/**
** this calculate value from percentage total but it need to divide between forward and backward
** ex: it has value 85 and 15
** it mean is Up (increase) so 
** increase values are 51 to 100
** decrease values are  1 to  49
** 100% . 100%   -  49% . 100%
**  51% .   1%   -   1% .   1%
**  50% .   0%   -   0% .   0%
** Formulas:
** ((((:value - 51) / (100 - 51))) X (100 - 1)) + 1 = :percent => (((85 - 51) / (100 - 51)) X (100 - 1)) + 1 => ((34 / 49) X 99) + 1 => (0.693877551 X 99) + 1 => 69.693877551
** ((((:value -  1) / ( 49 -  1))) X (100 - 1)) + 1 = :percent => (((15 -  1) / ( 49 -  1)) X (100 - 1)) + 1 => ((14 / 48) X 99) + 1 => (0.29166667  X 99) + 1 => 29.875
** 
**/
float Car::getValue(float value){
	if(value>50){
		return (((value - 51) / (100 - 51)) * (100-1)) + 1;
	}else if(value<50){
		return (((value -  49) / ( 1 -  49)) * (100-1)) + 1;
	}else{
		return 0;
	}
}

float Car::moveY(float y){

	if(this->isUp(y)){
		return this->getValue(y);
	}else if(y == 0){
		return 0;
	}else{
		return this->getValue(y);
	}
	
}
	
bool Car::isUp(float value){
	return value > 50;
}

void Car::stop(){
	this->motorRight->stop();
	this->motorLeft->stop();
}
/**
** in this point all calculation about percent power in each axi is calculated 
** so it need to know that value is assign to left and right movement 
** right: move Y + move X
** left:  move Y - move X
**/
void Car::move(float x, float y){
	
	float mx = this->moveX(x);
	float my = this->moveY(y);
	
	this->log("X: ");
	this->log((char)mx);
	this->log(" Y: ");
	this->log((char)my);
	this->log("\n\r");
     
	if(my == 0 && mx == 0){
		stop();
	}else if(isUp(x) && isUp(y)){
		this->forward();
		motorLeft->move(getMinusValues(my,mx));
		motorRight->move(getPlusValues(my,mx));
	}else if(!isUp(x) && isUp(y)){
		this->forward();
		motorLeft->move(getPlusValues(my,mx));
		motorRight->move(getMinusValues(my,mx));
	}else if(isUp(x) && !isUp(y)){
		this->backward();
		motorLeft->move(getMinusValues(my,mx));
		motorRight->move(getPlusValues(my,mx));
	}else if(!isUp(x) && !isUp(y)){
		this->backward();
		motorLeft->move(getPlusValues(my,mx));
        motorRight->move(getMinusValues(my,mx));
	}else{
		stop();
	}
}

void Car::forward(){
	digitalWrite(this->_d_b_Left,LOW);
		digitalWrite(this->_d_b_Right,LOW);
		digitalWrite(this->_d_f_Left,HIGH);
		digitalWrite(this->_d_f_Right,HIGH);
}

void Car::backward(){
	digitalWrite(this->_d_b_Left,LOW);
		digitalWrite(this->_d_b_Right,LOW);
		digitalWrite(this->_d_f_Left,HIGH);
		digitalWrite(this->_d_f_Right,HIGH);
}

uint8_t Car::getPlusValues(float a, float b){
	return a + b <= 100 ? a + b : 100;
}

uint8_t Car::getMinusValues(float a, float b){
	return a - b >= 0 ? a - b : 0;
}

void Car::log(char* msg){
	if(_enableLog){
		Serial.print(msg);
	}
}

void Car::ledsLow(){
  digitalWrite(this->_d_l_green,LOW);
  digitalWrite(this->_d_l_blue,LOW);
  digitalWrite(this->_d_l_red,LOW);
}

uint8_t Car::getX(String msg){
  String value = get(msg,1,5);
   return value.toInt();
}

uint8_t Car::getY(String msg){
  String value = get(msg,6,10);
   return value.toInt();
}

String Car::get(String msg,uint8_t first, uint8_t second){
  String value = msg.substring(first,second);
  return value;
}

void Car::loop(){
  this->ledsLow();
  char* response = this->rfRx->inLoop();

  if(strlen(response)>0){
    digitalWrite(_d_l_blue,HIGH);
    String value = String(response);
    this->_x = this->getX(value);
    this->_y = this->getY(value);
  }
  this->move(this->_x,this->_y);
  digitalWrite(this->_d_l_green,HIGH);
}

void Car::logs(bool enable = false){
	this->_enableLog = enable;
	this->motorLeft->setSerial(enable);
	this->motorRight->setSerial(enable);
	this->rfRx->logs(enable);
}