#include <MoveCar.h>


MoveCar::MoveCar(uint8_t da_left, uint8_t da_Right, uint8_t da_fLeft, uint8_t da_fRight, uint8_t da_bLeft, uint8_t da_bRight, Logs *log, CarRFRx *rf,Leds *ledRed,Leds *led1Red,Leds *led1Blue,Leds *led1Green,Leds *led2Red,Leds *led2Blue,Leds *led2Green){
	this->_log = log;
	this->_rf = rf;
	this->_calc = new CalculateInitMotor(log);
	this->motorLeft = new MotorPwmOut(da_left, log);
	this->motorRight = new MotorPwmOut(da_Right, log);

	this->motorLeft->setMinPower(this->_minPowerMotor);
	this->motorRight->setMinPower(this->_minPowerMotor);
	this->motorRight->setReducePower(1.0);
	this->motorLeft->setReducePower(0.25);
	this->_d_f_Left = da_fLeft;
	this->_d_f_Right = da_fRight;
	this->_d_b_Left = da_bLeft;
	this->_d_b_Right = da_bRight;

	this->_led_red = ledRed;
	this->_led1_red = led1Red;
	this->_led1_blue = led1Blue;
	this->_led1_green = led1Green;
	this->_led2_red = led2Red;
	this->_led2_blue = led2Blue;
	this->_led2_green = led2Green;
}

void MoveCar::begin(){
	this->motorLeft->begin();
	this->motorRight->begin();

	pinMode(this->_d_f_Left,OUTPUT);
	pinMode(this->_d_f_Right,OUTPUT);
	pinMode(this->_d_b_Left,OUTPUT);
	pinMode(this->_d_b_Right,OUTPUT);
}

void MoveCar::stop(){
	digitalWrite(this->_d_f_Left,LOW);
	digitalWrite(this->_d_f_Right,LOW);
	digitalWrite(this->_d_b_Left,LOW);
	digitalWrite(this->_d_b_Right,LOW);	
	this->motorRight->stop();
	this->motorLeft->stop();
	this->motorLeft->off();
	this->motorRight->off();
	if(this->_rf->isActiveMotor()){
		this->_led1_red->on();
		this->_led2_red->on();
	}
}
/**
** in this point all calculation about percent power in each axi is calculated 
** so it need to know that value is assign to left and right movement 
** right: move Y + move X
** left:  move Y - move X
**/
void MoveCar::move(int x, int y){
	if(x < 0 && y < 0){
		this->stop();
		return;
	}
	//sprintf(this->_msg,"\nX %04d Y %04d ", x, y);
	//this->log(this->_msg);

	uint8_t mx = this->_calc->moveX(x);
	uint8_t my = this->_calc->moveY(y);
	if(this->_enable_log && this->_log->isActive()){
		sprintf(this->_log->msg,"Car::INF: MX: %04d X: %04d MY: %04d Y: %04d Level: %02d \n\r",mx,x,my,y,this->_rf->getLevel());
		this->_log->log();
	}
    this->motorLeft->setLevel(this->_rf->getLevel());
    this->motorRight->setLevel(this->_rf->getLevel());
    if(this->_rf->isActiveMotor()){
    	this->motorLeft->on();
    	this->motorRight->on();
	}
	
	if(my > 0 && my < 5 && mx > 0 && mx < 5){
		this->stop();
		return;
	}

	this->moveForward(x, y, mx , my);
	this->moveBackward(x, y, mx , my);
	this->moveRight(x, y, mx , my);
	this->moveLeft(x, y, mx , my);
	this->moveRightForward(x, y, mx , my);
	this->moveLeftForward(x, y, mx , my);
	this->moveRightBackward(x, y, mx , my);
	this->moveLeftBackward(x, y, mx , my);

}

void MoveCar::forward(){
	if(this->_rf->isActiveMotor()){
		digitalWrite(this->_d_b_Left,LOW);
		digitalWrite(this->_d_b_Right,LOW);

		digitalWrite(this->_d_f_Left,HIGH);
		digitalWrite(this->_d_f_Right,HIGH);
	}else{
		this->_led1_red->off();
		this->_led2_red->off();
	}
}

void MoveCar::backward(){
	digitalWrite(this->_d_b_Left,HIGH);
	digitalWrite(this->_d_b_Right,HIGH);

	digitalWrite(this->_d_f_Left,LOW);
	digitalWrite(this->_d_f_Right,LOW);
}
void MoveCar::motor(){
	if(this->_rf->isWorking()){
  		this->moveMotor();
	}else{
		this->_led1_red->on();	
		this->_led1_red->on();	
		this->stop();
	//	delay(100);
	}
}

void MoveCar::moveMotor(){
	if(this->_rf->getTime() < millis() ){
  		this->_rf->setX(0);
  		this->_rf->setY(0);
  		this->_led_red->on();
  		if(this->_enable_log && this->_log->isActive()){
  			sprintf(this->_log->msg,"Car::INF:Stop times %d less millis %d ",this->_rf->getTime(),millis());
  			this->_log->log();
  		}
  		this->stop();
   		//delay(50);
   		return;
  	}

  	if(this->_rf->isActiveMotor()){
  		if( (this->_rf->getX() >= 0 || this->_rf->getY() >= 0)){
  			this->move(this->_rf->getX(),this->_rf->getY());
  		}
  	}else{
  		this->stop();
  	}
  }

 bool MoveCar::isUp(int value){
	return value > 497;
}


