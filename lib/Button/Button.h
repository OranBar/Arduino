#include <Arduino.h>


#define VerboseButton

class Button {
    public:
        Button(int buttonPin);
        ~Button();
        void loop(void);
        bool buttonWasPressed;
        bool buttonDown;
        bool buttonWasReleased;
        int lastPressTime;
        int lastPressDuration;
        
    private:
        int pin;
};