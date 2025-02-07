// /* THIS SECTION HOLDS THE EEPROM FUNCTIONS IN THE ORDER BELOW

//                             EEPROM_Init  - on void setup()  to check for previous config 

//                             ruint32_t RGBWToRG - Updates the dynamic variable to the EEPROM saved RGBW color
                                 
//                             LoadConfig   - loads the previous configuration from EEPROM and updates the neopixel(update config)

//                             SaveConfig  -  saves the configurations if there was not any or if changes have been made on webapp to the EEPROM 


// */

// void EEPROM_Init() {
//   /*----------------Initializing EEPROM----------------------------*/
//   EEPROM.begin(1 + sizeof(uint32_t) * 6 + sizeof(uint16_t) * 3 + sizeof(uint8_t) * 15);
//   if (EEPROM.read(0) == 0xA5) {
//     LoadConfig();
//     updateConfig_L();
//     updateConfig_R();
//   } else {
//     Serial.println("No Config Saved yet! Initializing Default.");
//     EEPROM.write(0, 0xA5);
//     SaveConfig();
//     Serial.println("Initializing of Config Successful");
//   }
// }

// //Updates the dynamic variable to the EEPROM saved RGBW color
// uint32_t RGBWToRGB(uint32_t rgbwColor) {
//   // Extract r, g, b, and w components from the 32-bit RGBW value
//   uint8_t r = (rgbwColor >> 24) & 0xFF;
//   uint8_t g = (rgbwColor >> 16) & 0xFF;
//   uint8_t b = (rgbwColor >> 8) & 0xFF;
//   // Ignore white (w) for RGB conversion

//   // Combine r, g, b into a single RGB value
//   uint32_t rgbColor = (r << 16) | (g << 8) | b;
//   return rgbColor;
// }



// void LoadConfig() {
//   // loading saved config from memory
//   uint16_t address = 1;
//   EEPROM.get(address, NUM_LEDS_L);
//   address += sizeof(uint16_t);
//   EEPROM.get(address, NUM_LEDS_R);
//   address += sizeof(uint16_t);
//   EEPROM.get(address, freq_L);
//   address += sizeof(uint8_t);
//   EEPROM.get(address, freq_R);
//   address += sizeof(uint8_t);
//   EEPROM.get(address, scheme_L);
//   address += sizeof(uint8_t);
//   EEPROM.get(address, scheme_R);
//   address += sizeof(uint8_t);
//   EEPROM.get(address, Strobe);
//   address += sizeof(uint8_t);
//   EEPROM.get(address, Dynamic_leftColor);
//   address += sizeof(uint32_t);
//   EEPROM.get(address, Dynamic_RightColor);
//   address += sizeof(uint32_t);
//   EEPROM.get(address, Dynamic_DRLColor);
//   address += sizeof(uint32_t);
//   EEPROM.get(address, Dynamic_BrakeColor);
//   address += sizeof(uint32_t);
//   EEPROM.get(address, Dynamic_thrdColor);
//   address += sizeof(uint32_t);
//   EEPROM.get(address, brightness);
//   address += sizeof(uint8_t);
//   EEPROM.get(address, duration);
//   address += sizeof(uint32_t);
//   EEPROM.get(address, BlinkerLEDs);
//   address += sizeof(uint8_t);
//   EEPROM.get(address, BlinkerSpeed);
//   address += sizeof(uint16_t);
//   EEPROM.get(address, strip_select);
//   address += sizeof(uint8_t);
//   EEPROM.get(address, BlinkerAnimation);
//   address += sizeof(uint8_t);
//   EEPROM.get(address, LeftDirection);
//   address += sizeof(uint8_t);
//   EEPROM.get(address, RightDirection);
//   address += sizeof(uint8_t);
//   EEPROM.get(address, StartAnimation);
//   address += sizeof(uint8_t);
//   delay(1000);

//   uint8_t Red = (Dynamic_leftColor >> 16) & 0xFF;
//   uint8_t Green = (Dynamic_leftColor >> 8) & 0xFF;
//   uint8_t Blue = Dynamic_leftColor & 0xFF;
//   col = converter.RGBToRGBW(Red, Green, Blue);
//   leftColor = (col.r << 24) | (col.g << 16) | (col.b << 8) | col.w;

//   Red = (Dynamic_RightColor >> 16) & 0xFF;
//   Green = (Dynamic_RightColor >> 8) & 0xFF;
//   Blue = Dynamic_RightColor & 0xFF;
//   col = converter.RGBToRGBW(Red, Green, Blue);
//   RightColor = (col.r << 24) | (col.g << 16) | (col.b << 8) | col.w;

//   Red = (Dynamic_DRLColor >> 16) & 0xFF;
//   Green = (Dynamic_DRLColor >> 8) & 0xFF;
//   Blue = Dynamic_DRLColor & 0xFF;
//   col = converter.RGBToRGBW(Red, Green, Blue);
//   DRLColor = (col.r << 24) | (col.g << 16) | (col.b << 8) | col.w;
//   Serial.print("Dynamic_DRL");
//   Serial.println(Dynamic_DRLColor);
//   Serial.print("DRL");
//   Serial.println(DRLColor);
  
  

