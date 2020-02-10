int pin_number = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_number, OUTPUT); //intentionally not the same pin as led; prevents current from being broken
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 5; i <= 1000; i=i+5) {
    PWM(50, i, 10, pin_number); 
  }
}

void PWM(int dur, int pwr, int prd, int pin) { //dur in ms, pwr from 0 to 1000, prd in us, pin set to 11
  int elapsed = 0;
  do {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pwr*prd);
    digitalWrite(pin, LOW);
    delayMicroseconds((1000-pwr)*prd);
    elapsed = elapsed + prd;
  }while(elapsed < dur);
}
