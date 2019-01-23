#include <Servo.h>
#include<Wire.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

 int CLK = 9;  
 int DT = 8;  
 int SW = 7; //button
 int RotPosition = 0; 
 int rotation;  
 int value;
 boolean LeftRight;
 boolean button = false;
 
int shockSensor = 13;
Servo arm1;
Servo arm2;

int Pos = 99;
int Home = 10;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     //wake up MPU
  Wire.endTransmission(true);
  Serial.begin(9600);
  arm1.attach(10);
  arm1.write(100-Home);
  arm2.attach(11);
  arm2.write(Home);
  pinMode (shockSensor, INPUT);

  pinMode (CLK,INPUT);
   pinMode (DT,INPUT);
   pinMode(SW,INPUT);
   rotation = digitalRead(CLK);   
}

void loop(){
 //getOrientation();
// printOrientation();

if(digitalRead(SW) == LOW){
    Serial.println("clicked");
    if(button==true){
      button = false;
      Serial.println("button = false");
      armsDown();
    }else{
      button = true;
      Serial.println("buton = true");
      RotPosition = Pos; 
    }
    delay(500);
   }

if(button==false){
  if(digitalRead(shockSensor)==LOW){
  Serial.println("Shock detected");
  armsUp();
  delay(1000);
  armsDown();
}
}
if(button==true){
  value = digitalRead(CLK);
  arm1.write(100-Pos);
  arm2.write(Pos);
  if (value != rotation){ // we use the DT pin to find out which way we turning.
     if (digitalRead(DT) != value) {  // Clockwise
       RotPosition ++;
       LeftRight = true;
     } else { //Counterclockwise
       LeftRight = false;
       RotPosition--;
     }
     if (LeftRight){ // turning right will turn on red led.
       Serial.println ("counterclockwise");
     }else{        // turning left will turn on green led.   
       Serial.println("clockwise");
     }
     Serial.print("Encoder RotPosition: ");
     Serial.println(RotPosition);
     if(Pos<102 && Pos>Home){
      Pos = RotPosition;
     
     }
     if(RotPosition>100){
      RotPosition = 99;
     }
     if(RotPosition<Home+2){
      RotPosition = Home+4;
     }
}
rotation = value;
} 
   
 
}

void armsUp(){
  arm1.write(100-Pos);
  arm2.write(Pos);
  Serial.println("arms up");
}
void armsDown(){
  arm1.write(100-Home);
  arm2.write(Home);
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

