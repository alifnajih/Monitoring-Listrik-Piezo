void showSplash()
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("SIPEKA");

    lcd.setCursor(0,1);
    lcd.print("Monitor Energi.2");

    delay(2000);
}


void updateLCD()
{
    if(millis()-lcdTimer<3000) return;

    lcdTimer=millis();

    lcd.clear();

    switch(lcdPage)
    {

    case 0:

        lcd.setCursor(0,0);
        lcd.print("V:");
        lcd.print(voltage,2);
        lcd.print("V");

        lcd.setCursor(0,1);
        lcd.print("I:");
        lcd.print(current,1);
        lcd.print("mA");

        break;

    case 1:

        lcd.setCursor(0,0);
        lcd.print("P:");
        lcd.print(power,3);
        lcd.print("W");

        lcd.setCursor(0,1);
        lcd.print("E:");
        lcd.print(energyWh,3);
        lcd.print("Wh");

        break;

    case 2:

        lcd.setCursor(0,0);

        if(wifiConnected)
            lcd.print("WiFi:ONLINE");

        else
            lcd.print("WiFi:AP MODE");

        lcd.setCursor(0,1);
        lcd.print(ipAddress);

        break;

    }

    lcdPage++;

    if(lcdPage>2)
        lcdPage=0;

}