#include "TouchSensor.h"

TouchSensor::TouchSensor(int touchSensorPin)
    pin = touchSensorPin;
    pinMode(pin, OUTPUT); //make that pin an OUTPUT?

    int i = PressTimesHistory_Cardinality;
    while(i--){
        lastPressBeginTimestamp[i] = NULL;
    }
}

//<<destructor>>
TouchSensor::~TouchSensor(){/*nothing to destruct*/}

void TouchSensor::loop(void)
{
    singleTouchDetected = false;
    doubleTouchDetected = false;
    longTouchDetected = false;

    if(digitalRead(pin)){
        #ifdef VerboseTouchSensor
            Serial.println("TouchSensor Pressed <>");
        #endif
        
        updateLastPressTimesArray(millis());
    }else{
        //If never pressed, let's avoid setting the lastPressDuration to some bullshit amount, and early out
        if(lastPressBeginTimestamp[0] != NULL){ 
            return;
        }

        unsigned long lastPressDuration = millis() - lastPressBeginTimestamp[0];

        if(millis() - lastPressBeginTimestamp[1] <= DoublePress_SecondTouchMaxDelay){
            //Double press logic
            doubleTouchDetected = true;
            #ifdef VerboseTouchSensor
                Serial.println("TouchSensor Double Click");
            #endif
        } else {
            //Single press logic
            singleTouchDetected = true;
            #ifdef VerboseTouchSensor
                Serial.println("TouchSensor Single Click");
            #endif
        }

        //Long button press logic
        if(lastPressDuration >= LongPress_MinPressTime){
            longTouchDetected = true;
             #ifdef VerboseTouchSensor
                Serial.println("TouchSensor Long Press");
            #endif
        }

        #ifdef VerboseTouchSensor
            Serial.println("TouchSensor Released ><");
            Serial.print("press duration was");
            Serial.println(lastPressDuration);
        #endif
    }
}

void TouchSensor::updateLastPressTimesArray(unsigned long beginPressTimeStamp){
    int i = PressTimesHistory_Cardinality - 1;
    while(i-- >=1){
        lastPressBeginTimestamp[i] = lastPressBeginTimestamp[i+1];
    }
    lastPressBeginTimestamp[0] = beginPressTimeStamp;
}
