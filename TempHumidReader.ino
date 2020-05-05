#include "Adafruit_Si7021.h"
#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float humid, temp;
float maxhumid, minhumid, maxtemp, mintemp;
int state = 1;

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  Serial.begin(115200);

  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Si7021 test!");
  
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }

  Serial.print("Found model ");
  switch(sensor.getModel()) {
    case SI_Engineering_Samples:
      Serial.print("SI engineering samples"); break;
    case SI_7013:
      Serial.print("Si7013"); break;
    case SI_7020:
      Serial.print("Si7020"); break;
    case SI_7021:
      Serial.print("Si7021"); break;
    case SI_UNKNOWN:
    default:
      Serial.print("Unknown");
  }
  Serial.print(" Rev(");
  Serial.print(sensor.getRevision());
  Serial.print(")");
  Serial.print(" Serial #"); Serial.print(sensor.sernum_a, HEX); Serial.println(sensor.sernum_b, HEX);

  lcd.begin(16, 2);
  maxtemp = sensor.readTemperature();
  maxhumid = sensor.readHumidity();
  mintemp = maxtemp;
  minhumid = maxhumid;
}

void loop() {
  //four switch statements for displaying four stats
  humid = sensor.readHumidity();
  if(humid > maxhumid) {
    maxhumid = humid;
  }
  else if(humid < minhumid) {
    minhumid = humid;
  }
  temp = sensor.readTemperature();
  if(temp > maxtemp) {
    maxtemp = temp;
  }
  else if(temp < mintemp) {
    mintemp = temp;
  }
  lcd.setCursor(0, 1);
  lcd.print(humid);
  lcd.setCursor(5, 1);
  lcd.print("%");
  lcd.setCursor(10, 1);
  lcd.print(temp);
  lcd.setCursor(15, 1);
  lcd.print("C");
  Serial.print("Humidity:    ");
  Serial.print(humid, 2);
  Serial.print("\tTemperature: ");
  Serial.print(temp, 2);
  Serial.print("\tMax Humidity:    ");
  Serial.print(maxhumid, 2);
  Serial.print("\tMax Temperature: ");
  Serial.print(maxtemp, 2);
  Serial.print("\tMin Humidity:    ");
  Serial.print(minhumid, 2);
  Serial.print("\tMin Temperature: ");
  Serial.println(mintemp, 2);
  if(state == 1) {
      lcd.setCursor(0, 0);
      lcd.print("Min Temp:      ");
      lcd.setCursor(11, 0);
      lcd.print(mintemp);
      lcd.print("C");
      state++;
  }
  else if(state == 2) {
      lcd.setCursor(0, 0);
      lcd.print("Max Temp:      ");
      lcd.setCursor(11, 0);
      lcd.print(maxtemp);
      lcd.print("C");
      state++;
  }
  else if(state == 3) {
      lcd.setCursor(0, 0);
      lcd.print("Min Humid:     ");
      lcd.setCursor(11, 0);
      lcd.print(minhumid);
      lcd.print("%");
      state++;
  }
  else if(state == 4) {
      lcd.setCursor(0, 0);
      lcd.print("Max Humid:     ");
      lcd.setCursor(11, 0);
      lcd.print(maxhumid);
      lcd.print("%");
      state = 1;
  }
  if(minhumid > maxhumid)
    maxhumid = minhumid;
  delay(2000);
}
