#include "ObS.h" //include the declaration for this class




ObS::ObS(){
   pinMode(ObS_PIN, OUTPUT); //make that pin an OUTPUT
   off = rebooted = false;
   onOffButton = new Button(OnOffButton);
}

//<<destructor>>
ObS::~ObS(){/*nothing to destruct*/}

//turn the ObS on
void ObS::digiOn(int pin){
       digitalWrite(pin,HIGH); //set the pin HIGH and thus turn ObS on
}

//turn the ObS off
void ObS::digiOff(int pin){
       digitalWrite(pin,LOW); //set the pin LOW and thus turn ObS off
}

//blink the ObS in a period equal to paramterer -time.
void ObS::onAndOff(int pin, int timeMillis){
       digiOn(pin);                   //turn ObS on
       sleep(timeMillis/2);  //wait half of the wanted period
       digiOff(pin);                  //turn ObS off
       sleep(timeMillis/2);  //wait the last half of the wanted period
}

void ObS::sleep(int timeMillis){
    // delay(timeMillis);
    // Serial.print("Sleeping for ");
    // Serial.println(timeMillis);
    
#ifdef DebugMode
    delay(timeMillis);
#else
    Sleepy::loseSomeTime(timeMillis);
#endif
}

void ObS::bootAnim(int ledpin){
#ifdef Verbose
    Serial.println("Booting >>>>");
#endif
    //Wait a sec before starting
    sleep(500);

    int delays[] = {1200,800,100,100,100,100,50,50,50,50,50,50};
    bool ledOn = false;
    int i = 0;
    int delaysSize = sizeof(delays) / sizeof(delays[0]);
    for(i=0; i < delaysSize ; i++){
        ledOn = !ledOn;
        digitalWrite(ledpin, ledOn);
        sleep(delays[i]);
    }
#ifdef Verbose
    Serial.println("Booting <<<<<");
#endif

    //Wait a sec, for good measure
    sleep(100);

}

void ObS::flashLed(int pin, int times, int delayMillis){
    for(int i=0; i<times; i++){
        if(i!=0) sleep(delayMillis);
        digitalWrite(pin, HIGH);
        sleep(delayMillis);
        digitalWrite(pin, LOW);
    }
}

bool ObS::OnOffButtonLoop(void){
    onOffButton->loop();
    if(onOffButton->buttonWasPressed){
        if(off){
            Serial.println("ReBooting >>>>");
            bootAnim(ObS_PIN);
            sleep(500);
            off = false;
            //lastButtonPressTime = millis();
            Serial.println("ReBooting <<<<");
            rebooted = true;
        }
    }

    if(onOffButton->buttonWasReleased){
        if(off == false && onOffButton->lastPressDuration > TurnOffTimeout){
            if(rebooted){
                rebooted = false;
                return true;
                //Successfully burnt the onOffButton released that would have triggered a turn off
            }
            Serial.println("Turning Off >>>> ");

            //Serial.print("Press time was");
            //Serial.println((millis() - lastonOffButtonPressTime));

            off = true;
            flashLed(ObS_PIN, 4, 200);
            Serial.println("Turning Off <<<<");
        }
    }

    return false;
}