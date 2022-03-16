#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
 #include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5

const char* ssid = "HOMIE"; //Your Network SSID
const char* password = "cats2020"; //Your Network Password
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1 = { 0x28, 0xCC, 0x4, 0x94, 0x97, 0x8, 0x3, 0xCA };
DeviceAddress sensor2 = { 0x28, 0xAD, 0x14, 0x94, 0x97, 0x9, 0x3, 0x86 };
 
WiFiClient client;
//unsigned long myChannelNumber = 1084258; //Your Channel Number (Without Brackets)
//const char * myWriteAPIKey = "ZTS7RNJUU018J78U"; //Your Write API Key
unsigned long myChannelNumber = 1085580; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "VA0K44TCB4O8E5IJ"; //Your Write API Key
int moist;
int SoM1 = A0; 
 
void setup(){
Serial.begin(9600);
delay(10);
// Connect to WiFi network
WiFi.begin(ssid, password);
ThingSpeak.begin(client);
}
 
void loop(){
  moist = analogRead(SoM1); //Read Analog values and Store in val variable
 // Serial.print(moist); //Print on Serial Monitor
  delay(100);
  sensors.requestTemperatures();
  delay(100);
  int TEMP = ((sensors.getTempC(sensor1) + sensors.getTempC(sensor2)) / 2);
  //Serial.println(TEMP);
  ThingSpeak.writeField(myChannelNumber, 2, moist, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 1, TEMP, myWriteAPIKey); //Update in ThingSpeak
  delay(100);
  
 
}
