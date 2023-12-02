# Gasmeter ESP 16 Reader

Provides gas meter reading through a REST API. Initial states (or manual updates) can be submitted 
by e.g. http://IP/write?meter=20672.18. Then, the application reads a gas meter (BK-G4) using a 
reed sensor (AZ-Delivery KY-025 Magnetic Switch Reed Sensor Module) and updates it state of the 
meter reading. Sometimes, that state is persisted in ESP's 
EEPROM.
