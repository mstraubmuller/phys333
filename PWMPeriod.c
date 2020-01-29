int pin_number = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_number, OUTPUT); //same pin as default led; good for ensuring problem is hardware
}

void loop() {
  // put your main code here, to run repeatedly:
  test_PWM(750, 500, 10, pin_number);
  delay(1000);
  test_PWM(250, 100, 10, pin_number);
  delay(1000);
}

void test_PWM(int dur, int pwr, int prd, int pin) {
  int elapsed = 0;
  do {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pwr*prd);
    digitalWrite(pin, LOW);
    delayMicroseconds((1000-pwr)*prd);
    elapsed = elapsed + prd;
  }while(elapsed < dur);
}
