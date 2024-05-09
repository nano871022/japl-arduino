/**
** Wifi.h by JAPL -
** Library to connect with WIFI module and setting in server mode to
** get connection in wifi and provide some commands to move the device
** Created By JAPL in April 21 2024
*/
#ifndef Wifi_h
#define Wifi_h

#include "Arduino.h"

#define acknowledge "AT"
//const char* reset = "AT+RST";
//const char* speedTx = "AT+CIOBAUD?";
//const char* speedTxChange1 = "AT+CIOBAUD";
//const char* speedTxChange2 = "AT+IPR";
/**
** 1 Station
** 2 SoftAp
** 4 Station + SoftAp 
**/
//const char* getMode = "AT+CWMODE?";
//const char* setMode = "AT+CWMODE";
//const char* seeEnableWifi = "AT+CWLAP";
/**
** AT+CWJAP=${ssid name}, ${pwd}
**/
//const char* connectToWifi = "AT+CWJAP";
#define checkConnected "AT+CWJAP?"
#define getIp "AT+CIFSR"
/**
** AT+CWSAP="SSID", "pwd", 3, 0
**/
#define createNetworkWifi "AT+CWSAP"
//const char* listDeviceConnected = "AT+CWLIF";
/**
** AT+CIPSERVER=enable, port
** Enable: 1(TRUE)/0(FALSE)
** Port  : 80
**/
//const char* activeServer = "AT+CIPSERVER";
/**
** active multiple connection 
** AT+CIPMUX=enable
** Enable: 1(TRUE)/0(FALSE)
**/
//const char* activeMultipleConecctions = "AT+CIPMUX";
/**
** connect to x server
** AT+CIPSTART=channel , mode, IP, port
** Channel: 4
** Mode: TCP/UDP 
** Ip  : Ip to connect
** Port: Port to connect ex: 80
**/
//const char* connectToServer = "AT+CIPSTART";
//const char* modeTx = "AT+CIPMODE";
/**
** send data for chanel and bytes to send
** AT+CIPSEND=4,5
**/
//const char* sendData = "AT+CIPSEND";
#include <SoftwareSerial.h>
#include "String.h"

class Wifi{
	public:
	    Wifi(uint8_t rx , uint8_t tx);
		void begin(long baud);
		int read();
		void print(char message);
		String command(char* command,long wait = 2000);
		bool available();
		void setSerialPrint(bool isSerialPrint);
		void waitServerConnection();
		String waitUDPConnection();
		String waitTCPConnection();
		bool closeUDP(String user = "0");
		bool openUDP(String user = "0");
		void leds(uint8_t red,uint8_t blue,uint8_t green);
		void closeAndOpenUDP();
		short getResets();
	private:
	  const char* _SSDI = "body";
	  const char* _pwd = "body12345";
	  SoftwareSerial *_softSerial;
	  uint8_t userId = 0;
	  short issues = 0;
	  short resets = 0;
	  unsigned int lastCheck = 0;
	  int _baud;
	  uint8_t led_red = 0;
	  uint8_t led_blue = 0;
	  uint8_t led_green = 0;
	  bool connected = false;
	  
	  void createNetwork();
	  void createServer();
	  void createUDP();
	  void createTCP();
	  
	  int isCreateNetwork();
	  int isCreateServer();
	  bool _isSerialPrint = true;
	  
	  void log(String message);
	  void logln(String message);
	  String waitAllMessage(long wait = 2000);
	  void enableMultiConnect();
	  void ledWrite(uint8_t led,int power);
};

#endif