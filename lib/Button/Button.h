#pragma once

#include <Arduino.h>
#include "Obs.h"

#define VerboseButton

class Button {
    public:
        Button(int buttonPin, void (*onButtonClickFunc)(int pressDuration));
        ~Button();
        void onButtonRising(void);

    private:
        int pin;
        unsigned long lastPressTime;
        bool buttonPressed;
        void (*onButtonClick)(int);
};
