/* 
Quiz 1 Problem 3 - Driving a fan using 3 power lines
Matthew Straubmuller

The greatest hurdle to overcome in this question is how to multithread and keep each line running at the same time in case the fan needs to switch
This could be mitigated by the states only lasting 500 us - small enough time for a capacitor to make up for the difference in voltage
Under this regime, the longest time any given pin has without power is 1 ms; not negligibly small, but it is within the visual limit
Motor acts as an inductor; the rapid change in voltage may result in induced reverse currents, so a diode should be installed to block current from flowing into the arduino and prevent pin damage
*/

int pin_1 = 2;
int pin_2 = 4;
int pin_3 = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_1, OUTPUT); //low pin
  pinMode(pin_2, OUTPUT); //medium pin
  pinMode(pin_3, OUTPUT); //high pin
}

void loop() { 
  // put your main code here, to run repeatedly:
  fast_PWM(0.5, 200, 0.00025, pin_1);
  fast_PWM(0.5, 400, 0.00025, pin_2);
  fast_PWM(0.5, 750, 0.00025, pin_3);
  //code then loops, period of 1.5 ms
}

void fast_PWM(int dur, int pwr, int prd, int pin) { //dur in ms, pwr from 0 to 1000, prd in ms, pin set to 11
  int elapsed = 0;
  do {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pwr*prd); //arduino can safely handle period down to 0.05us; duration is fixed to 500 us in this example
    digitalWrite(pin, LOW);
    delayMicroseconds((1000-pwr)*prd); 
    elapsed = elapsed + prd;
  }while(elapsed < dur); //duration is 0.5ms, therefore period should be very small; 1000 periods should be within ~250us therefore 0.25 us (0.00025 ms) period
  return;
}
