/*--------------------------------------------------------------------------------------------------*/
/* Define headers required. */
#include <SoftwareSerial.h>
#include "DHT.h"
/*--------------------------------------------------------------------------------------------------*/
/* Define socket port. */
SoftwareSerial nodemcu(5,6);

/*--------------------------------------------------------------------------------------------------*/
/* Initializes or defines the output pins */
#define tempAndHumid 7  // analog A0 to temperature and himidity
#define DHTTYPE DHT22 
#define soilMois A0              //soil moisture sensor
#define ldr A1                //ldr sensor
/*--------------------------------------------------------------------------------------------------*/
//declaration of Relay pins

int relayTemp =10;
int relaySoilMois=11;
int relayLdr=12;
int relayState;
DHT dht(tempAndHumid, DHTTYPE);

/*--------------------------------------------------------------------------------------------------*/
int ReadTemperatureAndHumidity(void){
  int tempData = dht.readTemperature();
  int humidData = dht.readHumidity();
  if (tempData>28){
  (digitalWrite(relayTemp, LOW));
  }
  else{
  (digitalWrite(relayTemp, HIGH)); 
  }
  return (relayTemp);
}
/*--------------------------------------------------------------------------------------------------*/
int ReadSoilMoisture(void){
 int soilMoisData = analogRead(soilMois);
  if (soilMoisData>400){
  (digitalWrite(relaySoilMois, LOW));
  }
  else{
  (digitalWrite(relaySoilMois, HIGH)); 
  }
  return (relaySoilMois);
}
/*--------------------------------------------------------------------------------------------------*/
int ReadLightAvalablity(void){
 int ldrData = analogRead(ldr);
 if (ldrData){
  (digitalWrite(relayLdr, LOW));
  }
 
  else if (ldrData<200){
  (digitalWrite(relayLdr, LOW));
  }
  else{
  (digitalWrite(relayLdr, HIGH)); 
  }
  return (relayLdr);
}

void setup() {
  /*--------------------------------------------------------------------------------------------------*/
//declaring pin mode

pinMode(tempAndHumid,INPUT);
pinMode(soilMois,INPUT);
pinMode(ldr,INPUT);
pinMode(relayTemp,OUTPUT);
pinMode(relaySoilMois,OUTPUT);
pinMode(relayLdr,OUTPUT);
Serial.begin(9600);
nodemcu.begin(9600);
dht.begin();
}

void loop() {
  ReadTemperatureAndHumidity();
  ReadSoilMoisture();
  ReadLightAvalablity();
  int humidData1 = dht.readHumidity();
  int tempData1 = dht.readTemperature();
  int soilMoisData1 = analogRead(soilMois);
   int ldrData1 = analogRead(ldr);
  String stringPass= stringPass + soilMoisData1+","+tempData1+","+humidData1+","+ldrData1;
  Serial.println(stringPass);
  
  nodemcu.println(stringPass);
  delay(2000);
  stringPass="";
  delay(2000);
  
}
