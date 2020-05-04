int pin_number = 11;
int sinevalue[16];

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_number, OUTPUT); // intentionally not the same pin as led; prevents current from being broken
  // index 64 sine calculations
  int j = 0;
  for(float i = 0; i < TWO_PI; i+=PI/8) {
    sinevalue[j] = 8*sin(i)+8; // rounds off decimals when converting to int
    j++;
  }
}

void loop() {
  int t0 = millis();
  int t = t0;
  /*do {
    PWMAudio(1, 1, pin_number); // sin is cyclic; hypothetical sinevalue[max] should be equivalent to sinevalue[0]
                                // dur*max in this function gives the period of one waveform
                                // acts as an FM loop - investigate further!!
    t = millis()-t0;
  }while(t < 1000);
  t0 = millis();
  do {
    PWMAudio(1, 2, pin_number);
    t = millis()-t0;
  }while(t < 1000);
  t0 = millis();
  do {
    PWMAudio(1, 3, pin_number);
    t = millis()-t0;
  }while(t < 1000);*/
  //t0 = millis();
  /*do {
    PWMAudio(1, 4, pin_number); //higher frequencies inaudible
    PWMAudio(1, 1, pin_number);
    t = millis()-t0;
  }while(t < 1000);
  t0 = millis();
  do {
    PWMAudio(1, 5, pin_number);
    PWMAudio(1, 1, pin_number);
    t = millis()-t0;
  }while(t < 1000);
  do {
    PWMAudio(1, 6, pin_number); // sin is cyclic; hypothetical sinevalue[max] should be equivalent to sinevalue[0]
    PWMAudio(1, 1, pin_number); // dur*max in this function gives the period of one waveform
                                // acts as an FM loop - investigate further!!
    t = millis()-t0;
  }while(t < 1000);
  t0 = millis();
  do {
    PWMAudio(1, 7, pin_number);
    PWMAudio(1, 1, pin_number);
    t = millis()-t0;
  }while(t < 1000);
  t0 = millis();
  do {
    PWMAudio(1, 8, pin_number);
    PWMAudio(1, 1, pin_number);
    t = millis()-t0;
  }while(t < 1000);
  t0 = millis();
  do {
    PWMAudio(1, 9, pin_number);
    PWMAudio(1, 1, pin_number);
    t = millis()-t0;
  }while(t < 1000);
  t0 = millis();
  do {
    PWMAudio(1, 10, pin_number);
    PWMAudio(1, 1, pin_number);
    t = millis()-t0;
  }while(t < 1000);
  do {
    PWMAudio(1, 11, pin_number);
    PWMAudio(1, 1, pin_number);
    t = millis()-t0;
  }while(t < 1000);
  t0 = millis();
  do {
    PWMAudio(1, 12, pin_number);
    PWMAudio(1, 1, pin_number);
    t = millis()-t0;
  }while(t < 1000);
  t0 = millis();
  */do {
    PWMAudio(1, 4, pin_number);
    t = millis()-t0;
  }while(t < 1000);
  t0 = millis(); //lower frequencies inaudbile
  /*do {
    PWMAudio(1, 14, pin_number);
    t = millis()-t0;
  }while(t < 1000);
  t0 = millis();
  do {
    PWMAudio(1, 15, pin_number);
    t = millis()-t0;
  }while(t < 1000);*/
    
}

void PWMAudio(int dur, int prd, int pin) { // dur in ms, pwr from 0 to 10, prd in us, pin set to 11
  for(int i = 0; i < 16; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(sinevalue[i]*prd);
    digitalWrite(pin, LOW);
    delayMicroseconds((16-sinevalue[i])*prd);
  }
}
