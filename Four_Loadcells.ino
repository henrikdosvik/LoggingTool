//Local receiver x4 load cells
#include <SPI.h>
#include "HX711.h"
#define calibration_factor_1 1500
#define calibration_factor_2 1800
#define calibration_factor_3 1800

int KneeL;
int KneeR;
int Ass;
int Belt;


HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;

void setup() {
  Serial.begin(250000);
  scale1.begin(2, 3); // DOUT = 2, CLK = 3
  scale2.begin(10, 11); // DOUT = 4, CLK = 5
  scale3.begin(6, 7); // DOUT = 6, CLK = 7
  scale4.begin(8, 9); // DOUT = 8, CLK = 9
  scale1.set_scale(calibration_factor_1);
  scale2.set_scale(calibration_factor_1);
  scale3.set_scale(calibration_factor_1);
  scale4.set_scale(calibration_factor_1);
  //scale1.tare(100);
  //scale2.tare(100);  
  //scale3.tare(100);
  //scale4.tare(100);  
}

void loop() {   
    KneeL = scale1.get_units(1), 1;
    KneeR = scale2.get_units(1), 1;
    Ass = scale3.get_units(1), 1;
    Belt = scale4.get_units(1), 1;

    Serial.print(KneeL-3);
    Serial.print(", ");
    Serial.print(KneeR-13);
    Serial.print(", ");
    Serial.print(Ass-15);
    Serial.print(", ");
    Serial.println(Belt-11);
    //delay(50);
  }
