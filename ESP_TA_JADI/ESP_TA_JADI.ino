#include <ESP8266WiFi.h>
#include <ThingSpeak.h>;
 #include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5

const char* ssid = "HOMIE";
const char* password = "cats2020";
//const char* ssid = "iPhone";
//const char* password = "nandacantik";
WiFiServer server(80);
WiFiClient client;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1 = { 0x28, 0xCC, 0x4, 0x94, 0x97, 0x8, 0x3, 0xCA };
DeviceAddress sensor2 = { 0x28, 0xAD, 0x14, 0x94, 0x97, 0x9, 0x3, 0x86 };
//unsigned long myChannelNumber = 1084258; //Your Channel Number (Without Brackets)
//const char * myWriteAPIKey = "ZTS7RNJUU018J78U"; //Your Write API Key
unsigned long myChannelNumber = 1085580; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "VA0K44TCB4O8E5IJ"; //Your Write API Key
int moist;
int SoM1 = A0; 
int val;

void setup() {
  Serial.begin(115200);
  delay(10);
ThingSpeak.begin(client);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  server.begin();
}

void loop() {
  moist = analogRead(SoM1); //Read Analog values and Store in val variable
 moist= map(moist,0,1023,100,0);
 //Serial.println(moist); //Print on Serial Monitor
 // delay(100);
  sensors.requestTemperatures();
  //delay(100);
  int TEMP = ((sensors.getTempC(sensor1) + sensors.getTempC(sensor2)) / 2);
 // Serial.println(TEMP);
  ThingSpeak.writeField(myChannelNumber, 2, moist, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 1, TEMP, myWriteAPIKey); //Update in ThingSpeak
 // delay(100);
  
  
  WiFiClient client = server.available();
  if (!client) {
     return;
  }
  
  //Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  //Serial.println(req);
 // client.flush();
  

  if (req.indexOf("/kipas1/0") != -1)
    val= 10;
  else if (req.indexOf("/kipas1/1") != -1)
   //Serial.println("11;0;0");
    val= 11;
   else if (req.indexOf("/kipas2/0") != -1)
    //Serial.println("20;0;0");
 val= 20;
  else if (req.indexOf("/kipas2/1") != -1)
   //Serial.println("21;0;0");
    val= 21;
   else if (req.indexOf("/pump/0") != -1)
    //Serial.println("30;0;0");
  val= 30;
  else if (req.indexOf("/pump/1") != -1)
   //Serial.println("31;0;0");
    val= 31;
    else {
    //Serial.println("invalid request");
 client.stop();
    return;
 }
  Serial.print(val);
 Serial.println(";0;0");
 client.flush();
 String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

 client.print(s);
} 



  //delay(1);
 // Serial.println("Client disonnected");
