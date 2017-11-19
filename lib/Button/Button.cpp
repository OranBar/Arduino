#ifndef Button_h
#define Button_h
#include "Button.h"

Button::Button(int buttonPin){
    pin = buttonPin;
    pinMode(pin, OUTPUT); //make that pin an OUTPUT
    buttonWasPressed = false;
    buttonWasReleased = false;
    lastPressTime = 0;
    lastPressDuration = 0;
}

//<<destructor>>
Button::~Button(){/*nothing to destruct*/}

void Button::loop()
{
    if(buttonWasPressed){
        buttonWasPressed = false;
    }
    if(buttonWasReleased){
        buttonWasReleased = false;
    }

    if(digitalRead(pin)){
        if(buttonDown == false){
            buttonDown = true;
            buttonWasPressed = true;
            lastPressTime = millis();
            #ifdef VerboseButton
                Serial.println("Button Pressed <>");
            #endif
        }
    } else {
        if(buttonDown){
            buttonDown = false;
            buttonWasReleased = true;
            lastPressDuration = millis() - lastPressTime;
            #ifdef VerboseButton
                Serial.println("Button Released ><");
                Serial.print("press duration was");
                Serial.println(lastPressDuration);
            #endif
        }
    }
}

int Button::getCurrentPressDuration(void){
    if(buttonDown){
        return millis() - lastPressTime;
    } else {
        return 0;
    }
}
#endif