#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

//Constants:
const int flexPin = A0;                 //pin A0 to read analog input

//Variables:
int value; //save analog value


void setup()
{
  
  Serial.begin(9600);                   //Begin serial communication
  
  drv.begin();
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);

}

void loop()
{
  
  value = analogRead(flexPin);         //Read and save analog value from potentiometer
  Serial.println(value);               //Print value

  if (value > 650)
  {
    // set the effect to play
    drv.setWaveform(0, 84);           // play effect 84 
    drv.setWaveform(1, 1);            // play effect 1
    drv.setWaveform(2,0);             // end waveform  

    drv.go();
    delay(500);
  }

  else if (value < 500)
  {
    drv.setWaveform(0, 1);            // play effect

    drv.go();
  }

  else 
  {
    drv.setWaveform(0, 0);            // end all waveforms

    drv.go();
  }
}
