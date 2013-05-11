#include "pulseIR.h"
#include "rawIRReader.h"
#include "Stereo2Channel.h"
#include "StereoAFD.h"
#include "StereoDtuningAnt.h"
#include "StereoDualMono.h"
#include "StereoDvD.h"
#include "StereoEnter.h"
#include "StereoFxModeMPXAudio.h"
#include "StereoLaptop.h"
#include "StereoMainMenu.h"
#include "StereoMovie.h"
#include "StereoMusic.h"
#include "StereoMute.h"
#include "StereoPower.h"
#include "StereoPresetMinus.h"
#include "StereoPresetPlus.h"
#include "StereoTuner.h"
#include "StereoTuningMinus.h"
#include "StereoTuningPlus.h"
#include "StereoVideo1.h"
#include "StereoVideo2.h"
#include "StereoVolDown.h"
#include "StereoVolUp.h"
#include "TVBack.h"
#include "TVinput.h"
#include "TVIO.h"
#include "TVMenu.h"
#include "TVMenuBack.h"
#include "TVMenuDown.h"
#include "TVMenuLeft.h"
#include "TVMenuOk.h"
#include "TVMenuRight.h"
#include "TVMenuUp.h"
#include "TVMute.h"
#include "TVVolDown.h"
#include "TVVolUp.h"

// This sketch will send out a canon D50 trigger signal (probably works with most canons)
// See the full tutorial at http://www.ladyada.net/learn/sensors/ir.html
// this code is public domain, please enjoy!

//int IRledPin =  12;    // LED connected to digital pin 12
//int buttonPin = 3;     // footswitch connected to digital #3

byte letter1, letter2;
// The setup() method runs once, when the sketch starts

void setup()   {
    // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);        
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); // pullup on
  
  Serial.begin(9600);
  Serial.println("Start");
}

void loop()                     
{
    if(Serial.available() >= 2){
      letter1 = byte(Serial.read());
      letter2 = byte(Serial.read());
      switch(letter1) {
        case 't':
          switch(letter2) {
            case 'u':
              SendTVVolUp();
              break;
            case 'd':
              SendTVVolDown();
              break;   
            case 'm':
              SendTVMute();
              break;
          }
        break;
        case 's':
          switch(letter2) {
            case 'u':
              SendStereoVolUp();
              break;
            case 'd':
              SendStereoVolDown();
              break;   
            case 'm':
              SendStereoMute();
              break;
          }
         break;   
      }
      Serial.println(char(letter1));
      Serial.println(char(letter2));
   }
   delay(20);
}



