#pragma once

#include <Arduino.h>
#include "Ala.h"
#include <SoftTimer.h>
#include <DelayRun.h>
#include <SimpleTimer.h>

class RGBLeds {
    public:
        RGBLeds(int redOutputPin, int greenOutputPin, int blueOutputPin);
        ~RGBLeds();
        void loop(void);
        void setColor(int redValue, int greenValue, int blueValue);
        void setColor(AlaColor color);
        void lerpToColor(AlaColor end, int totDuration);

        void turnOff(void);
        AlaColor color;
        SimpleTimer timer;
        bool ledsOn;

    private:
        int redPin, greenPin, bluePin;
        bool stopLerping;
        AlaColor lerpColor(AlaColor min, AlaColor max, float t);
        
        void lerpToColorStep();
};

// struct Color {
//     public:
//         int red, blue, green;
// } White;
