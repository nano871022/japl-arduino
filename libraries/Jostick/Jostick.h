/**
** Jostick.h Manage jostick in percentage values
**/
#include "Arduino.h"

class Jostick{
	public: 
	    Jostick(uint8_t aPortHorizontal,uint8_t aPortVertical, uint8_t dPortClick);
		void begin();
		void setMinPwm(double min);
		void setSerial(bool isActive);
		void read();
		int getHorizontalValue();
		int getVerticalValue();
		bool isClicked();
		
	private:
		int _currentHorizontal = 0;
		int _currentVertical = 0;
		int _currentClick = LOW;
		uint8_t _aPortHorizontal;
		uint8_t _aPortVertical;
		uint8_t _dPortClick;
		const double _maxPwm = 1025.0;
		double _minPwm = 0.0;
		void log(char* msg);
		bool _isSerial = true;
};