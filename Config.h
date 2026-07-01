#ifndef CONFIG_H
#define CONFIG_H

// =======================
// I2C
// =======================
#define SDA_PIN 21
#define SCL_PIN 22

// =======================
// LCD
// =======================
#define LCD_ADDRESS 0x27

// =======================
// Button
// =======================
#define WIFI_BUTTON 27

// =======================
// AP MODE
// =======================
const char* AP_SSID = "SIPEKA_AP";
const char* AP_PASS = "12345678";

// =======================
// Timing
// =======================
const uint32_t SENSOR_INTERVAL = 1000;
const uint32_t LCD_INTERVAL    = 3000;

#endif