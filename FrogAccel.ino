
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <math.h>

LSM9DS1 imu;

#define LSM9DS1_M	0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG	0x6B // Would be 0x6A if SDO_AG is LOW
#define PRINT_SPEED 10 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

void setup() 
{
  
  Serial.begin(115200);
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  imu.begin();
  //Serial.print("t (sec), ");
  Serial.println("gx (deg/sec), gy (deg/sec), gz (deg/sec), ax (g), ay (g), az (g), mx (gauss), my (gauss), mz (gauss), envelope (arb), audio (arb)");
}

void loop()
{
  // Update the sensor values whenever new data is available
  if ( imu.gyroAvailable() )
  {
    imu.readGyro();
  }
  if ( imu.accelAvailable() )
  {
    imu.readAccel();
  }
  if ( imu.magAvailable() )
  {
    imu.readMag();
  }
  
  if ((lastPrint + PRINT_SPEED) < millis())
  {
    //Serial.print(millis());
    //Serial.print(",");
    printGyro();  // Print "G: gx, gy, gz"
    Serial.print(",");
    printAccel(); // Print "A: ax, ay, az"
    Serial.print(",");
    printMag();   // Print "M: mx, my, mz"
    Serial.print(",");
    Serial.print(log10(analogRead(A0)/1024));
    Serial.print(",");
    Serial.println(log10(analogRead(A1)/1024));
    lastPrint = millis(); // Update lastPrint time
  }
}

void printGyro()
{
  Serial.print(imu.calcGyro(imu.gx), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gy), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gz), 2);
}

void printAccel()
{  
  Serial.print(imu.calcAccel(imu.ax), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.az), 2);
}

void printMag()
{  
  Serial.print(imu.calcMag(imu.mx), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 2);
}
