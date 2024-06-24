#include <Arduino.h>
#include <DisplaysController.h>

byte D1Segments[7] = {D1_SA, D1_SB, D1_SC, D1_SD, D1_SE, D1_SF, D1_SG};
byte D2Segments[7] = {D2_SA, D2_SB, D2_SC, D2_SD, D2_SE, D2_SF, D2_SG};

//Display  #2 = 1,#1 = 0,. From right to left.
byte Displays[2][7] = {D1_SA, D1_SB, D1_SC, D1_SD, D1_SE, D1_SF, D1_SG,
                       D2_SA, D2_SB, D2_SC, D2_SD, D2_SE, D2_SF, D2_SG};

unsigned long t = 0;

void DisplaysController::SetupDisplays(void)
{
    for (int i = 0; i <= 6; i++)
    {
        pinMode(D1Segments[i], OUTPUT);
        pinMode(D2Segments[i], OUTPUT);
    }
    for (int i = sizeof(D1Segments); i >= 0; i--)
    {
        pinMode(D2Segments[i], OUTPUT);
        pinMode(D1Segments[i], OUTPUT);
    }
}

void DisplaysController::StartupAnimation(void)
{
    for (int i = 0; i <= 6; i++)
    {
        digitalWrite(D1Segments[i], HIGH);
        digitalWrite(D2Segments[i], HIGH);
        delay(100);
    }
    for (int i = sizeof(D1Segments) - 1; i >= 0; i--)
    {
        digitalWrite(D2Segments[i], LOW);
        digitalWrite(D1Segments[i], LOW);
    }

    digitalWrite(D1Segments[6], HIGH);
    digitalWrite(D2Segments[6], HIGH);
}

void DisplaysController::WriteNumber(byte n)
{
    if (n <= 9)
    {
        WriteZero(1);
        WriteDigit(0, n);
    }
    else if (n >= 10)
    {
        byte digits[2];
        digits[1] = n / 10;
        digits[0] = n % 10;       //The remainder is the last digit. Ex: 8/10 = 0 with remainder of 8; 23/10 = 2 with remainder of 3.
        WriteDigit(0, digits[0]); //Write the #1 digit on the #1 display
        WriteDigit(1, digits[1]);
    }
}

void DisplaysController::WriteDigit(byte disp, byte n)
{
    switch (n)
    {
    case 1:
        WriteOne(disp);
        break;
    case 2:
        WriteTwo(disp);
        break;
    case 3:
        WriteThree(disp);
        break;
    case 4:
        WriteFour(disp);
        break;
    case 5:
        WriteFive(disp);
        break;
    case 6:
        WriteSix(disp);
        break;
    case 7:
        WriteSeven(disp);
        break;
    case 8:
        WriteEight(disp);
        break;
    case 9:
        WriteNine(disp);
        break;
    default:
        WriteZero(disp);
        break;
    }
}

void DisplaysController::ClearDisplay(byte display)
{
    for (int i = 0; i <= 6; i++)
    {
        digitalWrite(Displays[display][i], LOW);
    }
}

void DisplaysController::BlinkNumber(byte n, int msFrequency)
{
    unsigned long currentTime = millis();
    if (currentTime - t >= msFrequency)
    {
        ClearDisplay(0);
        ClearDisplay(1);
        if (currentTime - t >= msFrequency * 2)
        {
            WriteNumber(n);
            t = currentTime;
        }
    }
}

///Write functions: write a certain number on a specified display(#1 = 0, #2 = 1)
void DisplaysController::WriteZero(byte display)
{
    digitalWrite(Displays[display][0], 1);
    digitalWrite(Displays[display][1], 1);
    digitalWrite(Displays[display][2], 1);
    digitalWrite(Displays[display][3], 1);
    digitalWrite(Displays[display][4], 1);
    digitalWrite(Displays[display][5], 1);
    digitalWrite(Displays[display][6], 0);
}

void DisplaysController::WriteOne(byte display)
{
    digitalWrite(Displays[display][0], 0);
    digitalWrite(Displays[display][1], 1);
    digitalWrite(Displays[display][2], 1);
    digitalWrite(Displays[display][3], 0);
    digitalWrite(Displays[display][4], 0);
    digitalWrite(Displays[display][5], 0);
    digitalWrite(Displays[display][6], 0);
}

void DisplaysController::WriteTwo(byte display)
{
    digitalWrite(Displays[display][0], 1);
    digitalWrite(Displays[display][1], 1);
    digitalWrite(Displays[display][2], 0);
    digitalWrite(Displays[display][3], 1);
    digitalWrite(Displays[display][4], 1);
    digitalWrite(Displays[display][5], 0);
    digitalWrite(Displays[display][6], 1);
}

void DisplaysController::WriteThree(byte display)
{
    digitalWrite(Displays[display][0], 1);
    digitalWrite(Displays[display][1], 1);
    digitalWrite(Displays[display][2], 1);
    digitalWrite(Displays[display][3], 1);
    digitalWrite(Displays[display][4], 0);
    digitalWrite(Displays[display][5], 0);
    digitalWrite(Displays[display][6], 1);
}

void DisplaysController::WriteFour(byte display)
{
    digitalWrite(Displays[display][0], 0);
    digitalWrite(Displays[display][1], 1);
    digitalWrite(Displays[display][2], 1);
    digitalWrite(Displays[display][3], 0);
    digitalWrite(Displays[display][4], 0);
    digitalWrite(Displays[display][5], 1);
    digitalWrite(Displays[display][6], 1);
}

void DisplaysController::WriteFive(byte display)
{
    digitalWrite(Displays[display][0], 1);
    digitalWrite(Displays[display][1], 0);
    digitalWrite(Displays[display][2], 1);
    digitalWrite(Displays[display][3], 1);
    digitalWrite(Displays[display][4], 0);
    digitalWrite(Displays[display][5], 1);
    digitalWrite(Displays[display][6], 1);
}

void DisplaysController::WriteSix(byte display)
{
    digitalWrite(Displays[display][0], 1);
    digitalWrite(Displays[display][1], 0);
    digitalWrite(Displays[display][2], 1);
    digitalWrite(Displays[display][3], 1);
    digitalWrite(Displays[display][4], 1);
    digitalWrite(Displays[display][5], 1);
    digitalWrite(Displays[display][6], 1);
}

void DisplaysController::WriteSeven(byte display)
{
    digitalWrite(Displays[display][0], 1);
    digitalWrite(Displays[display][1], 1);
    digitalWrite(Displays[display][2], 1);
    digitalWrite(Displays[display][3], 0);
    digitalWrite(Displays[display][4], 0);
    digitalWrite(Displays[display][5], 0);
    digitalWrite(Displays[display][6], 0);
}

void DisplaysController::WriteEight(byte display)
{
    digitalWrite(Displays[display][0], 1);
    digitalWrite(Displays[display][1], 1);
    digitalWrite(Displays[display][2], 1);
    digitalWrite(Displays[display][3], 1);
    digitalWrite(Displays[display][4], 1);
    digitalWrite(Displays[display][5], 1);
    digitalWrite(Displays[display][6], 1);
}

void DisplaysController::WriteNine(byte display)
{
    digitalWrite(Displays[display][0], 1);
    digitalWrite(Displays[display][1], 1);
    digitalWrite(Displays[display][2], 1);
    digitalWrite(Displays[display][3], 1);
    digitalWrite(Displays[display][4], 0);
    digitalWrite(Displays[display][5], 1);
    digitalWrite(Displays[display][6], 1);
}