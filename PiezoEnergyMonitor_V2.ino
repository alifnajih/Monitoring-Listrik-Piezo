#include "Config.h"

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <Wire.h>

#include <Adafruit_INA219.h>

#include <LiquidCrystal_I2C.h>


// ===== Function Prototypes =====
void showSplash();
void updateLCD();

void initWiFi();
void startAP();
void connectWiFi(String ssid, String pass);
void resetWiFi();

void handleRoot();
void handleData();
void handleWiFiPage();
void handleSaveWiFi();

void readSensor();
void printSensor();

void checkResetButton();


LiquidCrystal_I2C lcd(0x27,16,2);
uint8_t lcdPage = 0;
unsigned long lcdTimer = 0;

Adafruit_INA219 ina219;
WebServer server(80);
Preferences prefs;

float voltage = 0;
float current = 0;
float power   = 0;
float energyWh = 0;

bool apMode = false;
bool wifiConnected = false;

String ipAddress = "";

unsigned long sensorTimer = 0;
unsigned long energyTimer = 0;

bool buttonPressed = false;
unsigned long buttonStart = 0;
bool resetExecuted = false;

void setup() {

    Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN);
    pinMode(WIFI_BUTTON, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();

    showSplash();
    if(!ina219.begin()){

        Serial.println("INA219 ERROR");

        while(1);

    }

    Serial.println("INA219 OK");
    initWiFi();
    server.on("/", handleRoot);
    
    server.on("/data", handleData);
    server.on("/wifi", handleWiFiPage);
    server.on("/save", handleSaveWiFi);
    server.begin();
    Serial.println("Web Server Started");
}


void loop()
{
    server.handleClient();
    checkResetButton();
    updateLCD();

    if (millis() - sensorTimer >= SENSOR_INTERVAL)
    {
        sensorTimer = millis();

        readSensor();

        printSensor();
    }
}