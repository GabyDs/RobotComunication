#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "get_mac.h"

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);
    
    // Descomentar la siguiente línea cuando se necesite ver la MAC
    // printMacAddress();
}

void loop()
{
}