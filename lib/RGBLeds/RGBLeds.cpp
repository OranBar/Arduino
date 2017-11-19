#include "RGBLeds.h"

//#define COMMOD_ANODE

RGBLeds::RGBLeds(int redOutputPin, int greenOutputPin, int blueOutputPin){
    redPin = redOutputPin;
    pinMode(redPin, OUTPUT);

    greenPin = greenOutputPin;
    pinMode(greenPin, OUTPUT);

    bluePin = blueOutputPin;
    pinMode(bluePin, OUTPUT);
}

RGBLeds::~RGBLeds(){/*Nothing to do here*/}

void RGBLeds::loop(void){

}

void RGBLeds::setColor(int redValue, int greenValue, int blueValue){
// #ifdef COMMON_ANODE
//     red = 255 - red;
//     green = 255 - green;
//     blue = 255 - blue;
// #else
    red = redValue;
    green = greenValue;
    blue = blueValue;
// #endif

    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}

void RGBLeds::turnOff(){
    setColor(0,0,0);
    // Color color;
    AlaColor color = new AlaColor(0,0,0);
    
}