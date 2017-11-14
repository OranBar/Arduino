#include <ObS.h>
#include <MotionSensor.h>
#include <RGBLeds.h>
#include "AlaLedRgb.h"


#define Unused 7

//Pins
#define Red 0
#define Green 1
#define Blue 2
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

long lastMotion_time = 0;

bool motionDetected = false;

int motionTimesRecord[10];
int motionTimeIndex = -1;

int turnOffSupportLedTime = 0;
bool supportLedOn = false;

void OnMotionDetected(void);
void ToggleSupportLed(bool on);    

ObS obs;//initialize an instance of the OranBar Operating System ObS class, the powerful engine that drives it all.
MotionSensor* motionSensor;
RGBLeds* rgbLeds;
Button* button;

AlaLedRgb rgbStrip;

#ifdef DebugMode
    ISR(WDT_vect) { Sleepy::watchdogEvent(); } // Setup the watchdog
#endif

bool off;

// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!

 
#define FADESPEED 5     // make this higher to slow down
 
// void setup() {
//   pinMode(Red, OUTPUT);
//   pinMode(Green, OUTPUT);
//   pinMode(Blue, OUTPUT);

//   button = new Button(ButtonPin);
//   analogWrite(Red, 0);
//   analogWrite(Green, 0);
//   analogWrite(Blue, 0);
//   off = true;
// }
 
 
// void loop() {
//     button->loop();
//     if(button->buttonWasPressed){
//         off = !off;
//         obs.flashLed(ObS_PIN, 3, 150);
//     }
//     if (off){
//         return;
//     }
//     int r, g, b;

//     // fade from blue to violet
//     for (r = 0; r < 256; r++)
//     {
//         analogWrite(Red, r);
//         delay(FADESPEED);
//     }
//     // fade from violet to red
//     for (b = 255; b > 0; b--)
//     {
//         analogWrite(Blue, b);
//         delay(FADESPEED);
//     }
//     // fade from red to yellow
//     for (g = 0; g < 256; g++)
//     {
//         analogWrite(Green, g);
//         delay(FADESPEED);
//     }
//     // fade from yellow to green
//     for (r = 255; r > 0; r--)
//     {
//         analogWrite(Red, r);
//         delay(FADESPEED);
//     }
//     // fade from green to teal
//     for (b = 0; b < 256; b++)
//     {
//         analogWrite(Blue, b);
//         delay(FADESPEED);
//     }
//     // fade from teal to blue
//     for (g = 255; g > 0; g--)
//     {
//         analogWrite(Green, g);
//         delay(FADESPEED);
//     }
// }

void setup(){
    // Serial.begin(9600);

    // motionSensor = new MotionSensor(MotionSensonPin, OnMotionDetected);
    rgbLeds = new RGBLeds(Red, Green, Blue);
    // button = new Button(ButtonPin);
    // pinMode(MotionSensonPin, INPUT);

    // obs.bootAnim(SignalLed);
    
    analogWrite(Red, 0);
    analogWrite(Green, 0);
    analogWrite(Blue, 0);

    //Init led strip
    /*
    byte pins[] = {Red, Green, Blue};
    rgbStrip.initTLC5940(3,  pins);
    rgbStrip.setAnimation(ALA_FADECOLORSLOOP, 12000, alaPalRgb);
    */
}


void loop() {
    // // if(obs.OnOffButtonLoop()){
    // //     return;
    // // }


    // if(digitalRead(ButtonPin)){
    //     obs.flashLed(ObS_PIN, 1, 150);
        
    //     Serial.println("Common Anode <>");
    //     rgbLeds->setColor(255, 0, 0); // red

    //     obs.sleep(2000); 

    //     Serial.println("Common Catode <>");
    //     rgbLeds->setColor(0, 255, 255); // red

    //     obs.sleep(2000); 

    //     Serial.println("Turning OFF lights ><");

    // }

    // motionSensor->loop();
    // rgbLeds->loop();

    // if(millis() > turnOffSupportLedTime && supportLedOn){
    //     Serial.print("Time ");
    //     Serial.print(turnOffSupportLedTime);
    //     Serial.println("[Turning LED off] ");
    //     //ToggleSupportLed(false);
    // }
    
    // // if(digitalRead(MotionSensonPin) == HIGH){
    // //     Serial.println("Motion Detected");
        
    // //     if(motionDetected == false){
    // //         Serial.println("MOTION");
    // //         OnMotionDetected();
    // //         motionDetected = true;
    // //         obs.sleep(6000); //6000 + 2000 = 8000. i've never seen a 8000.
    // //     }
    // // }
    // // else
    // // {
    // //     if(motionDetected){ motionDetected = false; }
    // // }

    // obs.sleep(LoopRate);
}



void OnMotionDetected(){
    lastMotion_time = millis();
    Serial.println(lastMotion_time);
    obs.flashLed(TrackingLed, 3, 150);

    // turnOffSupportLedTime = millis() + SupportLedOnTime;
    // Serial.print("Turning led off at ");
    // Serial.println(turnOffSupportLedTime);

    //rgbStrip.runAnimation();
    // Serial.println("Turning ON lights <>");
    // rgbLeds->setColor(0, 255, 255); // aqua

    obs.sleep(2000); 

    // rgbLeds->turnOff();
    // Serial.println("Turning OFF lights ><");

    
//    cycleColors();

    //ToggleSupportLed(true);
}

void ToggleSupportLed(bool onOrOff){
    digitalWrite(SupportLed, onOrOff);
    supportLedOn = onOrOff;
}

void cycleColors(void){
    
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
