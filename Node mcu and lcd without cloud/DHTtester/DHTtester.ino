
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
#include <LiquidCrystal_I2C.h>
#define LED D6
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int DESIRED_TEMP = 30;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));


  lcd.begin();

  lcd.backlight();

  dht.begin();

  pinMode(LED, OUTPUT);
}

void loop() {


  float h = dht.readHumidity();
  float t = dht.readTemperature();


  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  if (t < DESIRED_TEMP) {
    
    digitalWrite(LED, HIGH);

  }
  else {
    
    digitalWrite(LED, LOW);

  }


  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));


  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(6, 0);
  lcd.print(t);
  lcd.setCursor(11, 0);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.setCursor(6, 1);
  lcd.print(h);
  lcd.setCursor(11, 1);
  lcd.print(" %");

  delay(2000);
}
