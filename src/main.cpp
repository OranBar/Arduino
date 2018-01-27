#include <ObS.h>
#include <MotionSensor.h>
#include <RGBLeds.h>
#include "AlaLed.h"
#include "Ala.h"
#include <PcIManager.h>
#include <Button.h>
#include <SoftTimer.h>
#include <SimpleTimer.h>
#include <TouchSensor.h>

#define Unused 0

//Pins
#define Red 8 //8
#define Green 9
#define Blue 10
#define TouchSensorPin 7
#define TouchLed 13
#define TrackingLed 13
#define MotionSensonPin 3
// #define ButtonPin 2
//---
#define LedSleepDuration 25
#define LoopRate 300
    
bool cyclingColors = false;

ObS obs;//initialize an instance of the OranBar Operating System ObS class, the powerful engine that drives it all.
MotionSensor* motionSensor;
RGBLeds* rgbLeds;

AlaLed rgbStrip;
SimpleTimer timer;

void SignalAndActivateLeds(void);
void reactivateMotionSensor();
void cycleColors(void);
void lerpToColor(AlaColor end, int totDuration);
void lerpToColorStep(void);
void stopLerp(int pressDuration);

AlaColor lerpColor(AlaColor min, AlaColor max, float t);
int lerpInt(int min, int max, float t);
float lerpFloat(float min, float max, float t);

TouchSensor* touchSensor;

bool deactivated = false;

void setup(){
    touchSensor = new TouchSensor(TouchSensorPin);

    Serial.begin(9600);
    motionSensor = new MotionSensor(MotionSensonPin, SignalAndActivateLeds);
    rgbLeds = new RGBLeds(Red, Green, Blue);

    obs.bootAnim(ObS_PIN);
}

int tmp1, tmp2;
int reactivateMotionSensor_timerId = -1;

void loop() {
    timer.run();
    obs.loop(); //does nothing
    rgbLeds->loop();    //does nothing
    touchSensor->loop();

    if(deactivated == false){
        motionSensor->loop();
    }

    if(touchSensor->singleTouchDetected){
        stopLerp(0);
    }    
    if(touchSensor->doubleTouchDetected){
        SignalAndActivateLeds();
    }   
    if(touchSensor->longTouchDetected){
        deactivated = !deactivated;
        if(deactivated){
            //-----------
            obs.onAndOff(TouchLed, 2000);
            obs.onAndOff(TouchLed, 250);
            //-----------
            
            stopLerp(0);
            int _30_minutes = 1800000;
            reactivateMotionSensor_timerId = timer.setTimeout(_30_minutes, reactivateMotionSensor);
        } else {
            //-----------
            obs.onAndOff(TouchLed, 250);
            obs.onAndOff(TouchLed, 2000);
            //-----------

            if(reactivateMotionSensor_timerId != -1){
                timer.deleteTimer(reactivateMotionSensor_timerId);
                reactivateMotionSensor_timerId = -1;
            }

        }
    }   

    // if(rgbLeds->ledsOn){
    if(cyclingColors){
        obs.sleep((LedSleepDuration-1)/3);
    } else {
        obs.sleep(LoopRate);
    }
}

void reactivateMotionSensor(){
    deactivated = false;
    reactivateMotionSensor_timerId = -1;

    obs.flashLed(ObS_PIN, 6, 50);
    Serial.println("30 minutes are DONE!");
}

void SignalAndActivateLeds(){
    if(rgbLeds->ledsOn == false){
        Serial.println("cycling leds");
        cycleColors();
    } else {
        Serial.println("leds already on");
    }
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
        AlaColor(0, 0, 255), //3
        AlaColor(0, 255, 255), 
        AlaColor(255, 255, 255),
        AlaColor(255, 0, 255), //6
        AlaColor(255, 0, 0), 
        AlaColor(0, 0, 0) //8
    };
    int i = NoOfColors;
    while(i--){
        colors[i] = tmpC[i];
    }

    int tmpI[] ={
        3000,
        3000,
        3000,//3
        3000,
        6000,
        3000,//6
        3000,
        3000//8
    };
    i = NoOfColors;
    while(i--){
        lerpDurations[i] = tmpI[i];
    }

    index = 0;

    cyclingColors = true;
    lerpToColor(colors[0], lerpDurations[0]);
}

void lerpToColor(AlaColor end, int totDuration){
    t = 0;
    endColor = end;
    currLerpDuration = totDuration;
    lerpToColorStep();
}

void lerpToColorStep(){
    //base case
    if(t >= 1 ){
        //if not last, go to next
        if(index+1 < NoOfColors){
            index++;
            lerpToColor(colors[index], lerpDurations[index]);
            Serial.print("going to next color, index is ");
            Serial.println(index);
        } else {
            cyclingColors = false;
        }
        return;
    }

    AlaColor newColor = rgbLeds->color.interpolate(colors[index], t);
    rgbLeds->setColor(newColor);

    t += LedSleepDuration / currLerpDuration; 
    
    lerpTimerId = timer.setTimeout(LedSleepDuration, lerpToColorStep);
}

void stopLerp(int pressDuration){
    cyclingColors = false;
    timer.deleteTimer(lerpTimerId);
    rgbLeds->turnOff();
}
//-------------------------------

