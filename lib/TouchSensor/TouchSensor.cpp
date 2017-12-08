#include "TouchSensor.h"

TouchSensor::TouchSensor(int touchSensorPin){
    pin = touchSensorPin;
    pinMode(pin, INPUT); //make that pin an OUTPUT?

    int i = PressTimesHistory_Cardinality;
    while(i--){
        lastPressBeginTimestamp[i] = NULL;
    }
    isPressed = false;
}

//<<destructor>>
TouchSensor::~TouchSensor(){/*nothing to destruct*/}

void TouchSensor::loop(void)
{
    singleTouchDetected = false;
    doubleTouchDetected = false;
    longTouchDetected = false;

    //Single press logic: Wait to make sure it's not a double press, then set single press to true.
    if(waitingForDoublePress){
        if(millis() - lastPressBeginTimestamp[0] >= DoublePress_SecondTouchMaxDelay){
            singleTouchDetected = true;
            logln("[TouchSensor] Single Click");
            waitingForDoublePress = false;
        }
    }

    if(digitalRead(pin) == HIGH && isPressed == false){
        logln("[TouchSensor] Pressed <>");
        
        updateLastPressTimesArray(millis());
        isPressed = true;
    }else if(digitalRead(pin) == LOW && isPressed){
        unsigned long lastPressDuration = millis() - lastPressBeginTimestamp[0];

        //Long button press logic
        if(lastPressDuration >= LongPress_MinPressTime){
            longTouchDetected = true;
            logln("[TouchSensor] Long Press");
        } else {
            if(waitingForDoublePress){
                doubleTouchDetected = true;
                logln("[TouchSensor] Double Click");
                waitingForDoublePress = false;
            } else {
                waitingForDoublePress = true;
            }
        }
        isPressed = false;

        log("[TouchSensor] Released ><  - ");
    #ifdef VerboseTouchSensor
        Serial.println(lastPressDuration);
    #endif
    }
}

void TouchSensor::updateLastPressTimesArray(unsigned long beginPressTimeStamp){
    int i = PressTimesHistory_Cardinality - 1;
    while(i >= 1){
        lastPressBeginTimestamp[i] = lastPressBeginTimestamp[i-1];
        i--;
    }
    lastPressBeginTimestamp[0] = beginPressTimeStamp;
}

void TouchSensor::log(const char* msg){
    #ifdef VerboseTouchSensor
        Serial.print(msg);
    #endif
}

void TouchSensor::logln(const char* msg){
    #ifdef VerboseTouchSensor
        Serial.println(msg);
    #endif
}
