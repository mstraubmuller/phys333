 #include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor1 = Adafruit_Si7021();
Adafruit_Si7021 sensor2 = Adafruit_Si7021();
float temp1, temp2, tempDiff, tempAvg;
int LED_pin1 = 12;
int LED_pin2 = 11;
int fan_pin = 10;
int lamp_pin = 9;
bool error = false;

void setup() {
  pinMode(LED_pin1, OUTPUT);
  pinMode(LED_pin2, OUTPUT);
  pinMode(fan_pin, OUTPUT);
  pinMode(lamp_pin, OUTPUT);
  
  Serial.begin(9600);

  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Si7021 test!");
  
  if (!sensor1.begin() || !sensor2.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }

  Serial.print("Found model ");
  switch(sensor1.getModel()) {
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
  Serial.print(sensor1.getRevision());
  Serial.print(")");
  Serial.print(" Serial #"); Serial.print(sensor1.sernum_a, HEX); Serial.println(sensor1.sernum_b, HEX);

    Serial.print("Found model ");
  switch(sensor2.getModel()) {
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
  Serial.print(sensor2.getRevision());
  Serial.print(")");
  Serial.print(" Serial #"); Serial.print(sensor2.sernum_a, HEX); Serial.println(sensor2.sernum_b, HEX);
}

void loop() {
  Serial.print("\tTemperature: ");
  temp1 = sensor1.readTemperature();
  temp2 = sensor2.readTemperature();
  tempDiff = abs(temp1 - temp2);
  if(tempDiff > 0.05) {
    Serial.print("\tLast read disagreement - check sensors");
    digitalWrite(LED_pin1, HIGH); //equipment warning
  }
  else {
    digitalWrite(LED_pin1, LOW); //disable warning
  }
  tempAvg = (temp1 + temp2) / 2.00;
  if(tempAvg > 37.78 && tempAvg < 40.00) {
      digitalWrite(LED_pin2, HIGH); //temp warning
      digitalWrite(lamp_pin, LOW); //turn off lamp
      PWM(30, int(200+600*(1-temp1/40.00)), 10, fan_pin); //turns on fan, fan spins faster with heat
      Serial.print("\tLast read over temperature bounds - check cooling");
      error = true;
  }
  else if(tempAvg >= 40.00) {
      digitalWrite(LED_pin2, HIGH);
      digitalWrite(lamp_pin, LOW); //turn off lamp
      PWM(30, 900, 10, fan_pin); //fan set to fastest setting
      Serial.print("\tLast read significantly over temperature bounds - check cooling");
      error = true;
  }
  else if(tempAvg <= 37.78) {
      digitalWrite(LED_pin2, HIGH);
      digitalWrite(lamp_pin, HIGH); //turn on lamp; stays on until temp goes too high
      Serial.print("\tLast read under temperature bounds - check heating");
      error = true;
  }
  else {
      digitalWrite(LED_pin2, LOW); //disables LED
      digitalWrite(fan_pin, LOW); //disables fan
      if(error){
        error = false;
        Serial.print("\tErrors resolved since last read.");
      }
  }
  Serial.println(" ");
}

void PWM(int dur, int pwr, int prd, int pin) { //dur in ms, pwr from 0 to 1000, prd in ms, pin set to 11
  int elapsed = 0;
  do {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pwr*prd);
    digitalWrite(pin, LOW);
    delayMicroseconds((1000-pwr)*prd);
    elapsed = elapsed + prd;
  }while(elapsed < dur);
}
