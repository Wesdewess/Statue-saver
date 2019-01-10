 int CLK = 9;  // Pin 9 to clk on encoder
 int DT = 8;  // Pin 8 to DT on encoder
 int SW = 7; //button
 int RotPosition = 0; 
 int rotation;  
 int value;

 boolean LeftRight;
 void setup() { 
   Serial.begin (9600);
   pinMode (CLK,INPUT);
   pinMode (DT,INPUT);
   pinMode(SW,INPUT);
   rotation = digitalRead(CLK);   
 } 
 void loop() { 
   value = digitalRead(CLK);
   
   if(digitalRead(SW) == LOW){
    Serial.println("clicked");
   }
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
     // this will print in the serial monitor.
     
   } 
   rotation = value;
 }