//   Red = (Dynamic_BrakeColor >> 16) & 0xFF;
//   Green = (Dynamic_BrakeColor >> 8) & 0xFF;
//   Blue = Dynamic_BrakeColor & 0xFF;
//   col = converter.RGBToRGBW(Red, Green, Blue);
//   BrakeColor = (col.r << 24) | (col.g << 16) | (col.b << 8) | col.w;

//   Red = (Dynamic_thrdColor >> 16) & 0xFF;
//   Green = (Dynamic_thrdColor >> 8) & 0xFF;
//   Blue = Dynamic_thrdColor & 0xFF;
//   col = converter.RGBToRGBW(Red, Green, Blue);
//   thrdColor = (col.r << 24) | (col.g << 16) | (col.b << 8) | col.w;


//   delay(100);
//   Serial.println("Configuration Loaded Successfully.");
// }

// void SaveConfig() {
//   // Saving Current Settings
//   uint16_t address = 1;
//   EEPROM.put(address, NUM_LEDS_L);
//   address += sizeof(uint16_t);
//   EEPROM.put(address, NUM_LEDS_R);
//   address += sizeof(uint16_t);
//   EEPROM.put(address, freq_L);
//   address += sizeof(uint8_t);
//   EEPROM.put(address, freq_R);
//   address += sizeof(uint8_t);
//   EEPROM.put(address, scheme_L);
//   address += sizeof(uint8_t);
//   EEPROM.put(address, scheme_R);
//   address += sizeof(uint8_t);
//   EEPROM.put(address, Strobe);
//   address += sizeof(uint8_t);
//   EEPROM.put(address, Dynamic_leftColor);
//   address += sizeof(uint32_t);
//   EEPROM.put(address, Dynamic_RightColor);
//   address += sizeof(uint32_t);
//   EEPROM.put(address, Dynamic_DRLColor);
//   address += sizeof(uint32_t);
//   EEPROM.put(address, Dynamic_BrakeColor);
//   address += sizeof(uint32_t);
//   EEPROM.put(address, Dynamic_thrdColor);
//   address += sizeof(uint32_t);
//   EEPROM.put(address, brightness);
//   address += sizeof(uint8_t);
//   EEPROM.put(address, duration);
//   address += sizeof(uint32_t);
//   EEPROM.put(address, BlinkerLEDs);
//   address += sizeof(uint8_t);
//   EEPROM.put(address, BlinkerSpeed);
//   address += sizeof(uint16_t);
//   EEPROM.put(address, strip_select);
//   address += sizeof(uint8_t);
//   EEPROM.put(address, BlinkerAnimation);
//   address += sizeof(uint8_t);
//   EEPROM.put(address, LeftDirection);
//   address += sizeof(uint8_t);
//   EEPROM.put(address, RightDirection);
//   address += sizeof(uint8_t);
//   EEPROM.put(address, StartAnimation);
//   address += sizeof(uint8_t);
//   EEPROM.commit();
//   Serial.println("Current Configuration Saved Successfully!");
// }





// Function to initialize SPIFFS
void SPIFFS_Init() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
  } else {
    Serial.println("SPIFFS mounted successfully");
  }

   LoadConfig();
}

