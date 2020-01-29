int pin_number = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_number, OUTPUT); //same pin as default led; good for ensuring problem is hardware
}

void loop() {
  // put your main code here, to run repeatedly:
  test_PWM(250, 1000, 10, pin_number); //full power, quarter of a second
  delay(1000);
  test_PWM(500, 500, 10, pin_number); //half power, half a second
  delay(1000);
}

void test_PWM(int dur, int pwr, int prd, int pin) {
  int elapsed = 0;
  do {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pwr*prd); //pwr*prd = how many microseconds light is on
    digitalWrite(pin, LOW);
    delayMicroseconds((1000-pwr)*prd); //how many microseconds the light is off
    elapsed = elapsed + 1000*prd;
  }while(elapsed < dur); //expected duration is under 1000; not currently sanitized
}
