#include <ObS.h>
#include <MotionSensor.h>
#include <RGBLeds.h>
#include "AlaLed.h"
#include "Ala.h"
#include <PcIManager.h>
#include <Button.h>
#include <SoftTimer.h>
#include <SimpleTimer.h>

#define Unused 0

//Pins
#define Red 8 //8
#define Green 9
#define Blue 10
#define TrackingLed 13
#define MotionSensonPin 3
#define ButtonPin 2
//---
#define LedSleepDuration 25
#define LoopRate 1000
   
bool cyclingColors = false;

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

int tmp1, tmp2;

void loop() {
    timer.run();
    obs.loop();
    motionSensor->loop();
    rgbLeds->loop();    //does nothing
    
    // if(rgbLeds->ledsOn){
    if(cyclingColors){
        // tmp1 = (tmp1+1)%3;
        // int i = tmp1;
        // while(i--){
        //     Serial.print(".");
        // }
        // Serial.println("");
        obs.sleep((LedSleepDuration-1)/3);
    } else {
        // tmp2 = (tmp2+1)%3;
        // int i = tmp2;
        // while(i--){
        //     Serial.print("x");
        // }
        // Serial.println("");
        obs.sleep(LoopRate);
    }
}

void SignalAndActivateLeds(){
    obs.flashLed(TrackingLed, 3, 150);
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

