// Speed Transmitter Right

#include "HX711.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <HX711.h>
#include <Wire.h>
#include <MPU6050.h>

#define calibration_factor 38800 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define LOADCELL_DOUT_PIN  2
#define LOADCELL_SCK_PIN  3

MPU6050 mpu;
RF24 radio(8, 7);
//----------------------------------

const uint64_t pipe2 = 0xF0F0F0F066;

struct sensor
{
  int force;
  int angle;
  byte sensorNum;
};
sensor pole;

HX711 scale;

void setup() {
  Serial.begin(250000);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(1600); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  radio.begin();
  radio.openWritingPipe(pipe2);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
   while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
   {
     Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
     delay(500);
   }
  
  pole.sensorNum = 2;

  delay(1000);
  
}

void loop() {
  Vector normAccel = mpu.readNormalizeAccel();
  pole.force = scale.get_units();
  pole.angle = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;;
  Serial.print(pole.force);
  Serial.print(", ");
  Serial.println(pole.angle);
  radio.write(&pole, sizeof(pole));
  //delay(10);

}
