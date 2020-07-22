#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
SoftwareSerial nodemcu(D6,D5);
 //#include <ESP8266HTTPClient.h>

// Set these to run example.
#define FIREBASE_HOST "yourproject.firebaseio.com"
#define FIREBASE_AUTH "wecbweicbwvbwivwofowencVYTyu56dod"
#define WIFI_SSID "modem"
#define WIFI_PASSWORD "yourpasscode"


String myString = ""; // complete message from arduino, which consistors of snesors data
char rdata;
String w;
String x;
String y;
String o;
int firstVal, secondVal,thirdVal,fourthVal;


void setup()
{
  // Debug console
  Serial.begin(9600);
  nodemcu.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop()
{
 if (nodemcu.available() > 0 ) 
  {
    rdata = nodemcu.read(); 
    myString = myString+ rdata; 
     Serial.println("recieving");
   Serial.println(myString);
    if( rdata == '\n')
    {
  
String l = getValue(myString, ',', 0);
String m = getValue(myString, ',', 1);
String n = getValue(myString, ',', 2);
String o = getValue(myString, ',', 3);
 
 
 
firstVal = l.toInt();
secondVal = m.toInt();
thirdVal = n.toInt();
fourthVal = o.toInt();
Serial.println(firstVal); //soil mois
Serial.println(secondVal); //temp
Serial.println(thirdVal);   //humid
Serial.println(fourthVal);  //ldr
 
  myString = "";
// end new code
    
 if(firstVal<900)
 {
 w= "Watering the plants status = Watering";
 }
 else
 { w ="Watering the plants status = Not Watering";}
 if(fourthVal>400)
 {x= "LED Status : LED lights are ON";
 }
 else
 {x= "LED Status : LED lights are OFF";
 }
 y = "Temperature = "+m+"°C";
 z= "Humidity = "+n+"%";
Serial.println(y);
Serial.println(z);

Firebase.setString("/Soil_moisture",w);
delay(800); 

Firebase.setString("/Temperature",y);
delay(800); 

Firebase.setString("/Humidity",z);
delay(800); 

Firebase.setString("/Ldr_sensor",x);
//delay(1000); 
    }
   }
      
     if (nodemcu.available() == 0 ) 
    {
  
 Serial.println("not recieving");
 delay(3000);
  }           
}
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
