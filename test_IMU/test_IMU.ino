#include <Arduino_LSM9DS1.h>

#define MINIMUM_TILT 5    // Threshold for tilt detection in degrees
#define WAIT_TIME 500     // How often to run the code (in milliseconds)


//Variable Definitions
float x, y, z;
int angleX = 0;
int angleY = 0;
unsigned long previousMillis = 0;

//Function Headers
void calculate_angle();

void setup() {
  Serial.begin(9600);
  while (!Serial);

  //Initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
}


void loop() {
  calculate_angle();
}

/*
Calculates angle using accelerometer of IMU and prints it via serial
*/
void calculate_angle() {
  unsigned long currentMillis = millis();

  if (IMU.accelerationAvailable() && (currentMillis - previousMillis >= WAIT_TIME)) {
    previousMillis = currentMillis;

    IMU.readAcceleration(x, y, z);

    // Calculate tilt angles in degrees
    angleX = atan2(x, sqrt(y * y + z * z)) * 180 / PI;
    angleY = atan2(y, sqrt(x * x + z * z)) * 180 / PI;

    // Determine the tilting direction based on angleX and angleY
    if (angleX > MINIMUM_TILT) {  // Tilting up
      Serial.print("Tilting up ");
      Serial.print(angleX);
      Serial.println(" degrees");
    } else if (angleX < -MINIMUM_TILT) {  // Tilting down
      Serial.print("Tilting down ");
      Serial.print(-angleX);
      Serial.println(" degrees");
    }

    if (angleY > MINIMUM_TILT) {  // Tilting left
      Serial.print("Tilting left ");
      Serial.print(angleY);
      Serial.println(" degrees");
    } else if (angleY < -MINIMUM_TILT) {  // Tilting right
      Serial.print("Tilting right ");
      Serial.print(-angleY);
      Serial.println(" degrees");
    }
  }
}