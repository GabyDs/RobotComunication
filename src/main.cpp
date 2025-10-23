#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include "get_mac.h"
#include "config.h"

void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status)
{
	Serial.print("\r\nLast Packet Send Status:\t");
	Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void SendMessage(uint8_t peek_id)
{
	String payload = "MY STRING";

	esp_err_t result = esp_now_send(RECEIVERS_MACS[peek_id], (uint8_t*)payload.c_str(), payload.length());

	if(result == ESP_OK)
	{
		Serial.println("Sent with success");
	}
	else
	{
		Serial.println("Error sending the data");
	}
}


// We need to register all MAC in the Sender.

void static RegisterPeek(uint8_t id)
{
	esp_now_peer_info_t peerInfo;
	memset(&peerInfo, 0, sizeof(peerInfo)); // Inicializar toda la estructura
	memcpy(peerInfo.peer_addr, RECEIVERS_MACS[id], 6);
	peerInfo.channel = 1; // Canal WiFi fijo (1-13)
	peerInfo.encrypt = false;
	peerInfo.ifidx = WIFI_IF_STA; // ¡Esto es crucial!

	if(esp_now_add_peer(&peerInfo) != ESP_OK)
	{
		Serial.println("Failed to add peer");
	}
	else
	{
		Serial.print("Registered peer ");
		Serial.println(id);
	}
}

void static RegisterPeeks()
{
	for(auto peek_id = 0; peek_id < RECEIVERS_COUNT; peek_id ++)
	{
		RegisterPeek(peek_id);
	}
}

void static InitEspNow()
{
	if(esp_now_init() != ESP_OK)
	{
		Serial.println("Error initializing ESP-NOW");
	}
	else
	{
		esp_now_register_send_cb(OnDataSent);
		
		RegisterPeeks();
	}
}


void setup()
{
    Serial.begin(115200);
    
    // Descomentar la siguiente línea cuando se necesite ver la MAC
    // printMacAddress();
    
    Serial.println("Sistema iniciado");
    Serial.print("Número de receptores configurados: ");
    Serial.println(RECEIVERS_COUNT);

    delay(2000);
    WiFi.mode(WIFI_STA);
    
    // Configurar el canal WiFi explícitamente
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

    InitEspNow();
}

void loop()
{
  static uint8_t currentReceiver = 0;
  
  Serial.print("Sending to receiver ");
  Serial.println(currentReceiver);
  
  SendMessage(currentReceiver);
  
  // Cambiar al siguiente receptor
  currentReceiver++;
  if(currentReceiver >= RECEIVERS_COUNT)
  {
    currentReceiver = 0; // Volver al primer receptor
  }
  
  delay(2000);
}