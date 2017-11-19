#include <Arduino.h>


#define VerboseMotionSensor

class MotionSensor {
    public:
        MotionSensor(int outputPin, void (*onMotionDetected)(void));
        ~MotionSensor();
        void loop(void);
        bool wasMotionDetected;
        long lastMotionTimestamp;
        
    private:
        int pin;
        void (*OnMotionDetected)(void);
};