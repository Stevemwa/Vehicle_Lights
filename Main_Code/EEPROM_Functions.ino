/* THIS SECTION HOLDS THE EEPROM FUNCTIONS IN THE ORDER BELOW

                            EEPROM_Init  - on void setup()  to check for previous config 
                                 
                            LoadConfig   - loads the previous configuration from EEPROM and updates the neopixel(update config)

                            SaveConfig  -  saves the configurations if there was not any or if changes have been made on webapp to the EEPROM 


*/

void EEPROM_Init(){
  /*----------------Initializing EEPROM----------------------------*/
   EEPROM.begin(1 + sizeof(uint32_t) * 6 + sizeof(uint16_t) * 3 + sizeof(uint8_t) * 10);
  if (EEPROM.read(0) == 0xA5) {
    LoadConfig();
    updateConfig_L();
    updateConfig_R();
  } else {
    Serial.println("No Config Saved yet! Initializing Default.");
    EEPROM.write(0, 0xA5);
    SaveConfig();
    Serial.println("Initializing of Config Successful");
  }

}


void LoadConfig() {
  // loading saved config from memory
  uint16_t address = 1;
  EEPROM.get(address, NUM_LEDS_L);
  address += sizeof(uint16_t);
  EEPROM.get(address, NUM_LEDS_R);
  address += sizeof(uint16_t);
  EEPROM.get(address, freq_L);
  address += sizeof(uint8_t);
  EEPROM.get(address, freq_R);
  address += sizeof(uint8_t);
  EEPROM.get(address, scheme_L);
  address += sizeof(uint8_t);
  EEPROM.get(address, scheme_R);
  address += sizeof(uint8_t);
  EEPROM.get(address, Strobe);
  address += sizeof(uint8_t);
  EEPROM.get(address, leftColor);
  address += sizeof(uint32_t);
  EEPROM.get(address, RightColor);
  address += sizeof(uint32_t);
  EEPROM.get(address, DRLColor);
  address += sizeof(uint32_t);
  EEPROM.get(address, BrakeColor);
  address += sizeof(uint32_t);
  EEPROM.get(address, brightness);
  address += sizeof(uint8_t);
  EEPROM.get(address, duration);
  address += sizeof(uint32_t);
  EEPROM.get(address, BlinkerLEDs);
  address += sizeof(uint8_t);
  EEPROM.get(address, BlinkerSpeed);
  address += sizeof(uint16_t);
  EEPROM.get(address, strip_select);
  address += sizeof(uint8_t);
  EEPROM.get(address, BlinkerAnimation);
  address += sizeof(uint8_t);
  delay(1000);
  Serial.println("Configuration Loaded Successfully.");
}

void SaveConfig() {
  // Saving Current Settings
  uint16_t address = 1;
  EEPROM.put(address, NUM_LEDS_L);
  address += sizeof(uint16_t);
  EEPROM.put(address, NUM_LEDS_R);
  address += sizeof(uint16_t);
  EEPROM.put(address, freq_L);
  address += sizeof(uint8_t);
  EEPROM.put(address, freq_R);
  address += sizeof(uint8_t);
  EEPROM.put(address, scheme_L);
  address += sizeof(uint8_t);
  EEPROM.put(address, scheme_R);
  address += sizeof(uint8_t);
  EEPROM.put(address, Strobe);
  address += sizeof(uint8_t);
  EEPROM.put(address, leftColor);
  address += sizeof(uint32_t);
  EEPROM.put(address, RightColor);
  address += sizeof(uint32_t);
  EEPROM.put(address, DRLColor);
  address += sizeof(uint32_t);
  EEPROM.put(address, BrakeColor);
  address += sizeof(uint32_t);
  EEPROM.put(address, brightness);
  address += sizeof(uint8_t);
  EEPROM.put(address, duration);
  address += sizeof(uint32_t);
  EEPROM.put(address, BlinkerLEDs);
  address += sizeof(uint8_t);
  EEPROM.put(address, BlinkerSpeed);
  address += sizeof(uint16_t);
  EEPROM.put(address, strip_select);
  address += sizeof(uint8_t);
  EEPROM.put(address, BlinkerAnimation);
  address += sizeof(uint8_t);
  EEPROM.commit();
  Serial.println("Current Configuration Saved Successfully!");
}