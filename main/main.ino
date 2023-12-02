
#include <ESP8266WebServer.h> // http://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html#server

ESP8266WebServer server(80);

/** Configuration **/
#define DEBUG 0
const char* ssid = "";
const char* password = "";

#define INPUT_PIN_REED D2
float global_meter = -1;

void setup() {
  Serial.begin(115200);

  // connect to existing Wifi
  // TODO: create wifi setup
  connectExistingWifi(ssid, password);

  // initialize and start web-server
  setupWebserver();
  server.begin();

  // read latest meter reading
  global_meter = load_meter(); 

  // activate pins
  pinMode(LED_BUILTIN, OUTPUT); // built-in LED pin set to output
  pinMode(INPUT_PIN_REED, INPUT); // Activate reading on Reed sensor pin
}

void loop() {
  // handle incoming web requests
  server.handleClient();

  // check whether a reed contact has been fired
  if (has_meter_measure()) {
    // increase meter and print a debug note
    global_meter += 0.01;
    Serial.print("Received reed contact; meter: ");
    Serial.print(global_meter);
    Serial.println("m3");

    // check whether data should be saved permanently
    if (save_meter()) {
      save_meter(global_meter);
      Serial.print("Stored meter: ");
      Serial.println(global_meter);
    }
  }

  delay(10);  
}
