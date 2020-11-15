  #include "shreg8.h"

  /* 
Shift Register 8 Control Object
Written by: Piotr Kupczyk
v.1.1
Object controls Shift Registers by easy way.

2019-2020
  */
 
  void setup()
  {
     
  }

ShReg8 DebugLEDs(8,9,11);
 

  void loop()
  {
      delay(550);

 DebugLEDs.PrepareOne(2,false);
 DebugLEDs.ShiftExec();

      delay(550);

 DebugLEDs.PrepareOne(2,true);
 DebugLEDs.ShiftExec();
  
  }
