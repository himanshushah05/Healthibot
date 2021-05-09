#include <ESP8266WiFi.h>;

#include <WiFiClient.h>;

#include <ThingSpeak.h>;
#include<DHT.h>
#define DHTTYPE DHT11

int dhtpin = 4;//d2
double alpha=0.75;
int period=20;
double refresh=0.0;

const char* ssid = "Atul Shah"; //Your Network SSID

const char* password = "atulshah"; //Your Network Password
WiFiClient client;

unsigned long myChannelNumber = 1382546; //Your Channel Number (Without Brackets)

const char * myWriteAPIKey = "64CCKL34S37D4I1X"; //Your Write API Key


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0,INPUT);
delay(10);

// Connect to WiFi network

WiFi.begin(ssid, password);



ThingSpeak.begin(client);

}
void temp(){
  DHT dht(dhtpin,DHTTYPE);
  dht.begin();
  float t = dht.readTemperature();
  float f = (t*9)/5 + 32; 
  Serial.print("temperature = ");
  Serial.print(f); 
  Serial.println("F  ");
  delay(800);
  ThingSpeak.writeField(myChannelNumber, 2,f, myWriteAPIKey); //Update in ThingSpeak
  delay(100);
}
void beat(){
   static double oldValue=0;
   static double oldrefresh=0;
   int beat=analogRead(A0);
   double value=alpha*oldValue+(0-alpha)*beat;
   refresh=value-oldValue;
   Serial.print(" Heart Monitor "); 
   Serial.print("          ");
   Serial.println(beat/10);
   oldValue=value;
   oldrefresh=refresh;
   delay(period*10);
   ThingSpeak.writeField(myChannelNumber, 1,beat/10, myWriteAPIKey); 
  

}

void loop() {
  // put your main code here, to run repeatedly:
temp();
beat();
}
