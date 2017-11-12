#ifndef ObS_h
#define ObS_h

#define DebugMode
#define Verbose

//Pins
#define ObS_PIN 13
//#define OnOffButton Unused
#define OnOffButton 6
//------------------

#define TurnOffTimeout 3000 //3 secondi


#include <Arduino.h>
#include <JeeLib.h>
#include "Button.h"

class ObS {
public:
        ObS();
        ~ObS();
        void digiOn(int pin);
        void digiOff(int pin);
        void onAndOff(int pin, int timeMillis);
        void sleep(int timeMillis);
        void bootAnim(int ledpin);
        void flashLed(int pin, int times, int delayMillis);      

        bool OnOffButtonLoop(void);        

private:
        bool rebooted;  
        bool off;
        Button* onOffButton;
};
 
#endif