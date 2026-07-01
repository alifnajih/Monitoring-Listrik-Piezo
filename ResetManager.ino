void checkResetButton()
{

    if(digitalRead(WIFI_BUTTON)==LOW)
    {

        if(!buttonPressed)
        {

            buttonPressed=true;

            buttonStart=millis();

        }

        else
        {

            unsigned long holdTime = millis()-buttonStart;

            if(holdTime>=5000 && !resetExecuted)
            {

                resetExecuted=true;

                resetWiFi();

            }

        }

    }
    else
    {

        buttonPressed=false;

        resetExecuted=false;

    }

}


void resetWiFi()
{

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("Reset WiFi...");

    lcd.setCursor(0,1);

    lcd.print("Please Wait");

    Serial.println();

    Serial.println("================================");

    Serial.println("RESET WIFI");

    prefs.begin("wifi",false);

    prefs.clear();

    prefs.end();

    WiFi.disconnect(true,true);

    delay(2000);

    ESP.restart();

}