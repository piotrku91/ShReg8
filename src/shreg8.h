#ifndef SHREG8_H
#define SHREG8_H

  /* 
Shift Register 8 Control Object
Written by: Piotr Kupczyk
v.1.1
Object controls Shift Registers by easy way.

2019-2020
  */

#include <Arduino.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                        CLASS SHREG8 - HEADER                                                                 //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ShReg8
{

//Public variables
public:
  const uint8_t latchPin;
  const uint8_t clockPin;
  const uint8_t dataPin;

//Private variables/objects
private:
  bool SA[8];      // Status array
  struct BitAccess // Bits field
  {
    bool a0 : 1;
    bool a1 : 1;
    bool a2 : 1;
    bool a3 : 1;
    bool a4 : 1;
    bool a5 : 1;
    bool a6 : 1;
    bool a7 : 1;
  };

  union // Anonymous union
  {
    BitAccess Pack;
    uint8_t IntRepresenter;
  };


// Private functions
  inline void LockLatch() { digitalWrite(latchPin, LOW); };
  inline void UnlockLatch() { digitalWrite(latchPin, HIGH); };
  void SA_to_BA(bool PT[8]);
  void BA_to_SA(bool PT[8]);


//Public functions
public:
  void ShiftExec(const bool &Direction = MSBFIRST);
  void PrepareALL(const bool &NewStatus);
  void PrepareOne(const uint8_t &BitPlace, const bool &NewStatus);
  void PrepareIntRepresenter(const uint8_t &NewIntRepresenter);
  inline void PrepareClear() {PrepareALL(false);};

  void MoveLeft(uint8_t BitsAmount);
  void MoveRight(uint8_t BitsAmount);

  void ImportSA(bool External[8]);
  void ExportSA(bool External[8]);
  inline uint8_t GetIntRepresenter() const { return IntRepresenter; };

  // Overloading
  void operator<<(uint8_t BitsAmount);
  void operator>>(uint8_t BitsAmount);

  ShReg8() = delete;
  // Constructor
  ShReg8(int LATCHPIN, int CLOCKPIN, int DATAPIN, bool ClearOnStartup = true) : latchPin(LATCHPIN), clockPin(CLOCKPIN), dataPin(DATAPIN)
  {
    // Setting pins on Arduino
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    if (ClearOnStartup)
    { 
      PrepareClear();
      ShiftExec();
    };
  };


  //Additional functions
void SimpleStep(const int& Value,const int& JumpLevel,const int& StartLevel); // Follow Value and Set shift register from MIN to MAX (prepare only)
void DecimalInc() {IntRepresenter++;}
void DecimalDec() {IntRepresenter--;}
void BitAND_i(const uint8_t& InInteger) {IntRepresenter=(IntRepresenter bitand InInteger); BA_to_SA(SA);}
void BitOR_i(const uint8_t& InInteger) {IntRepresenter=(IntRepresenter bitor InInteger); BA_to_SA(SA);}
void BitXOR_i(const uint8_t& InInteger) {IntRepresenter=(IntRepresenter xor InInteger); BA_to_SA(SA);}
void PrepareOne_MM(const uint8_t &BitPlace, const bool &NewStatus) // Prepare one by shift and mask method
{
   (NewStatus) ? BitOR_i((1 << BitPlace)):BitXOR_i((1 << BitPlace));
}

};


#endif
