#include <espnow.h>
#include <ESP8266WiFi.h>
#include <Servo.h>


/*
   pitch    = D5
   roll     = D6
   extra    = D7 undefined for now
 */

# define PPin D5
# define RPin D6


int Roll = 83;
int Pitch = 80;


Servo Pservo; // Pitch
Servo Rservo; // Roll

int PPos = 0; // Pitch PWM output
int RPos = 0; // Roll PWM output


unsigned long now;
unsigned long LastRec;
unsigned long NxtRcv;

// Setting up what the signal would look like
struct Signal {
    byte pitch;
    byte roll;
};

Signal data;


// To run if signal is lost
void DataReset(){
    data.pitch = 90;
    data.roll = 90;
}



void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {

    memcpy(&data, incomingData, sizeof(Signal));

    Pitch = data.pitch;
    Roll = data.roll;

    LastRec = millis() / 1000;
    NxtRcv = LastRec + 3;

    Serial.print("Pitch: ");
    Serial.println(data.pitch);

    Serial.print("Roll: ");
    Serial.println(data.roll);

    now = millis();
}

void setup(){

    Serial.begin(9600);

    delay(500);

    Pservo.attach(PPin);
    Rservo.attach(RPin);

    DataReset();

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW...");
        return;
    }

    // Sets role
    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    // Does things on callback (when data is sent over)
    esp_now_register_recv_cb(OnDataRecv);
}


int lastRecv = 0;

void loop(){
    now = millis() / 1000;
    if (now > NxtRcv){
        DataReset();
        Serial.println("Connection lost, data has been reset...");
        delay(500);
    }

    PPos = data.pitch;     // pin D5 (PWM signal)
    RPos = data.roll;      // pin D6 (PWM signal)

    Pservo.write(PPos);
    Rservo.write(RPos);
}
