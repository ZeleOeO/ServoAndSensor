
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define DHTTYPE DHT11
#define DHTPIN 2
#define soilPin A0
#define lightPin A1
#define pumpPin 3
int soilValue;
float temperature;
float humidity;
int lightValue;
int doOnce = 1;
DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  pinMode(pumpPin, OUTPUT); 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  soil();
  temp();
  light(); // I didn't do anything with my Light Value
  delay(500);
  if (doOnce == 1)
  {
    LCD(temperature,humidity);
  }
}
  
  

void soil() {
  soilValue = analogRead(soilPin);
  if (soilValue <= 500) {
    digitalWrite(pumpPin, LOW);
    lcd.setCursor(0,1);
    lcd.print("PUMP OFF ");
    delay(50);
  }
  else if (soilValue >= 750) {
    digitalWrite(pumpPin, HIGH);
    lcd.setCursor(0,1);
    lcd.print("PUMP ON");
    delay(50);
  }
}

void temp() {
    delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    doOnce = 0;
    lcd.setCursor(0,0);
    lcd.print("ERR reading TEMP");
  }
  else {
    doOnce = 1;
    temperature = event.temperature;
    
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    doOnce = 0;
    lcd.setCursor(0,1);
    lcd.print("ERR reading HUMD");
  }
  else {
    doOnce = 1;
    humidity = event.relative_humidity;

  }
}

void light() {
  lightValue = analogRead(lightPin);
  Serial.print("Light: ");
  Serial.println(lightValue); 
}

void LCD(float Temp ,float Humid) 
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TM:");
  lcd.print(Temp);
  lcd.setCursor(9,0);
  lcd.print("HM:");
  lcd.print(Humid);

}
