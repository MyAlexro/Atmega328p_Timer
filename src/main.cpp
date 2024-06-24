#include <Arduino.h>
#include <avr/power.h>
#include "DisplaysController.h"

DisplaysController dc;

byte startStopBttn = 3; //Atmega328p pin: 5
byte resetBttn = 2;     //4
byte buzzerPin = A4;    //27

volatile byte timer = 0;
volatile bool timerToggle = false;
bool hasEverStarted = false;

unsigned long previousTime = 0;
unsigned long previousTime2 = 0;
unsigned long debounceDelay = 250;

//Debug flags
// bool pressedTimerBttn = false;
// bool pressedResetBttn = false;

void ToggleTimerInterrupt()
{
  //Filter out all the little bounces(which get detected as clicks) in the button that happen during/after actual click. Increase debounceDelay to increase tolerance
  if ((millis() - previousTime) >= debounceDelay)
  {
    timerToggle = !timerToggle;
    //pressedTimerBttn = true;
    previousTime = millis();
  }
}

void ResetTimerInterrupt()
{
  if ((millis() - previousTime) >= debounceDelay)
  {
    timer = 0;
    dc.WriteNumber(timer);
    //pressedResetBttn = true;
    previousTime = millis();
  }
}

// void DebugMessages()
// {
//   if (pressedTimerBttn)
//   {
//     Serial.println("Pressed toggle timer button");
//     pressedTimerBttn = false;
//   }
//   if (pressedResetBttn)
//   {
//     Serial.println("Pressed reset time button");
//     pressedResetBttn = false;
//   }
// }

void setup()
{
  //Disable to save power
  power_adc_disable();
  power_spi_disable();
  power_twi_disable(); //(I2C)

  pinMode(startStopBttn, INPUT_PULLUP);
  pinMode(resetBttn, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  // Serial.begin(9600);
  // Serial.println("Serial communication initialized");
  dc.SetupDisplays();
  dc.StartupAnimation();

  attachInterrupt(digitalPinToInterrupt(startStopBttn), ToggleTimerInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(resetBttn), ResetTimerInterrupt, FALLING);
}

void loop()
{
  if (timerToggle == true && timer <= 60)
  {
    if (hasEverStarted == false)
    {
      dc.WriteNumber(timer);
      previousTime2 = millis();
    }
    hasEverStarted = true;

    if (millis() - previousTime2 >= 1000)
    {
      timer++;
      dc.WriteNumber(timer);
      if (timer == 30)
      {
        tone(buzzerPin, 1600, 250);
      }
      if (timer == 60)
      {
        tone(buzzerPin, 1600, 250);
        delay(400);
        tone(buzzerPin, 1600, 250);
        timer++;
      }

      previousTime2 = millis();
    }
  }
  else if (timerToggle == false && hasEverStarted == true)
  {
    dc.BlinkNumber(timer, 500);
  }

  //DebugMessages();
}