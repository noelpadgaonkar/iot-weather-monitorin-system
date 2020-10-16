

#include <ESP8266WiFi.h>

#include "DHT.h"

#include <ESP8266HTTPClient.h>

WiFiClient client;

DHT dht2(2,DHT22);

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;

void setup()
{
  Serial.begin(9600);
   pinMode(D1, INPUT);
    WiFi.disconnect();
   WiFi.begin("LAB","9867780436");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300); 

  }

}


void loop()
{
  

    if (client.connect("api.thingspeak.com",80)) {
      writeAPIKey = "key=JYLKR4WVJ5NPEPOC";
      tsfield1Name = "&field1=10";
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "4UYSS6DSZJW3THQ9";
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += (dht2.readTemperature( )+0.4);
      http.begin(request_string);
      request_string += "key=";
      request_string += "4UYSS6DSZJW3THQ9";
      request_string += "&";
      request_string += "field2";
      request_string += "=";
      request_string += (dht2.readHumidity( ));
      http.begin(request_string);
      request_string += "key=";
      request_string += "4UYSS6DSZJW3THQ9";
      request_string += "&";
      request_string += "field3";
      request_string += "=";
      request_string += digitalRead(D1);
      http.begin(request_string);
      http.GET();
      http.end();
delay(60000);
    }

}
