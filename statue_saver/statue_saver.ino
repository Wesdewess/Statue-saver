#include <Servo.h>
#include<Wire.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int shockSensor = 13;
Servo arms;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     //wake up MPU
  Wire.endTransmission(true);
  Serial.begin(9600);
  arms.attach(10);
  pinMode (shockSensor, INPUT);
}

void loop(){
 //getOrientation();
// printOrientation();

if(digitalRead(shockSensor)==LOW){
  Serial.println("Shock detected");
  armsUp();
  delay(1000);
  armsDown();
}


 
}

void armsUp(){
  arms.write(90);
  Serial.println("arms up");
}
void armsDown(){
  arms.write(0);
  Serial.println("arms down");
}
void getOrientation(){
   Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  //read orientation values
  AcX=Wire.read()<<8|Wire.read();  // 0x3B     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D 
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F 
  GyX=Wire.read()<<8|Wire.read();  // 0x43 
  GyY=Wire.read()<<8|Wire.read();  // 0x45 
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 
}
void printOrientation(){
   //print orientation values
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.println(" | AcZ = "); Serial.print(AcZ);
}

