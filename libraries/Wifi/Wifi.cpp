/**
** Wifi.cpp implmenets Wifi.h 
** library implementation
**/
#define ledBoardPin 13
#include "Arduino.h"
#include "String.h"
#include "Wifi.h"
#include <SoftwareSerial.h>



Wifi::Wifi(uint8_t rx , uint8_t tx){
	_softSerial = new SoftwareSerial(rx,tx);
}

void Wifi::begin(long baud){
	_softSerial->begin(baud);
	createNetwork();
	createUDP();
	if(led_red > 0){
		pinMode(led_red,OUTPUT);
	}
	if(led_blue > 0){
		pinMode(led_blue,OUTPUT);
	}
	if(led_green > 0){
		pinMode(led_green,OUTPUT);
	}
	command("AT+CWJAP?",100);
    command("AT+CIFSR",4000);
}
int Wifi::read(){
	return _softSerial->read();
	
}

String Wifi::command(char* commands,long wait = 2000){
	bool active = true;
	String start = waitAllMessage(wait);
	String values = "";
	while(active){
		_softSerial->print(commands);
		_softSerial->print("\r\n");
		delay(50);
		values = waitAllMessage(wait);	
		if(values.indexOf("busy")>=0){
			delay(150);
			
			ledWrite(led_blue,HIGH);
			ledWrite(led_red,LOW);
			ledWrite(led_green,LOW);
			
			logln("Esperando busy");
		}else{
			active = false;
		}
	}
	delay(30);
	if(values.indexOf("ERROR")>=0){
		ledWrite(led_red,HIGH);
		ledWrite(led_green,LOW);
		ledWrite(led_blue,LOW);
	}else if(values.indexOf("OK")>=0){
		ledWrite(led_green,HIGH);
		ledWrite(led_red,LOW);
		ledWrite(led_blue,LOW);
	}
	if(issues>2){
		issues = 0;
		command("AT+RST");
		resets++;
	}
	
	return values;
}

void Wifi::print(char message){
	_softSerial->print(message);
}

bool Wifi::available(){
	return _softSerial->available();
}

 void Wifi::logln(String message){
	if(message.length() > 0 && _isSerialPrint){
		Serial.println(message);
	} 
 }
  void Wifi::log(String message){
	if(message.length() > 0 && _isSerialPrint){
		Serial.print(message);
	} 
 }

String Wifi::waitAllMessage(long wait = 2000){
	String values = "";
	unsigned long start = millis() + wait;
	
	ledWrite(led_blue,HIGH);
	
	do{
		while(_softSerial->available()){
			char v = _softSerial->read();
			values += v;
		}
		delay(50);
	}while(start > millis());
	
	log(".");
	
	ledWrite(led_blue,LOW);
	delay(10);
	
	
	logln(values);
	
	return values;
}

bool Wifi::closeUDP(String user = "0"){
	String commands = "AT+CIPCLOSE";
	//commands.concat(user);
	String response = command(commands.c_str(),20);
	return response.indexOf("OK")>=0;
}

bool Wifi::openUDP(String user = "0"){
	String commands = "AT+CIPSTART=";
	//commands.concat(user);
	commands.concat("\"UDP\",\"0.0.0.0\",4445,1000,2");
	String result = command(commands.c_str(),80);
	return result.indexOf("OK")>=0;
}
 
 String Wifi::waitUDPConnection(){
	ledWrite(led_green,LOW);
	ledWrite(led_red,LOW);
	ledWrite(led_blue,LOW);
		 
	 String values = waitAllMessage(1000);
	 if(values.indexOf("IPD,",1)>=0){
		int pos = values.indexOf(":",1);
		String value = values.substring(pos+1);
		value = value.substring(0,value.indexOf("\n",1));
		logln(value);
		lastCheck = 0;
		return value;
	 }
	 
	  if(lastCheck == 0){
		lastCheck = millis() + 3000;
	}else if(lastCheck < millis()){
		ledWrite(led_red,HIGH);
		delay(10);

		lastCheck = 0;
		command("AT+CIPSTATUS",1000);
		closeAndOpenUDP();

		ledWrite(led_red,LOW);
	}
	 return values;
 }
 
 void Wifi::leds(uint8_t red,uint8_t blue,uint8_t green){
	 led_red = red;
	 led_blue = blue;
	 led_green = green;
 }
 
 String Wifi::waitTCPConnection(){
	 String values = waitAllMessage(1000);
	 if(values.indexOf("IPD,",1)>=0){
		int pos = values.indexOf(":",1);
		String value = values.substring(pos+1);
		value = value.substring(0,value.indexOf("\n",1));
		logln(value);
		return value;
	 }
	 return values;
 }

void Wifi::waitServerConnection(){
	String values = "";
	while(_softSerial->available()){
		char v = _softSerial->read();
		values += v;
		delay(10);
	}
	//+IPD,0,362:GET /DADASDAD HTTP/1.1
	if(values.length() > 0 && values.indexOf("IPD",1)>=0){
		int pos = values.indexOf(":GET ");
		int pos2= values.indexOf(" HTTP/1.1");
		String conn = values.substring(0,1);
		String path = values.substring(pos+5,pos2);
		String sender = "AT+CIPSEND="+conn+",17";
		command(sender.c_str());
		String response = "thanks: "+path;
		command(response.c_str());
		String close = "AT+CIPCLOSE="+conn;
		command(close.c_str());
	}
	
}
void Wifi::createNetwork(){
	command("AT+CWJAP=\"Lore-Alejo\",\"AL3j0_L0r30228-2016\"",3000);
	//command("AT+CWSAP=\"ArduinoUnoModuloWifi\",\"123456789\",8,2");
	//command("AT+CIPAP=\"192.168.0.200\"");
}

void Wifi::enableMultiConnect(){
	String response = command("AT+CIPMUX?",4000);
	if(response.indexOf("CIPMUX:1",1) >= 0 && response.indexOf("OK",1) >= 0){
		command("AT+CIPMUX=0");
	}
}

void Wifi::createServer(){
	enableMultiConnect();
	delay(2000);
	command("AT+CIPSERVER=1,8080");
}

void Wifi::createUDP(){
	enableMultiConnect();
	if(!openUDP()){
		closeAndOpenUDP();
	}
}
 void Wifi::createTCP(){
	enableMultiConnect();
	command("AT+CIPSTART=0,\"TCP\",\"0.0.0.0\",4845,4845,1",2000);
 }

int  Wifi::isCreateNetwork(){}
int  Wifi::isCreateServer(){}

void Wifi::setSerialPrint(bool isSerialPrint){
	_isSerialPrint = isSerialPrint;
}

void Wifi::closeAndOpenUDP(){
	 if(userId > 4){
		 return;
	 }
	 if(closeUDP(String(userId))){
      if(!openUDP(String(userId))){
		  issues++;
		  closeAndOpenUDP();
	  }
    }else{
		//userId ++;
		if(!openUDP(String(userId))){
			issues++;
			closeAndOpenUDP();
		}
	}
}

void Wifi::ledWrite(uint8_t led,int power){
	if(led > 0){
		digitalWrite(led,power);
	}
}

short Wifi::getResets(){
	return resets;
}