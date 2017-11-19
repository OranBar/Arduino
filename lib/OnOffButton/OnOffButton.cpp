

bool ObS::loop(void){

   onOffButton->loop();

    if(onOffButton->getCurrentPressDuration() > 3000){
        if (off)        {
            Serial.println("ReBooting >>>>");
            bootAnim(ObS_PIN);
            sleep(500);
            off = false;
            Serial.println("ReBooting <<<<");
            rebooted = true;
        } else {
            if (rebooted) {
                rebooted = false;
                return true;
                //Successfully burnt the ad onOffButton released that was have triggering a turn off
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


//TODO: move to own class?
bool ObS::OnOffButtonLoop(void){
    
}