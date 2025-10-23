#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "get_mac.h"
#include "config.h"

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);
    
    // Descomentar la siguiente línea cuando se necesite ver la MAC
    // printMacAddress();
    
    Serial.println("Sistema iniciado");
    Serial.print("Número de receptores configurados: ");
    Serial.println(RECEIVERS_COUNT);
}

void loop()
{
}