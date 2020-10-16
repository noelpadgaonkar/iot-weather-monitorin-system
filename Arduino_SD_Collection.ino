#include <SD.h>
#include <SPI.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define DHTPIN 8
#define DHTTYPE DHT22

long seconds=00;
long minutes=00;
long hours=00;

int CS_pin = 4;

DHT dht(DHTPIN, DHTTYPE);
File sd_file;

#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(A4, A5);

void setup()  {
  lcd.begin(16, 2); 
  Serial.begin(9600);
  pinMode(CS_pin, OUTPUT);
  //pinMode(RS_pin, OUTPUT);
  dht.begin();
  rtc.begin();
  //rtc.setDOW(THURSDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 00, 00);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(14, 06, 2018);   // Set the date to January 1st, 2014
  
  // SD Card Initialization
  if (SD.begin())  {
    Serial.println("SD card is initialized. Ready to go");
  } 
  else  {
    Serial.println("Failed");
    return;
  }

  sd_file = SD.open("data.txt", FILE_WRITE);

  if (sd_file)  {
    /*Serial.print("Time");
    Serial.print(",");*/
    Serial.print("Date");
    Serial.print("\t\t");
    Serial.print("Time");
    Serial.print("\t\t");
    Serial.print("Humidity");
    Serial.print("\t");
    Serial.println("Temperature_C");
    //Serial.print("\t");
    //Serial.print("Temperature_F");
    //Serial.print(",");
    //Serial.print("Heat_index");
    //Serial.print(",");
    //Serial.println("Rainfall_Status (0 - Rain 1 - No Rain)");

    /*sd_file.print("Time");
    sd_file.print(",");*/
    sd_file.print("Date");
    sd_file.print("\t\t");
    sd_file.print("Time");
    sd_file.print("\t\t");
    sd_file.print("Humidity");
    sd_file.print("\t");
    sd_file.println("Temperature_C");
    //sd_file.print("\t");
    //sd_file.print("Temperature_F");
    //sd_file.print(",");
    //sd_file.print("Heat_index");
    //sd_file.print(",");
    //sd_file.println("Rainfall_Status (0 - Rain 1 - No Rain)");
  }
  sd_file.close(); //closing the file
  
} 

void loop()  {
  screen();
  sd_file = SD.open("data.txt", FILE_WRITE);
  if (sd_file)  {
    senddata();
  }
  // if the file didn't open, print an error:
  else  {
    Serial.println("error opening file");
  }
  delay(120000);
  
}

void screen()
{ 
  float temp = dht.readTemperature()+0.4; //Reading the temperature as Celsius and storing in temp
    float hum = dht.readHumidity();     //Reading the humidity and storing in hum
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("'C");

  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(hum);
  lcd.print("%");
  delay(20000);
}

void senddata()  {
  float rain = digitalRead(7);
  for(long seconds = 00; seconds < 60; seconds=seconds+2)  {
    float temp = dht.readTemperature()+0.4; //Reading the temperature as Celsius and storing in temp
    float hum = dht.readHumidity();     //Reading the humidity and storing in hum
    float fah = dht.readTemperature(true);
    float heat_index = dht.computeHeatIndex(fah, hum);
    

  

    /*sd_file.print(hours);
    sd_file.print(":");
    sd_file.print(minutes);
    sd_file.print(":");
    sd_file.print(seconds);
    sd_file.print(",  ");*/
    sd_file.print(rtc.getDateStr());
    sd_file.print("\t");
    sd_file.print(rtc.getTimeStr());
    sd_file.print("\t");
    sd_file.print(hum);
    sd_file.print("%        \t");
    sd_file.print(temp);
    sd_file.println("'C       \t");
    //sd_file.print(fah);
    //sd_file.print("       ");
    //sd_file.print(heat_index);
    //sd_file.print(",      ");
    //sd_file.println(digitalRead(7));

    /*Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print(":");
    Serial.print(seconds);
    Serial.print(",  ");*/
    Serial.print(rtc.getDateStr());
    Serial.print("\t");
    Serial.print(rtc.getTimeStr());
    Serial.print("\t");
    Serial.print(hum);
    Serial.print("%        \t");
    Serial.print(temp);
    Serial.println("'C       \t");
    //Serial.print(fah);
    //Serial.print(",      ");
    //Serial.print(heat_index);
    //Serial.print(",      ");
    //Serial.println(digitalRead(7));
    

    if(seconds>=58)  {
      minutes= minutes + 1;
    }

    if (minutes>59)  {
      hours = hours + 1;
      minutes = 0;
    }

    sd_file.flush(); //saving the file

    delay(120000);
  }
  
  sd_file.close();   //closing the file
}
