/* DisplaysController.h
* Controls the 2 7-segment displays
*/
#ifndef DisplaysController_h
#define DisplaysController_h

#include <Arduino.h>
//Display digit #1 pins
#define D1_SA 10 //Atmega328p pin: 16
#define D1_SB 11 //17
#define D1_SC 12 //18
#define D1_SD 13 //19
#define D1_SE A1 //24
#define D1_SF A2 //25
#define D1_SG A3 //26

//Display digit #2 pins
#define D2_SA 4  //6
#define D2_SB 5  //11
#define D2_SC 6  //12
#define D2_SD 7  //13
#define D2_SE 8  //14
#define D2_SF 9  //15
#define D2_SG A0 //23
class DisplaysController
{
public:
    byte displays = 2;
    byte totalSegments = 14;

    void SetupDisplays(void);
    void StartupAnimation(void);
    void WriteNumber(byte n);
    void ClearDisplay(byte display);
    void BlinkNumber(byte n, int msFrequency);

private:
    ///Write functions: write a certain number on a specified display(#1 = 0, #2 = 1)
    void WriteDigit(byte disp, byte n);
    void WriteZero(byte n);
    void WriteOne(byte n);
    void WriteTwo(byte n);
    void WriteThree(byte n);
    void WriteFour(byte n);
    void WriteFive(byte n);
    void WriteSix(byte n);
    void WriteSeven(byte n);
    void WriteEight(byte n);
    void WriteNine(byte n);
};
#endif
