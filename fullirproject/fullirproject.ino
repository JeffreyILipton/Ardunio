#include "pulseIR.h"
#include "rawIRReader.h"
#include "Stereo2Channel.h"
//#include "StereoAFD.h"
//#include "StereoDtuningAnt.h"
//#include "StereoDualMono.h"
//#include "StereoFxModeMPXAudio.h"
#include "StereoDvd.h"
#include "StereoEnter.h"
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
//#include "TVMenu.h"
//#include "TVMenuBack.h"
//#include "TVMenuDown.h"
//#include "TVMenuLeft.h"
//#include "TVMenuOk.h"
//#include "TVMenuRight.h"
//#include "TVMenuUp.h"
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
      switch(letter1){
        case 't':
          switch(letter2) {
            case 'u':
              SendTVVolUp();
              break;
//            case 'a':
//              SendTVMenu();
//              break;
            case 'b':
              SendStereoMute();
  //            SendTVBack();
              break;
//            case 'c':
//              SendTVMenuBack();
//              break;
            case 'd':
              SendTVVolDown();
              break;   
/*            case 'e':
              SendTVMenuLeft();
              break;
            case 'f':
              SendTVMenuOk();
              break;
            case 'g':
              SendTVMenuRight();
              break;
            case 'h':
              SendTVMenuUp();
              break;
*/          case 'i':
              SendTVInput();
              break;
//            case 'j':
//              SendTVMenuDown();
//              break;
            case 'm':
              SendTVMute();
              break;
            case 'o':
              SendTVOn();
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
            case 'a':
              SendStereo2Channel();
              break;
//            case 'b':
//              SendStereoAFD();
//              break;
//            case 'c':
//              SendStereoDtuningAntCode();
//              break;
            case 'e':
              SendStereoEnter();
              break;
            case 'f':
              SendStereoMusic();
              break;
//            case 'g':
//              SendStereoDualMono();
//              break;
//            case 'h':
//              SendStereoFXMode();
//              break;
//            case 'i':
//              SendStereoMainMenu();
//              break;
//            case 'j':
//              SendStereoDvD();
//              break;
            case 'k':
              SendStereoMovie();
              break;
            case 'l':
              SendStereoLaptop();
              break;
            case 'n':
              SendStereoVideo1();
              break;
            case 'o':
              SendStereoVideo2();
              break;
            case 'p':
              SendStereoPower();
              break;
            case 'v':
              SendStereoPresetMinus();
              break;
            case 'w':
              SendStereoPresetPlus();
              break;
            case 'x':
              SendStereoTuner();
              break;
            case 'y':
              SendStereoTuningMinus();
              break;
            case 'z':
              SendStereoTuningPlus();
              break;
          }
        break;   
      }
      Serial.print(char(letter1));
      Serial.println(char(letter2));
   }
   delay(20);
}

