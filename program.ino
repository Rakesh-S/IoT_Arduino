// this project used Arduino nano board and ESP8266 wifi module

#include<stdlib.h>
#define SSID "rakesh"       // SSID of wifi to which ESP is connected
#define PASS "123456781"    // Password for connection
#define IP "api.thingspeak.com"  //
const int LED=4;    
const int IN1=6;
const int IN2=7;
const int EN=8;
const int GAS=A0;
String GET = "GET /update?key=4ULBN78I6EQ5ONC5&field1=";
String GET1 = "GET /update?key=4ULBN78I6EQ5ONC5&field2=";
void setup()
{ 
  pinMode(LED,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(EN,OUTPUT);
  pinMode(GAS,INPUT);
  Serial.begin(9600);
  Serial.println("AT");
  delay(5000);
  if(Serial.find("OK")){
    connectWiFi();
  }
}
void loop() {
  char buffer[10];
  int SML=analogRead(GAS);
  int PER=digitalRead(PIR);
  Serial.println(SML);
  delay(200);
  Serial.println(PER);
  delay(2000);
   if(SML>600)
  {
    digitalWrite(LED,HIGH);
  }
  else
  {
    digitalWrite(LED,LOW);
  }
  connectTCP();
  String beginning= GET;
  beginning +=SML;
  beginning +="\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(beginning.length());
  if(Serial.find(">")){
    Serial.print(beginning);
  }else{
    Serial.println("AT+CIPCLOSE");
  }
  delay(15000);
}

 
boolean connectWiFi(){
  Serial.println("AT+CWMODE=1");
  delay(2000);
  String hotspot="AT+CWJAP=\"";
  hotspot+=SSID;
  hotspot+="\",\"";
  hotspot+=PASS;
  hotspot+="\"";
  Serial.println(hotspot);
  delay(5000);
  if(Serial.find("OK")){
    return true;
  }else{
    return false;
  }
}


boolean connectTCP()
{
String beginning = "AT+CIPSTART=\"TCP\",\"";
  beginning  += IP;
  beginning  += "\",80";
  Serial.println(beginning );
  delay(2000);
  if(Serial.find("Error")){
    return;
  }}
