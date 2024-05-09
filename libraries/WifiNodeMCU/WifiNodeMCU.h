/**
** WifiNodeMCU.h Libreria to manage connection wifi with another arduino
**/
#ifndef WifiNodeMCU_h
#define WifiNodeMCU_h

#include "Arduino.h"
#include <ESP8266WiFi.h>

class WifiNodeMCU{
	
	public:
		
		void begin();
		void send(String message);
		
	private:
		
		
		void log(String message);
		
		void print(String message);
	
};

#endif