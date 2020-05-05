#include "Adafruit_Si7021.h"
#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float humid, temp;
float maxhumid, minhumid, maxtemp, mintemp;
int state = 1;
long t, t0;

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
  t0 = millis();
  pinMode(7, OUTPUT);

  while(t - t0 < 300000) {
    humid = sensor.readHumidity();
    digitalWrite(7, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Humidity");
    lcd.setCursor(0, 1);
    lcd.print(humid);
    lcd.setCursor(5, 1);
    lcd.print("%");
    Serial.print("Humidity:    ");
    Serial.println(humid, 2);
    digitalWrite(7, LOW);
    delay(1000);
    t = millis();
  }
  Serial.println("Data complete.");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Data complete.");
}

void loop() {

}
