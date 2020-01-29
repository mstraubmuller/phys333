int pin_number = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_number, OUTPUT); //intentionally not the same pin as led; prevents current from being broken
}

void loop() {
  // put your main code here, to run repeatedly:
  test_PWM(250, 250, 10, pin_number);
  delay(250);
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
