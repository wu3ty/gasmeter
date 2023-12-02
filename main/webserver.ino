void setupWebserver() {
  Serial.print("Starting HTTP Server...");
  server.on("/", getMeter);
  server.on("/write", setMeter);

  Serial.println("done");
}

/**
 * Endpoint that returns a JSON-based reading
 */
void getMeter() {
  String json = "{";
  json += "\"model\" : \"BK-G4\",\n";
  json += "\"meter\" : ";
  json += global_meter;
  json += ",\n\"unit\" : \"m3\"";
  json += "}";
  server.send(200, "application/json", json.c_str());     // Zählerstand und Led Status an Html Seite senden
}

/**
 * Enables a manual update of the latest meeting reading, http://IP/write?meter=20672.18
 */
void setMeter() {
  if (server.hasArg("meter")) {
    Serial.println(server.arg("meter"));
    
    float new_meter = server.arg("meter").toFloat();
    global_meter = new_meter;
    save_meter(new_meter);

    Serial.print("Manual updated meter value: ");
    Serial.println(new_meter);

    server.send(200, "text/html", "done");
  }
}