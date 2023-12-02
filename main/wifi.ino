#include <ESP8266WiFi.h>

void connectExistingWifi(const char* p_ssid, const char* p_password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(p_ssid, p_password);
  
  Serial.print("\nConnecting to WiFi");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(p_ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Mac address: ");
  Serial.println(WiFi.macAddress());
}