//#include <Arduino_Threads.h>
#include <Arduino_LSM9DS1.h>
#include <math.h>

#define WAIT_TIME 500

//Variable Definitions
float x, y, z;
int angleX = 0;
int angleY = 0;
unsigned long previousMillis = 0;

//Function Headers
void calculate_angle();
void Read_Stretch_Band();

void setup() {
  Serial.begin(9600);
  while (!Serial);

  //IMU_sensor.start();
  //stretch_sensor.start();
  //IMUSensor.start();
  //StretchSensor.start();
  //EMGSensor.start();

}

void loop() {
  calculate_angle();

}


void Read_Stretch_Band(){

  int sensorValue = analogRead(A6);

  float voltage = (sensorValue / 1023.0) * 5.0;

  float resistance = 10000.0 * ((5.0 / voltage) - 1.0);

  Serial.print("ADC: ");
  Serial.print(sensorValue);
  
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  
  Serial.print(" | Resistance: ");
  Serial.println(resistance);
}


void calculate_angle() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= WAIT_TIME) {
    if (IMU.accelerationAvailable()) {
    previousMillis = currentMillis;

    IMU.readAcceleration(x, y, z);

    // Calculate tilt angles in degrees
    angleX = atan2(x, sqrt(y * y + z * z)) * 180 / PI;
    angleY = atan2(y, sqrt(x * x + z * z)) * 180 / PI;

    Serial.print("ANGLE,");
    Serial.print(angleX, 2);
    Serial.print(",");
    Serial.println(angleY, 2);
    }
    
  }
}