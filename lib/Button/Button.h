#include <Arduino.h>


#define VerboseButton

class Button {
    public:
        Button(int buttonPin);
        ~Button();
        void loop(void);
        int getCurrentPressDuration(void);
        bool buttonWasPressed;
        bool buttonDown;
        bool buttonWasReleased;
        long lastPressTime;
        int lastPressDuration;

    private:
        int pin;
};