// Function to load configuration from SPIFFS
void LoadConfig() {
  if (!SPIFFS.exists(configFilePath)) {
    Serial.println("No config file found, initializing default settings");
    SaveConfig(); // Save default settings if no file exists
    return;
  }

  File file = SPIFFS.open(configFilePath, FILE_READ);
  if (!file) {
    Serial.println("Failed to open config file for reading");
    return;
  }

  uint16_t address = 0;
  file.readBytes((char *)&NUM_LEDS_L, sizeof(uint16_t));
  file.readBytes((char *)&NUM_LEDS_R, sizeof(uint16_t));
  file.readBytes((char *)&freq_L, sizeof(uint8_t));
  file.readBytes((char *)&freq_R, sizeof(uint8_t));
  file.readBytes((char *)&scheme_L, sizeof(uint8_t));
  file.readBytes((char *)&scheme_R, sizeof(uint8_t));
  file.readBytes((char *)&Strobe, sizeof(uint8_t));
  file.readBytes((char *)&Dynamic_leftColor, sizeof(uint32_t));
  file.readBytes((char *)&Dynamic_RightColor, sizeof(uint32_t));
  file.readBytes((char *)&Dynamic_DRLColor, sizeof(uint32_t));
  file.readBytes((char *)&Dynamic_BrakeColor, sizeof(uint32_t));
  file.readBytes((char *)&Dynamic_thrdColor, sizeof(uint32_t));
  file.readBytes((char *)&brightness, sizeof(uint8_t));
  file.readBytes((char *)&duration, sizeof(uint32_t));
  file.readBytes((char *)&BlinkerLEDs, sizeof(uint8_t));
  file.readBytes((char *)&BlinkerSpeed, sizeof(uint16_t));
  file.readBytes((char *)&strip_select, sizeof(uint8_t));
  file.readBytes((char *)&BlinkerAnimation, sizeof(uint8_t));
  file.readBytes((char *)&LeftDirection, sizeof(uint8_t));
  file.readBytes((char *)&RightDirection, sizeof(uint8_t));
  file.readBytes((char *)&StartAnimation, sizeof(uint8_t));

  file.close();

  updateConfig_L();
  updateConfig_R();

  uint8_t Red = (Dynamic_leftColor >> 16) & 0xFF;
  uint8_t Green = (Dynamic_leftColor >> 8) & 0xFF;
  uint8_t Blue = Dynamic_leftColor & 0xFF;
  col = converter.RGBToRGBW(Red, Green, Blue);
  leftColor = leds_R->Color(col.r, col.g, col.b, col.w);


  
  Red = (Dynamic_RightColor >> 16) & 0xFF;
  Green = (Dynamic_RightColor >> 8) & 0xFF;
  Blue = Dynamic_RightColor & 0xFF;
  col = converter.RGBToRGBW(Red, Green, Blue);
  RightColor = leds_R->Color(col.r, col.g, col.b, col.w);
  Serial.print("Dynamic_Right: ");
  Serial.println(Dynamic_RightColor);
  Serial.print("Right: ");
  Serial.println(RightColor);


  Red = (Dynamic_DRLColor >> 16) & 0xFF;
  Green = (Dynamic_DRLColor >> 8) & 0xFF;
  Blue = Dynamic_DRLColor & 0xFF;
  col = converter.RGBToRGBW(Red, Green, Blue);
  DRLColor = leds_R->Color(col.r, col.g, col.b, col.w);
  Serial.print("Dynamic_DRL: ");
  Serial.println(Dynamic_DRLColor);
  Serial.print("DRL: ");
  Serial.println(DRLColor);
  

  Red = (Dynamic_BrakeColor >> 16) & 0xFF;
  Green = (Dynamic_BrakeColor >> 8) & 0xFF;
  Blue = Dynamic_BrakeColor & 0xFF;
  col = converter.RGBToRGBW(Red, Green, Blue);
  BrakeColor = leds_R->Color(col.r, col.g, col.b, col.w);

  Red = (Dynamic_thrdColor >> 16) & 0xFF;
  Green = (Dynamic_thrdColor >> 8) & 0xFF;
  Blue = Dynamic_thrdColor & 0xFF;
  col = converter.RGBToRGBW(Red, Green, Blue);
  thrdColor = leds_R->Color(col.r, col.g, col.b, col.w);
  Serial.println("Configuration loaded successfully");

  
}

// Function to save configuration to SPIFFS
void SaveConfig() {
  File file = SPIFFS.open(configFilePath, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open config file for writing");
    return;
  }

  file.write((uint8_t *)&NUM_LEDS_L, sizeof(uint16_t));
  file.write((uint8_t *)&NUM_LEDS_R, sizeof(uint16_t));
  file.write((uint8_t *)&freq_L, sizeof(uint8_t));
  file.write((uint8_t *)&freq_R, sizeof(uint8_t));
  file.write((uint8_t *)&scheme_L, sizeof(uint8_t));
  file.write((uint8_t *)&scheme_R, sizeof(uint8_t));
  file.write((uint8_t *)&Strobe, sizeof(uint8_t));
  file.write((uint8_t *)&Dynamic_leftColor, sizeof(uint32_t));
  file.write((uint8_t *)&Dynamic_RightColor, sizeof(uint32_t));
  file.write((uint8_t *)&Dynamic_DRLColor, sizeof(uint32_t));
  file.write((uint8_t *)&Dynamic_BrakeColor, sizeof(uint32_t));
  file.write((uint8_t *)&Dynamic_thrdColor, sizeof(uint32_t));
  file.write((uint8_t *)&brightness, sizeof(uint8_t));
  file.write((uint8_t *)&duration, sizeof(uint32_t));
  file.write((uint8_t *)&BlinkerLEDs, sizeof(uint8_t));
  file.write((uint8_t *)&BlinkerSpeed, sizeof(uint16_t));
  file.write((uint8_t *)&strip_select, sizeof(uint8_t));
  file.write((uint8_t *)&BlinkerAnimation, sizeof(uint8_t));
  file.write((uint8_t *)&LeftDirection, sizeof(uint8_t));
  file.write((uint8_t *)&RightDirection, sizeof(uint8_t));
  file.write((uint8_t *)&StartAnimation, sizeof(uint8_t));

  file.close();
  Serial.println("Configuration saved successfully");
}

// Initialization function
void SPIFFS_Config_Init() {
  SPIFFS_Init();
  LoadConfig();
}
