void readSensor()
{
    voltage = ina219.getBusVoltage_V();

    current = ina219.getCurrent_mA();

    power = (voltage * current) / 1000.0;

    static unsigned long lastMillis = millis();
    unsigned long now = millis();

    float deltaHour = (now - lastMillis) / 3600000.0;

    energyWh += power * deltaHour;

    lastMillis = now;
}

void printSensor()
{
    Serial.println("================================");

    Serial.print("Voltage : ");
    Serial.print(voltage, 2);
    Serial.println(" V");

    Serial.print("Current : ");
    Serial.print(current, 2);
    Serial.println(" mA");

    Serial.print("Power   : ");
    Serial.print(power, 3);
    Serial.println(" W");

    Serial.print("Energy  : ");
    Serial.print(energyWh, 5);
    Serial.println(" Wh");

    Serial.println();
}