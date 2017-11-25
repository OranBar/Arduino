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
#define AwknowledgementRate 45000 //45 secondi

#include <Arduino.h>



class ObS {
public:
        ObS();
        ~ObS();
        static void digiOn(int pin);
        static void digiOff(int pin);
        static void onAndOff(int pin, int timeMillis);
        static void sleep(int timeMillis);
        void bootAnim(int ledpin);
        static void flashLed(int pin, int times, int delayMillis);      

        // bool OnOffButtonLoop(void);   
        bool loop(void); 

private:
        bool rebooted;  
        bool off;
        // Button* onOffButton;
        long lastTimeOnAwknowledged;
        void periodicOnLed_LoopLogic(void);
};
 
#endif