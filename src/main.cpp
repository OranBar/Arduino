#include <ObS.h>

#define Unused 7

//Pins
#define Red 0
#define Blue 1
#define Green 2
#define TrackingLed Unused
#define MotionSensonPin 4
#define SupportLed Unused
#define ButtonPin 6
#define SignalLed 13
#define BootAnimLed 13
//---

#define SupportLedOnTime 5000 

// #define R_Pin 10
// #define G_Pin 11
// #define B_Pin 12

bool booting = true;
long lastMotion_time = 0;

bool motionDetected = false;

int motionTimesRecord[10];
int motionTimeIndex = -1;

int turnOffSupportLedTime = 0;
bool supportLedOn = false;

void OnMotionDetected(void);
void ToggleSupportLed(bool on);    

ObS obs;//initialize an instance of the OranBar Operating System ObS class, the powerful engine that drives it all.

#ifdef DebugMode
    ISR(WDT_vect) { Sleepy::watchdogEvent(); } // Setup the watchdog
#endif

void setup(){
    Serial.begin(9600);
    
    booting = true;
    obs.sleep(500);
    obs.bootAnim(BootAnimLed);
    booting = false;

    obs.sleep(100);
}

void loop(){
    Serial.println("-");
    if(booting) { return; }
    
    //button->loop();
    if(obs.OnOffButtonLoop()){
        return;
    }
    
    digitalWrite(SignalLed, digitalRead(ButtonPin));
    obs.sleep(100);

}

// void setup() {
//     Serial.begin(9600);
//     pinMode(MotionSensonPin, INPUT);
//     pinMode(TrackingLed, OUTPUT);
//     pinMode(SupportLed, OUTPUT);

//     pinMode(BootAnimLed, OUTPUT);   //For Boot Anim

//     BootAnim();
// }

// void loop() {
//     if(off || booting){
//         return; 
//     }

//     if(millis() > turnOffSupportLedTime && supportLedOn){
//         Serial.print("Time ");
//         Serial.print(turnOffSupportLedTime);
//         Serial.println("[Turning LED off] ");
//         ToggleSupportLed(false);
//     }
    
//     if(digitalRead(MotionSensonPin) == HIGH){
//         if(motionDetected == false){
//             Serial.println("Motion Detected");
//             OnMotionDetected();
//             motionDetected = true;
//             //delay(6000); //6000 + 2000 = 8000. i've never seen a 8000.
//         }
//     }
//     else
//     {
//         if(motionDetected){ motionDetected = false; }
//     }

//     sleepForTime(100);
// }


void OnMotionDetected(){
    lastMotion_time = millis();
    Serial.println(lastMotion_time);
    obs.flashLed(MotionSensonPin, 50, 100);

    turnOffSupportLedTime = millis() + SupportLedOnTime;
    Serial.print("Turning led off at ");
    Serial.println(turnOffSupportLedTime);

    ToggleSupportLed(true);
}

void ToggleSupportLed(bool onOrOff){
    digitalWrite(SupportLed, onOrOff);
    supportLedOn = onOrOff;
}