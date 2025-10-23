#include <Arduino.h>
#include <WiFi.h>
#include "get_mac.h"

void printMacAddress()
{
  Serial.println("=== Dirección MAC del ESP32 ===");
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("================================");
}