#include <ObS.h>
#include <MotionSensor.h>
#include <RGBLeds.h>
#include "AlaLedRgb.h"
#include "Ala.h"

#define Unused 7

//Pins
#define Red 8
#define Green 9
#define Blue 10
#define TrackingLed 13
#define MotionSensonPin 4
#define SupportLed Unused
#define ButtonPin 6
#define R_Pin 10
#define G_Pin 11
#define B_Pin 12
#define SignalLed 13
//---

#define SupportLedOnTime 5000 
#define LoopRate 1000
   
bool activateLeds = false;

ObS obs;//initialize an instance of the OranBar Operating System ObS class, the powerful engine that drives it all.
MotionSensor* motionSensor;
RGBLeds* rgbLeds;
Button* button;

AlaLedRgb rgbStrip;

#ifdef DebugMode
    ISR(WDT_vect) { Sleepy::watchdogEvent(); } // Setup the watchdog
#endif

bool off;

void OnMotionDetected(void);
void cycleColors(void);
AlaColor lerpColor(AlaColor min, AlaColor max, float t);
int lerpInt(int min, int max, float t);
float lerpFloat(float min, float max, float t);

void setup(){
    Serial.begin(9600);

    motionSensor = new MotionSensor(MotionSensonPin, OnMotionDetected);
    // rgbLeds = new RGBLeds(Red, Green, Blue);
    button = new Button(ButtonPin);
    obs.bootAnim(SignalLed);
    
    // rgbLeds->turnOff();

    //Init led strip
    byte pins[] = {Red, Green, Blue};
    rgbStrip.initPWM(3, pins);
    rgbStrip.setAnimation(ALA_FADECOLORSLOOP, 12000, alaPalRgb);
}


void loop() {
    obs.loop();
    motionSensor->loop();
    // rgbLeds->loop();

    if(activateLeds){
        rgbStrip.runAnimation();
        if(millis() - motionSensor->lastMotionTimestamp > 12000 + 100){
            activateLeds = false;
        }
    }

    obs.sleep(LoopRate - activateLeds * 950);
}

void OnMotionDetected(){
    obs.flashLed(TrackingLed, 3, 150);

    activateLeds = true;
    // cycleColors();
    
    // obs.sleep(2000); 

    // rgbLeds->turnOff();
}

void cycleColors(void){
    // float t;
    // AlaColor min, max;
    // while(t >= 0){
    //     AlaColor color = lerpColor(min, max, t);
    //     // rgbLeds->setColor();

    //     t++; //CHANGEME
    // }

    rgbLeds->setColor(255, 0, 0); // red
    obs.sleep(2000);
    rgbLeds->setColor(0, 255, 0); // green
    obs.sleep(2000);
    rgbLeds->setColor(0, 0, 255); // blue
    obs.sleep(2000);
    rgbLeds->setColor(255, 255, 0); // yellow
    obs.sleep(2000);
    rgbLeds->setColor(80, 0, 80); // purple
    obs.sleep(2000);
    rgbLeds->setColor(0, 255, 255); // aqua
    obs.sleep(2000);
}


///----------------------
AlaColor lerpColor(AlaColor min, AlaColor max, float t){
    AlaColor result = min.interpolate(max, t);
    return result;
}

int lerpInt(int min, int max, float t){
    return (1 - t) * min + t * max;
}

float lerpFloat(float min, float max, float t){
    return (1 - t) * min + t * max;
}
