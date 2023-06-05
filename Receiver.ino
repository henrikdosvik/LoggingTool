// Speed receiver V4

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 7);
const uint64_t pipe1 = 0xF0F0F0F0AA;
const uint64_t pipe2 = 0xF0F0F0F066;
const uint64_t pipe3 = 0xF0F0F0F0A1;

struct sensor
{
  int force;
  int angle;
  byte sensorNum;
};

sensor sensorData;
int PoleFL;
int PoleFR;
int AngleFL;
int AngleFR;

void setup() {
  Serial.begin(250000);
  radio.begin();
  radio.openReadingPipe(1, pipe1);
  radio.openReadingPipe(2, pipe2);
  radio.openReadingPipe(3, pipe3);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  Serial.print("Start:");
  delay(1000);

}

void loop() {
  if (radio.available()) {
    radio.read(&sensorData, sizeof(sensorData));
    write_sensor_data();
    radio.read(&sensorData, sizeof(sensorData));
    write_sensor_data();
   
    Serial.print(PoleFL);
    Serial.print(", ");
    Serial.print(PoleFR);
    Serial.print(", ");
    Serial.print(AngleFL);
    Serial.print(", ");
    Serial.println(AngleFR);
  }
}

void write_sensor_data() {
  if(sensorData.sensorNum == 1)
  {
    PoleFL = sensorData.force;
    AngleFL = sensorData.angle;
  }
  if(sensorData.sensorNum == 2)
  {
    PoleFR = sensorData.force;
    AngleFR = sensorData.angle;
  }
}
