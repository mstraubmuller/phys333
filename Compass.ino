#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <LiquidCrystal.h>

LSM9DS1 imu;
#define PRINT_CALCULATED
#define PRINT_SPEED 250 //250 ms between prints

//data taken from Rochester, MN; 44* 1' 51" N, 92* 28' 15" W; calculated to 0* 24' W plus/minus 24'
#define DECLINATION -0.4

void printMag();
void printAttitude(float ax, float ay, float az, float mx, float my, float mz);

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float b;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  if (imu.begin() == false) { //default addresses
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Check wiring; default settings used here will work for an out of the box LSM9DS1.");
    while(1);
  }

  lcd.begin(16, 2);
  pinMode(7, OUTPUT);
}

void loop() {
  imu.readMag(); //only using magnet sensor; updates mx, my, mz vars
  printMag(); //Print "M: mx, my, mz"
  Serial.println();
  //magnetic north appears to be at x = 0?
  float bx = imu.calcMag(imu.mx);
  float by = imu.calcMag(imu.my);
  float bz = imu.calcMag(imu.mz);
  lcd.print(sqrt(bx*bx+by*by+bz*bz));
  if(bx < 0.02 && bx > -0.02 && by > 0.3) {
    Serial.println("Facing west");
    lcd.setCursor(0, 1);
    lcd.print("W");
    digitalWrite(7, HIGH);
  }
  else {
    digitalWrite(7, LOW);
  }
  delay(100);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void printMag() {
  //Serial.print("M: ");
  lcd.setCursor(0, 0);
  lcd.print("M: x");
  lcd.print(imu.calcMag(imu.mx));
  lcd.print(" y");
  lcd.print(imu.calcMag(imu.my));
  lcd.setCursor(3, 1);
  lcd.print("z");
  lcd.print(imu.calcMag(imu.mz));
  lcd.setCursor(10, 1);
  //lcd.print("gauss");
  /*Serial.print(imu.calcMag(imu.mx), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 2);
  Serial.println(" gauss");*/
}
