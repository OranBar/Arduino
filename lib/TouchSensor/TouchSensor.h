#pragma once

#include <Arduino.h>
#include "Obs.h"

#define VerboseTouchSensor

#define DoublePress_SecondTouchMaxDelay 500
#define LongPress_MinPressTime 2000

#define PressTimesHistory_Cardinality 3


class TouchSensor {
    public:
        TouchSensor(int touchSensorPin);
        ~TouchSensor();
        void loop(void);
        bool singleTouchDetected;
        bool doubleTouchDetected;
        bool longTouchDetected;

    private:
        int pin;
        unsigned long lastPressBeginTimestamp[PressTimesHistory_Cardinality];
        unsigned long lastPressDuration;
        void updateLastPressTimesArray(unsigned long bseginPressTimestamp)
};