void MoveCar::moveForward(int x, int y, uint8_t mx , uint8_t my){
	if(my > 0 && mx < 5 && isUp(y)){
		this->_log->log("\nmoveForward\n");
		this->forward();
		motorLeft->move(my);
		motorRight->move(my);
		this->_led1_green->unblock();
		this->_led1_green->on();
		this->_led1_blue->unblock();
		this->_led1_blue->off();
		this->_led2_blue->unblock();
		this->_led2_blue->off();
		this->_led2_green->unblock();
		this->_led2_green->off();
	}
}
void MoveCar::moveBackward(int x, int y, uint8_t mx , uint8_t my){
	 if(my > 0 && mx < 5 && !isUp(y)){
	 	this->_log->log("\nmoveBackward\n");
		this->backward();
		motorLeft->move(my);
		motorRight->move(my);
		this->_led1_blue->unblock();
		this->_led1_blue->on();
		this->_led1_green->unblock();
		this->_led1_green->off();
		this->_led2_blue->unblock();
		this->_led2_blue->off();
		this->_led2_green->unblock();
		this->_led2_green->off();
	}
}
void MoveCar::moveLeft(int x, int y, uint8_t mx , uint8_t my){
	if(my < 5 && mx > 0 && !isUp(x)){
		this->_log->log("\nmoveLeft\n");
		this->forward();
		motorLeft->move(0);
		motorRight->move(mx);
		this->_led2_blue->unblock();
		this->_led2_blue->on();
		this->_led1_blue->unblock();
		this->_led1_blue->off();
		this->_led1_green->unblock();
		this->_led1_green->off();
		this->_led2_green->unblock();
		this->_led2_green->off();
	}
}
void MoveCar::moveRight(int x, int y, uint8_t mx , uint8_t my){
	 if(my < 5 && mx > 0 && isUp(x)){
	 	this->_log->log("\nmoveRight\n");
		this->forward();
		motorLeft->move(mx);
		motorRight->move(0);
		this->_led2_green->unblock();
		this->_led2_green->on();
		this->_led1_blue->unblock();
		this->_led1_blue->off();
		this->_led2_blue->unblock();
		this->_led2_blue->off();
		this->_led1_green->unblock();
		this->_led1_green->off();
	}
}
void MoveCar::moveLeftForward(int x, int y, uint8_t mx , uint8_t my){
	if(!isUp(x) && mx > 5 && isUp(y)){
		this->_log->log("\nmoveLeftForward\n");
		this->forward();
		motorLeft->move(this->_calc->getMinusValues(my,mx));
		motorRight->move(this->_calc->getPlusValues(my,mx));
		if(mx > 10){
			this->_led1_blue->unblock();
			this->_led1_blue->on();
			this->_led1_green->unblock();
			this->_led1_green->off();
		}
    	if(my > 10){
    		this->_led2_green->unblock();
    		this->_led2_green->on();
			this->_led2_blue->unblock();
			this->_led2_blue->off();
    	}
	}
}
void MoveCar::moveLeftBackward(int x, int y, uint8_t mx , uint8_t my){
  if(!isUp(x) && mx > 5 && !isUp(y)){
  	this->_log->log("\nmoveLeftBackward\n");
		this->backward();
		motorLeft->move(this->_calc->getMinusValues(my,mx));
        motorRight->move(this->_calc->getPlusValues(my,mx));
        if(mx > 10){
        	this->_led1_blue->unblock();
        	this->_led1_blue->on();
        	this->_led1_green->unblock();
			this->_led1_green->off();
    	}
    	if(my > 10){
    		this->_led2_blue->unblock();
    		this->_led2_blue->on();
			this->_led2_blue->unblock();
			this->_led2_blue->off();
    	}
	}
}
void MoveCar::moveRightForward(int x, int y, uint8_t mx , uint8_t my){
	if(isUp(x) && mx > 5 && isUp(y)){
		this->_log->log("\nmoveRightForward\n");
		this->forward();
		motorLeft->move(this->_calc->getPlusValues(my,mx));
		motorRight->move(this->_calc->getMinusValues(my,mx));
		if(mx > 10 ){
			this->_led1_green->unblock();
			this->_led1_green->on();
			this->_led1_blue->unblock();
			this->_led1_blue->off();
		}
    	if(my > 10){
    		this->_led2_green->unblock();
    		this->_led2_green->on();
			this->_led2_blue->unblock();
			this->_led2_blue->off();
    	}
	}
}
void MoveCar::moveRightBackward(int x, int y, uint8_t mx , uint8_t my){
	if(isUp(x) && mx > 5 &&  !isUp(y)){
		this->_log->log("\nmoveRightBackward\n");
		this->backward();
		motorLeft->move(this->_calc->getPlusValues(my,mx));
		motorRight->move(this->_calc->getMinusValues(my,mx));
		if(mx > 10 ){
			this->_led1_green->unblock();
			this->_led1_green->on();
			this->_led1_blue->unblock();
			this->_led1_blue->off();
		}
    	if(my > 10){
    		this->_led2_blue->unblock();
    		this->_led2_blue->on();
			this->_led2_green->unblock();
			this->_led2_green->off();
    	}
	}
}
