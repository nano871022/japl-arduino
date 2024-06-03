#include <CalculateInitMotor.h>



CalculateInitMotor::CalculateInitMotor(Logs *log){
	this->_log = log;
}

uint8_t CalculateInitMotor::getPlusValues(uint8_t a, uint8_t b){
	return a + b <= 100 ? a + b : 100;
}

uint8_t CalculateInitMotor::getMinusValues(uint8_t a, uint8_t b){
	return a - b >= 0 ? a - b : 0;
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
uint8_t CalculateInitMotor::moveX(int x){
	//sprintf(this->_msg,"\nMoveX %04d \n", x);
	//this->log(this->_msg);
	uint8_t value =  this->getValue(x);
	if(value > 100 ){
		return 100;
	}

	if( value < 0){
		return 0;
	}
	return value;
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
uint8_t CalculateInitMotor::getValue(int value){
	if(this->_enable && this->_log->isActive()){
		sprintf(this->_log->msg,"\nGetValue IN %04d ", value);
		this->_log->log();
	}
	
	int output = 0;
	if(value > 0 && value <1025){
		if(value > 497){
			output = map(value,497,1023,1,100);
		}else{
			output = map(497-value,1,497,1,100);
		}
	}else if(value == 0){
		output = 100;
	}
	if(this->_enable && this->_log->isActive()){
		sprintf(this->_log->msg," OUT %03d \n ", output);
		this->_log->log();
	}
	if(output > 100){
		output = 100;
	}else if(output < 0){
		output = 0;
	}
	return output;
}

uint8_t CalculateInitMotor::moveY(int y){
	//sprintf(this->_msg,"\nMoveY %04d ", y);
	//this->log(this->_msg);
	float value =  this->getValue(y);
	if(value > 100 ){
		return 100;
	}

	if( value < 0){
		return 0;
	}
	return value;
}
	