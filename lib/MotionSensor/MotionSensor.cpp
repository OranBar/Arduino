#include "MotionSensor.h"

int pin;
bool wasMotionDetected;
int lastMotionTimestamp;
void (*OnMotionDetected)(void);

MotionSensor::MotionSensor(int outputPin, void (*onMotionDetected)(void)){
    pinMode(outputPin, INPUT);
    pin = outputPin;
    OnMotionDetected = onMotionDetected;
}

MotionSensor::~MotionSensor(){/*nothing to do here*/}

void MotionSensor::loop(){
    if(digitalRead(pin) == HIGH){
        // #ifdef VerboseMotionSensor
        //     Serial.println("Motion Detected");
        // #endif
        if(wasMotionDetected == false){
            #ifdef VerboseMotionSensor
                Serial.println("MOTION");
            #endif
            (*OnMotionDetected)();
            wasMotionDetected = true;
            lastMotionTimestamp = millis();
        }
    }
    else
    {
        if(wasMotionDetected){ wasMotionDetected = false; }
    }
}
