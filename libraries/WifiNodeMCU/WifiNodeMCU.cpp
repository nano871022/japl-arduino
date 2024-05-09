
#include "Arduino.h"
#include "String.h"

#include <ESP8266WiFi.h>
#include <WifiNodeMCU.h>

#include <WiFiUdp.h>

WiFiUDP udp;
void WifiNodeMCU::begin(){
	unsigned long time = millis();
	WiFi.mode(WIFI_STA);
	WiFi.begin("Lore-Alejo","AL3j0_L0r30228-2016");
	//WiFi.begin("ArduinoUnoModuloWifi","123456789");
	log("Conectando");
	
	while(WiFi.status() != WL_CONNECTED && time+60000 > millis()){
		delay(500);
		print(".");
	}
	if(WiFi.status() == WL_NO_SSID_AVAIL){
		//log("ArduinoUnoModuloWifi no disponible para conexion");
		
		return;
	}
	if(WiFi.status() == WL_CONNECT_FAILED){
		//log("ArduinoUnoModuloWifi no se logro realiza la coneccion");
		
		return;
	}
	
	//Serial.println(WiFi.status() );
	//print("Conectado with local-ip: ");
	//Serial.print(WiFi.localIP());
	//log("");
	
}
	
void WifiNodeMCU::send(String message)	{
	udp.beginPacket("192.168.0.197",4445);
	udp.write(message.c_str());
	udp.endPacket();
	log("Send: "+message);
}
	
void WifiNodeMCU::log(String message){
	Serial.println(message.c_str());
}

void WifiNodeMCU::print(String message){
	Serial.print(message.c_str());
}
			

