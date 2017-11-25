#include <ObS.h>
#include <MotionSensor.h>
#include <RGBLeds.h>
#include "AlaLed.h"
#include "Ala.h"
#include <PcIManager.h>
#include <Button.h>
#include <SoftTimer.h>

#define Unused 7

//Pins
#define Red 4 //8
#define Green 5
#define Blue 6
#define TrackingLed 13
#define MotionSensonPin 3
#define SupportLed Unused
#define ButtonPin 2
//---
#define LedSleepDuration 25
#define SupportLedOnTime 5000 
#define LoopRate 25
   
bool activateLeds = false;

ObS obs;//initialize an instance of the OranBar Operating System ObS class, the powerful engine that drives it all.
MotionSensor* motionSensor;
RGBLeds* rgbLeds;

AlaLed rgbStrip;
SimpleTimer timer;

void SignalAndActivateLeds(void);
void cycleColors(void);
void lerpToColor(AlaColor end, int totDuration);
void lerpToColorStep(void);
void stopLerp(int pressDuration);

AlaColor lerpColor(AlaColor min, AlaColor max, float t);
int lerpInt(int min, int max, float t);
float lerpFloat(float min, float max, float t);

//Button Setup
Button* button;
void pin3Interrupt(){
    button->onButtonRising();
    obs.flashLed(ObS_PIN, 1, 500); 
}

void setup(){
    attachInterrupt(1, pin3Interrupt, RISING); 
    button = new Button(ButtonPin, stopLerp);   
//Button Setup complete 

    Serial.begin(9600);
    motionSensor = new MotionSensor(MotionSensonPin, SignalAndActivateLeds);
    rgbLeds = new RGBLeds(Red, Green, Blue);

    obs.bootAnim(ObS_PIN);
}

void loop() {
    timer.run();
    obs.loop();
    motionSensor->loop();
    rgbLeds->loop();    //does nothing
    
    if(rgbLeds->ledsOn){
        obs.sleep((LedSleepDuration-1)/2);
    } else {
        obs.sleep(LoopRate);
    }
}

void SignalAndActivateLeds(){
    obs.flashLed(TrackingLed, 3, 150);
    cycleColors();
}

//Lerp to Color functions ---------------------------------
AlaColor endColor;
float currLerpDuration;
float t;
int lerpTimerId;
#define NoOfColors 8
AlaColor colors[NoOfColors];
int lerpDurations[NoOfColors];
int index;

void cycleColors(){
    AlaColor tmpC[] = {
        AlaColor(255, 0, 0),
        AlaColor(0, 255, 0),
        AlaColor(0, 0, 255),
        AlaColor(0, 255, 255), 
        AlaColor(255, 255, 255),
        AlaColor(255, 0, 255), 
        AlaColor(255, 0, 0), 
        AlaColor(0, 0, 0)
    };
    int i = NoOfColors;
    while(--i){
        colors[i] = tmpC[i];
    }

    int tmpI[] ={
        3000,
        3000,
        3000,
        3000,
        6000,
        3000,
        3000
    };
    i = NoOfColors;
    while(--i){
        lerpDurations[i] = tmpI[i];
    }
    // *lerpDurations = *tmpI;

    index = 0;

    lerpToColor(colors[0], lerpDurations[0]);
}

void lerpToColor(AlaColor end, int totDuration){
    t = 0;
    endColor = end;
    currLerpDuration = totDuration;
    lerpToColorStep();

}

void lerpToColorStep(){
    if(t >= 1 ){
        if(index+1 < NoOfColors){
            index++;
            obs.flashLed(ObS_PIN, 2, 150); 
            lerpToColor(colors[index], lerpDurations[index]);
            Serial.print("Next color: ");
            Serial.print(colors[index].r);
            Serial.print(" ");
            Serial.print(colors[index].g);
            Serial.print(" ");
            Serial.print(colors[index].b);
            Serial.println("");

            Serial.print("Next duration: ");
            Serial.print(lerpDurations[index]);
        } 
        return;
    }

    AlaColor newColor = rgbLeds->color.interpolate(colors[index], t);
    rgbLeds->setColor(newColor);

    t += LedSleepDuration / currLerpDuration; 
    
    lerpTimerId = timer.setTimeout(LedSleepDuration, lerpToColorStep);
}

void stopLerp(int pressDuration){
    timer.deleteTimer(lerpTimerId);
    rgbLeds->turnOff();
}
//-------------------------------
