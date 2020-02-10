int pin_number = 11;
int sinevalue[64];

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_number, OUTPUT); // intentionally not the same pin as led; prevents current from being broken
  // index 64 sine calculations
  int j = 0;
  for(float i = 0; i < TWO_PI; i+=PI/32) {
    sinevalue[j] = 250*sin(i)+250; // rounds off decimals when converting to int
    j++;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 64; i++) {
    PWM(50, sinevalue[i], 10, pin_number); // sin is cyclic; hypothetical sinevalue[64] should be equivalent to sinevalue[0]
                                           // dur*64 in this function gives the period of one waveform
  }
}

void PWM(int dur, int pwr, int prd, int pin) { // dur in ms, pwr from 0 to 1000, prd in us, pin set to 11
  int elapsed = 0;
  do {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pwr*prd);
    digitalWrite(pin, LOW);
    delayMicroseconds((1000-pwr)*prd);
    elapsed = elapsed + prd;
  }while(elapsed < dur);
}
