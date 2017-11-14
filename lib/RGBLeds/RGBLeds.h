#include <Arduino.h>



class RGBLeds {
    public:
        RGBLeds(int redOutputPin, int greenOutputPin, int blueOutputPin);
        ~RGBLeds();
        void loop(void);
        void setColor(int redValue, int greenValue, int blueValue);
        void turnOff(void);
        int red, green, blue;
        
    private:
        int redPin, greenPin, bluePin;
        
};