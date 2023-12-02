
// stores start of last reed contact
unsigned long lastContactStart = -1;
// TODO: check whether there are small disconnects of the contact
unsigned long prevContactEnd = -1;

// cound duration of contact
int contacts = 0;

/**
 * Returns true, if a reading cycle is finished
 */
bool has_meter_measure() {
  int digitalValue = digitalRead(INPUT_PIN_REED);
  int adcValue = analogRead(A0);

  if (digitalValue == 1 || adcValue < 900)
  {
    contacts += 1;
    if (lastContactStart == -1) {
      lastContactStart = millis();
      if (DEBUG) { Serial.print("Contact started: "); Serial.println(lastContactStart); }
    }
  } else {
    if (contacts > 0) {
      unsigned long int finishedContact = millis();
      unsigned long int durationContact = finishedContact - lastContactStart;

      if (DEBUG) {
        Serial.print("Finished: "); Serial.print(finishedContact);
        Serial.print("; duration: "); Serial.print(durationContact); Serial.print(" [ms]");
        Serial.print("; Analog: "); Serial.print(adcValue);
        Serial.print("; Digital: "); Serial.println(digitalValue);  
      }
      contacts = 0;
      lastContactStart = -1;

      return true;
    }
    else
    {
      // no contact; skip
    }
  }

  return false;
}
