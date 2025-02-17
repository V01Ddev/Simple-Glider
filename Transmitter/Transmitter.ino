#include <SPI.h>
#include "WiFi.h"
#include <esp_now.h>


/*
Right stick:
   X-axis = D32 (pitch)
   Y-axis = D33 (roll)
*/


#define PitchPIN 32
#define RollPIN 33
int Pitch = 0;
int Roll = 0;

// 50:02:91:FF:DB:3A
uint8_t broadcastAddress[] =  {0x50, 0x02, 0x91, 0xFF, 0xDB, 0x3A};
esp_now_peer_info_t peerInfo;

// Setting up what the signal would look like
struct Signal {
    byte pitch;
    byte roll;
};

Signal data;


void setup(){
    Serial.begin(115200);

    pinMode(PitchPIN, INPUT);
    pinMode(RollPIN, INPUT);

    WiFi.mode(WIFI_STA);

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register the send callback

    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0; 
    peerInfo.encrypt = false;

    // Add peer        
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
	return;
    }

    delay(1000);

    Serial.println("Setup complete...");
}



void loop(){
	// map({pin}, {min_value}, {max_value}, 0, 255)

	Roll = analogRead(RollPIN);
	Roll = map(Roll, 0, 4095, 180, 0);

	Pitch = analogRead(PitchPIN);
	Pitch = map(Pitch, 0, 4095, 0, 180);

	// Reversing the pitch
	// Pitch = 255 - Pitch;

	//constrain(Pitch, 45, 135);

	Serial.print("Pitch: ");
	Serial.println(Pitch);

	Serial.print("Roll: ");
	Serial.println(Roll);

	data.pitch = Pitch;
	data.roll = Roll;

	esp_now_send(broadcastAddress, (uint8_t *) &data, sizeof(Signal));

	delay(50);
}
