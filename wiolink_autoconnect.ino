#include <ESP8266WiFi.h>          // Replace with WiFi.h for ESP32
#include <ESP8266WebServer.h>     // Replace with WebServer.h for ESP32
#include <AutoConnect.h>

ESP8266WebServer Server;          // Replace with WebServer for ESP32
AutoConnect      Portal(Server);

void rootPage() {
    char content[] = "Hello, world";
    Server.send(200, "text/plain", content);
}

#include <Bounce2.h>

#define LED_PIN 14
#define BUTTON_PIN 12

// Instantiate a Bounce object
Bounce debouncer = Bounce(); 

void setup() {
    delay(1000);
    Serial.begin(115200);
    Serial.println();
  
    Server.on("/", rootPage);
    if (Portal.begin()) {
        Serial.println("WiFi connected: " + WiFi.localIP().toString());
    }

    // Enable digital pins
    pinMode(15, OUTPUT);
    digitalWrite(15, 1);
  
    // Setup the first button with an internal pull-up :
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    // After setting up the button, setup the Bounce instance :
    debouncer.attach(BUTTON_PIN);
    debouncer.interval(5); // interval in ms
    
    pinMode(LED_PIN, OUTPUT);    
}

void loop() {
    Portal.handleClient();

    debouncer.update();
  
    // Get the updated value :
    int value = debouncer.read();

    // Turn on the LED if either button is pressed :
    if ( value == LOW) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }      
}
