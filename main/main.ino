#include <Arduino_Threads.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  //IMU_sensor.start();
  //stretch_sensor.start();
  IMUSensor.start();
  StretchSensor.start();

}

void loop() {
  // put your main code here, to run repeatedly:

}
