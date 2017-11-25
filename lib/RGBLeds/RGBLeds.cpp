#include "RGBLeds.h"

//#define COMMOD_ANODE



RGBLeds::RGBLeds(int redOutputPin, int greenOutputPin, int blueOutputPin){
    redPin = redOutputPin;
    pinMode(redPin, OUTPUT);

    greenPin = greenOutputPin;
    pinMode(greenPin, OUTPUT);

    bluePin = blueOutputPin;
    pinMode(bluePin, OUTPUT);

    turnOff();
}

RGBLeds::~RGBLeds(){/*Nothing to do here*/}

void RGBLeds::loop(void){

}

void RGBLeds::setColor(int redValue, int greenValue, int blueValue){
    color = AlaColor(redValue, greenValue, blueValue);
    setColor(color);
}

void RGBLeds::setColor(AlaColor colorToSet){
    analogWrite(redPin, colorToSet.r);
    analogWrite(greenPin, colorToSet.g);
    analogWrite(bluePin, colorToSet.b);
    
    color = colorToSet;
    if(color.r + color.b + color.g == 0){
        ledsOn = false;
    } else {
        ledsOn = true;
    }
}

void RGBLeds::turnOff(){
    stopLerping = true;
    setColor(0,0,0);
}

//---------------
