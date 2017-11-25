#include "Button.h"

Button::Button(int buttonPin, void (*onButtonClickFunc)(int pressDuration)){
    if(buttonPin !=2 && buttonPin !=3){
        delay(3000);
        ObS::flashLed(ObS_PIN, 6, 300);
        Serial.println("Please use pin 2 or 3 for the button, to enable interrupts");
    }
    pin = buttonPin;
    pinMode(pin, OUTPUT); //make that pin an OUTPUT?
    onButtonClick = onButtonClickFunc;
}

//<<destructor>>
Button::~Button(){/*nothing to destruct*/}

void Button::onButtonRising()
{
    if(digitalRead(pin)){
        #ifdef VerboseButton
            Serial.println("Button Pressed <>");
        #endif

        lastPressTime = millis();
    }else{
        unsigned long lastPressDuration = millis() - lastPressTime;
        (*onButtonClick)(lastPressDuration);

        #ifdef VerboseButton
            Serial.println("Button Released ><");
            Serial.print("press duration was");
            Serial.println(lastPressDuration);
        #endif
    }
}
