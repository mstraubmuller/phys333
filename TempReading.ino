 #include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  Serial.begin(9600);

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
}

void loop() {
  int time0, time1;
  time0 = millis();
  Serial.print("\tTemperature: ");
  Serial.println(sensor.readTemperature(), 2);
  time1 = millis();
  Serial.print("\tTime elapsed: ");
  Serial.println(time1 - time0);
  delay(1000);
}
