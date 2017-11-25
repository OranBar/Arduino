#pragma once

#include <Arduino.h>
#include "Ala.h"

class RGBLeds {
    public:
        RGBLeds(int redOutputPin, int greenOutputPin, int blueOutputPin);
        ~RGBLeds();
        void loop(void);
        void setColor(int redValue, int greenValue, int blueValue);
        void setColor(AlaColor color);

        void turnOff(void);
        AlaColor color;
        bool ledsOn;

    private:
        int redPin, greenPin, bluePin;
};
