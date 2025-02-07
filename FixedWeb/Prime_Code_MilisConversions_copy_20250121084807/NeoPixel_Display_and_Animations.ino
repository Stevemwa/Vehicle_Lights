/*
THIS SECTION CONTAINS DISPLAY VARIABLES,FUNCTIONS, ANIMATIONS IN THE FOLLOWING ORDER
                                  
                                 
                                        
                                ANIMATION VARIABLES

                      NEO PIXEL CONFIGURATION & UPDATE FUNCTIONS 

                               ANIMATIONS FUNCTIONS 

                                

*/


/*_____________________________________________________________ VARIABLES DEFINATION ________________________________________________________*/

uint8_t idex = 0;
uint8_t ihue = 0;
uint8_t isat = 255;
uint8_t ibright = 0;
//uint16_t TOP_INDEX = uint8_t(strip->numPixels() / 2); // center of the stip
//uint8_t EVENODD = strip->numPixels() % 2;
uint8_t bouncedirection = 0;

//---------------------------------White over Rainbow-----------------------------------
int tail2 = 0;
int loops2 = 3;
int loopNum2 = 0;
int firstPixelHue = 0;
int whiteLEDsCount = 1;  // Initialize the counter with 1 white LED


// -------------------------------- RAINBOW LOOP 1-------------------------------------
int tail = 0;
int loopNum = 0;

// -------------------------------- RAINBOW LOOP 2 -------------------------------------
int fadeVal = 0, fadeMax = 100;

// rotating rainbow
uint32_t randomColor = random(0, 0x1000000);

//------------------------------- RADIATION ---------------------------------------
float rcount = 0.0;
int currentStep = 0;           // Keeps track of the current step (0, 1, or 2)


/*_______________________________________________________________________ RELATED FUNCTIONS _____________________________________________________________-*/
/*--------------------------------------------- NEOPIXEL INITIALIZATION -----------------------------------------------*/
void NeoPixel_Init(){
leds_L->begin();
  leds_R->begin();
  leds_3->begin();
}



/*----------------------------------------- NEOPIXEL UPDATE CONFIGURATIONS --------------------------------------------*/
void updateConfig_L() {
  delete leds_L;
  leds_L = new Adafruit_NeoPixel(NUM_LEDS_L, LED_PIN_L, scheme_L + freq_L);
  leds_L->setBrightness(brightness);
  leds_L->clear();
}

void updateConfig_R() {
  delete leds_R;
  leds_R = new Adafruit_NeoPixel(NUM_LEDS_R, LED_PIN_R, scheme_R + freq_R);
  leds_R->setBrightness(brightness);
  leds_R->clear();
}

void updateConfig_3() {
  delete leds_3;
  leds_3 = new Adafruit_NeoPixel(NUM_LEDS_3, LED_PIN_3, scheme_3 + freq_3);
  leds_3->setBrightness(brightness);
  leds_3->clear();
}


/*------------------------------------------ HEX COLOR TO STRING CONVERTER ----------------------------------------------*/
String ColorString(uint32_t ColorHex) {
  Red = (ColorHex >> 16) & 0xFF;
  Green = (ColorHex >> 8) & 0xFF;
  Blue = ColorHex & 0xFF;
  String redHex = String(Red, HEX);
  if (redHex.length() == 1) {
    redHex = "0" + redHex;  // add leading zero if necessary
  }
  String greenHex = String(Green, HEX);
  if (greenHex.length() == 1) {
    greenHex = "0" + greenHex;  // add leading zero if necessary
  }
  String blueHex = String(Blue, HEX);
  if (blueHex.length() == 1) {
    blueHex = "0" + blueHex;  // add leading zero if necessary
  }
  String HexColor = "#" + redHex + greenHex + blueHex;
  return HexColor;
}




/*____________________________________________________________________________________________________________________________________________________________________________*/


/*----------------------------------------------------------------------------- ANIMATION EFFECTS -----------------------------------------------------------------------------*/

/*____________________________________________________________________________________________________________________________________________________________________________*/


/*___________________________________________WHITE OVER RAINBOW EFFECTS___________________________________________*/
void WhiteoverRainbow(Adafruit_NeoPixel *strip, int whiteSpeed, int whiteLength) {
  uint16_t NumLeds = strip->numPixels();
  whiteLength = NumLeds;  // Set whiteLength to NumLeds

  if (whiteLength >= NumLeds) whiteLength = NumLeds - 1;

  for (int i = 0; i < NumLeds; i++) {
    if (((i >= tail2) && (i <= tail2 + whiteLEDsCount - 1)) || ((tail2 + whiteLEDsCount - 1 >= NumLeds) && ((i >= tail2) || (i <= (tail2 + whiteLEDsCount - 1) % NumLeds)))) {
      strip->setPixelColor(i, strip->Color(255, 255, 255));  // Set white
    } else {
      int pixelHue = firstPixelHue + (i * 65536L / strip->numPixels());
      strip->setPixelColor(i, strip->gamma32(strip->ColorHSV(pixelHue)));  // Set rainbow
    }
  }

  strip->show();  // Update strip with new colors

  firstPixelHue += 40;  // Advance just a little along the color wheel

  if ((millis() - lastTime) > whiteSpeed) {  // Time to update head/tail?
    tail2++;                                 // Increment tail2
    if (tail2 >= NumLeds) {
      tail2 = 0;         // Reset tail2 to 0 when it reaches the end of the strip
      whiteLEDsCount++;  // Increment the number of white LEDs
      if (whiteLEDsCount > whiteLength) {
        whiteLEDsCount = 1;  // Reset the counter when it exceeds whiteLength
      }
    }

    lastTime = millis();  // Save time of last movement
  }
}



/*_________________________________________ RAINBOW LOOP 1______________________________________*/
void RainbowLoop1(Adafruit_NeoPixel *strip, int whiteSpeed, int whiteLength) {
  int head = whiteLength - 1;
  uint16_t NumLeds = strip->numPixels();
  if (whiteLength >= NumLeds) whiteLength = NumLeds - 1;

  for (int i = 0; i < NumLeds; i++) {    // For each pixel in strip...
    if (((i >= tail) && (i <= head)) ||  //  If between head & tail...
        ((tail > head) && ((i >= tail) || (i <= head)))) {
      continue;
    } else {  // else set rainbow
      int pixelHue = firstPixelHue + (i * 65536L / strip->numPixels());
      strip->setPixelColor(i, strip->gamma32(strip->ColorHSV(pixelHue)));
    }
  }

  strip->show();

  firstPixelHue += 40;  // Advance just a little along the color wheel

  if ((millis() - lastTime) > whiteSpeed) {  // Time to update head/tail?
    if (++head >= NumLeds) {                 // Advance head, wrap around
      head = 0;
    }
    if (++tail >= strip->numPixels()) {  // Advance tail, wrap around
      tail = 0;
    }
    lastTime = millis();  // Save time of last movement
  }
}



/*_________________________________________ RAINBOW LOOP 2 ________________________________________*/
void RainbowLoop2(Adafruit_NeoPixel *strip, int rainbowLoops, int whiteLoops) {
  firstPixelHue += 256;
  if (firstPixelHue >= rainbowLoops * 65536)
    firstPixelHue = 0;

  for (int i = 0; i < strip->numPixels(); i++) {  // For each pixel in strip...

    uint32_t pixelHue = firstPixelHue + (i * 65536L / strip->numPixels());

    strip->setPixelColor(i, strip->gamma32(strip->ColorHSV(pixelHue, 255, 255 * fadeVal / fadeMax)));
  }

  strip->show();

  if (firstPixelHue < 65536) {         // First loop,
    if (fadeVal < fadeMax) fadeVal++;  // fade in
  } else {
    fadeVal = fadeMax;  // Interim loop, make sure fade is at max
  }
}



/*_______________________________________________ COLOR WIPE ________________________________________*/
// Global state variables for each LED strip
unsigned long lastUpdateTime_L = 0;
int currentPixel_L = 0;
uint32_t newColor_L = random(0, 0x1000000) ;

unsigned long lastUpdateTime_R = 0;
int currentPixel_R = 0;
uint32_t newColor_R = random(0, 0x1000000 );

void colorWipe(Adafruit_NeoPixel *strip_L, Adafruit_NeoPixel *strip_R) {
  unsigned long currentMillis = millis();  // Current time
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Check if enough time has passed to update the next pixel
  if (currentMillis - lastUpdateTime_L >= Speed) {
    lastUpdateTime_L = currentMillis;  // Update lastUpdateTime to the current time

    // Update the first strip (leds_L) pixel by pixel
    if (currentPixel_L < strip_L->numPixels()) {
      strip_L->setPixelColor(currentPixel_L, newColor_L);  // Set the color for the current pixel
      currentPixel_L++;  // Move to the next pixel
    } else {
      // Once the first strip is fully updated, reset all pixels to black
      for (int i = 0; i < strip_L->numPixels(); i++) {
        strip_L->setPixelColor(i, 0); // Turn off each pixel
      }
      currentPixel_L = 0;  // Reset the current pixel to start a new cycle
      newColor_L = random(0, 0xFFFFFF);  // Generate a new random color for the next cycle
    }
  }

  // Check if enough time has passed to update the second strip (leds_R)
  if (currentMillis - lastUpdateTime_R >= Speed) {
    lastUpdateTime_R = currentMillis;  // Update lastUpdateTime to the current time

    // Update the second strip (leds_R) pixel by pixel
    if (currentPixel_R < strip_R->numPixels()) {
      strip_R->setPixelColor(currentPixel_R, newColor_R);  // Set the color for the current pixel
      currentPixel_R++;  // Move to the next pixel
    } else {
      // Once the second strip is fully updated, reset all pixels to black
      for (int i = 0; i < strip_R->numPixels(); i++) {
        strip_R->setPixelColor(i, 0); // Turn off each pixel
      }
      currentPixel_R = 0;  // Reset the current pixel to start a new cycle
      newColor_R = random(0, 0x1000000 );  // Generate a new random color for the next cycle
    }
  }

  // Show the updated colors after both strips are processed
  strip_L->show();
  strip_R->show();
}

//_____________________________________________ RANDOM MARCH _________________________________________*/
//--------------------------------------the madness of random leds_L-----------------------------------
void randomMarch(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R) {
  static unsigned long lastUpdateTime = 0;  // Time of last update
  unsigned long currentMillis = millis();  // Current time
    int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Check if enough time has passed to perform the update
  if (currentMillis - lastUpdateTime >= Speed) {
    lastUpdateTime = currentMillis;  // Update lastUpdateTime to the current time

    // Set the first pixel on both strips to a random color
    leds_L->setPixelColor(0, leds_L->Color(random(0, 255), random(0, 255), random(0, 255)));
    leds_R->setPixelColor(0, leds_R->Color(random(0, 255), random(0, 255), random(0, 255)));

    // March the pixels on the left strip
    for (int idex = 1; idex < leds_L->numPixels(); idex++) {
      int iCCW = adjacent_ccw(leds_L->numPixels(), idex);
      leds_L->setPixelColor(idex, leds_L->getPixelColor(iCCW));
    }

    // March the pixels on the right strip
    for (int idex = 1; idex < leds_R->numPixels(); idex++) {
      int iCCW = adjacent_ccw(leds_R->numPixels(), idex);
      leds_R->setPixelColor(idex, leds_R->getPixelColor(iCCW));
    }

    // Update the strips with the new colors
    leds_L->show();
    leds_R->show();
  }
}
/*_____________________________________________ RGB PROPELLER _____________________________________*/
void rgbpropeller(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R) {
  static unsigned long lastUpdateTime = 0;  // Time of last update
  unsigned long currentMillis = millis();  // Current time
    int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Check if enough time has passed to perform the update
  if (currentMillis - lastUpdateTime >= 10) {
    lastUpdateTime = currentMillis;  // Update lastUpdateTime to the current time

    // Calculate the shift based on elapsed time for both strips
    int shift_L = (currentMillis / Speed) % NUM_LEDS_L;
    int shift_R = (currentMillis / Speed) % NUM_LEDS_R;

    // Set each pixel on the left strip (leds_L) to left or right color based on its position
    for (int i = 0; i < NUM_LEDS_L; i++) {
      if ((i + shift_L) % NUM_LEDS_L >= NUM_LEDS_L / 2) {
        leds_L->setPixelColor(i, RightColor);
      } else {
        leds_L->setPixelColor(i, leftColor);
      }
    }

    // Set each pixel on the right strip (leds_R) to left or right color based on its position
    for (int i = 0; i < NUM_LEDS_R; i++) {
      if ((i + shift_R) % NUM_LEDS_R >= NUM_LEDS_R / 2) {
        leds_R->setPixelColor(i, RightColor);
      } else {
        leds_R->setPixelColor(i, leftColor);
      }
    }

    // Update both strips with the new colors
    leds_L->show();
    leds_R->show();
  }
}

/*___________________________________________________ FIRE ______________________________________*/
unsigned long lastFireUpdateTime = 0;  // To track when to update the fire effect
int fireDelay = map(EffectSpeed, 1, 255, 5, 200);

void setPixelHeatColor(Adafruit_NeoPixel *strip, int Pixel, byte temperature) {
  byte t192 = round((temperature / 255.0) * 191);
  byte heatramp = t192 & 0x3F;
  heatramp <<= 2;

  if (t192 > 0x80) {
    strip->setPixelColor(Pixel, 255, 255, heatramp);
  } else if (t192 > 0x40) {
    strip->setPixelColor(Pixel, 255, heatramp, 0);
  } else {
    strip->setPixelColor(Pixel, heatramp, 0, 0);
  }
}

void fire(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, int Cooling, int Sparking) {
  static byte* heat_L = new byte[leds_L->numPixels()];  // Dynamically allocate memory for the heat array for the left strip
  static byte* heat_R = new byte[leds_R->numPixels()];  // Dynamically allocate memory for the heat array for the right strip
  int cooldown;

  unsigned long currentMillis = millis();  // Get current time

  // Only update fire every 'fireDelay' milliseconds
  if (currentMillis - lastFireUpdateTime >= fireDelay) {
    lastFireUpdateTime = currentMillis;  // Update last update time

    // Cool the pixels on the left strip
    for (int i = 0; i < leds_L->numPixels(); i++) {
      cooldown = random(0, ((Cooling * 10) / leds_L->numPixels()) + 2);
      if (cooldown > heat_L[i]) {
        heat_L[i] = 0;
      } else {
        heat_L[i] = heat_L[i] - cooldown;
      }
    }

    // Cool the pixels on the right strip
    for (int i = 0; i < leds_R->numPixels(); i++) {
      cooldown = random(0, ((Cooling * 10) / leds_R->numPixels()) + 2);
      if (cooldown > heat_R[i]) {
        heat_R[i] = 0;
      } else {
        heat_R[i] = heat_R[i] - cooldown;
      }
    }

    // Propagate heat to the neighboring pixels on the left strip
    for (int k = leds_L->numPixels() - 1; k >= 2; k--) {
      heat_L[k] = (heat_L[k - 1] + heat_L[k - 2] + heat_L[k - 2]) / 3;
    }

    // Propagate heat to the neighboring pixels on the right strip
    for (int k = leds_R->numPixels() - 1; k >= 2; k--) {
      heat_R[k] = (heat_R[k - 1] + heat_R[k - 2] + heat_R[k - 2]) / 3;
    }

    // Add random sparking on the left strip
    if (random(255) < Sparking) {
      int y = random(7);
      heat_L[y] = heat_L[y] + random(160, 255);
    }

    // Add random sparking on the right strip
    if (random(255) < Sparking) {
      int y = random(7);
      heat_R[y] = heat_R[y] + random(160, 255);
    }

    // Update the left LED strip with heat values
    for (int j = 0; j < leds_L->numPixels(); j++) {
      setPixelHeatColor(leds_L, j, heat_L[j]);
    }

    // Update the right LED strip with heat values
    for (int j = 0; j < leds_R->numPixels(); j++) {
      setPixelHeatColor(leds_R, j, heat_R[j]);
    }

    leds_L->show();  // Show the updated left strip
    leds_R->show();  // Show the updated right strip
  }
}

/*___________________________________________________ FIRE ______________________________________*/
unsigned long lastFireUpdateTimes = 0;  // To track when to update the fire effect
int fireEffectDelay = map(EffectSpeed, 1, 255, 5, 200);

void fireEffect(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, int coolingFactor, int sparkingFactor) {
  static byte* fireHeat_L = new byte[leds_L->numPixels()];  // Heat array for the left strip
  static byte* fireHeat_R = new byte[leds_R->numPixels()];  // Heat array for the right strip
  int fireCooldown;

  unsigned long currentFireMillis = millis();  // Get current time

  // Only update fire every 'fireEffectDelay' milliseconds
  if (currentFireMillis - lastFireUpdateTimes >= fireEffectDelay) {
    lastFireUpdateTimes = currentFireMillis;  // Update last update time

    // Cool the pixels on the left strip
    for (int i = 0; i < leds_L->numPixels(); i++) {
      fireCooldown = random(0, ((coolingFactor * 10) / leds_L->numPixels()) + 2);
      if (fireCooldown > fireHeat_L[i]) {
        fireHeat_L[i] = 0;
      } else {
        fireHeat_L[i] = fireHeat_L[i] - fireCooldown;
      }
    }

    // Cool the pixels on the right strip
    for (int i = 0; i < leds_R->numPixels(); i++) {
      fireCooldown = random(0, ((coolingFactor * 10) / leds_R->numPixels()) + 2);
      if (fireCooldown > fireHeat_R[i]) {
        fireHeat_R[i] = 0;
      } else {
        fireHeat_R[i] = fireHeat_R[i] - fireCooldown;
      }
    }

    // Propagate heat to the neighboring pixels on the left strip
    for (int k = leds_L->numPixels() - 1; k >= 2; k--) {
      fireHeat_L[k] = (fireHeat_L[k - 1] + fireHeat_L[k - 2] + fireHeat_L[k - 2]) / 3;
    }

    // Propagate heat to the neighboring pixels on the right strip
    for (int k = leds_R->numPixels() - 1; k >= 2; k--) {
      fireHeat_R[k] = (fireHeat_R[k - 1] + fireHeat_R[k - 2] + fireHeat_R[k - 2]) / 3;
    }

    // Add random sparking on the left strip
    if (random(255) < sparkingFactor) {
      int sparkIndex = random(7);
      fireHeat_L[sparkIndex] = fireHeat_L[sparkIndex] + random(160, 255);
    }

    // Add random sparking on the right strip
    if (random(255) < sparkingFactor) {
      int sparkIndex = random(7);
      fireHeat_R[sparkIndex] = fireHeat_R[sparkIndex] + random(160, 255);
    }

    // Update the left LED strip with heat values and blend with base color
    for (int j = 0; j < leds_L->numPixels(); j++) {
      byte t192_L = round((fireHeat_L[j] / 255.0) * 191);
      byte heatramp_L = t192_L & 0x3F;
      heatramp_L <<= 2;
      byte red = (leftColor >> 16) & 0xFF;
      byte green = (leftColor >> 8) & 0xFF;
      byte blue = leftColor & 0xFF;

      if (t192_L > 0x80) {
        leds_L->setPixelColor(j, min(255, red + heatramp_L), min(255, green + heatramp_L), blue);
      } else if (t192_L > 0x40) {
        leds_L->setPixelColor(j, min(255, red + heatramp_L), green, blue);
      } else {
        leds_L->setPixelColor(j, red, green, min(255, blue + heatramp_L));
      }
    }

    // Update the right LED strip with heat values and blend with base color
    for (int j = 0; j < leds_R->numPixels(); j++) {
      byte t192_R = round((fireHeat_R[j] / 255.0) * 191);
      byte heatramp_R = t192_R & 0x3F;
      heatramp_R <<= 2;
      byte red = (RightColor >> 16) & 0xFF;
      byte green = (RightColor >> 8) & 0xFF;
      byte blue = RightColor & 0xFF;

      if (t192_R > 0x80) {
        leds_R->setPixelColor(j, min(255, red + heatramp_R), min(255, green + heatramp_R), blue);
      } else if (t192_R > 0x40) {
        leds_R->setPixelColor(j, min(255, red + heatramp_R), green, blue);
      } else {
        leds_R->setPixelColor(j, red, green, min(255, blue + heatramp_R));
      }
    }

    leds_L->show();  // Show the updated left strip
    leds_R->show();  // Show the updated right strip
  }
}



/*________________________________________________ RANDOM BURST ______________________________________*/
//--------------------------------------------- random color change-----------------------------------
unsigned long lastBurstTime = 0;  // To track when the next burst should happen

void randomBurst(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R) {
  unsigned long currentMillis = millis();  // Get the current time

  // Calculate burst delay based on EffectSpeed (map 1-255 to 5ms-200ms)
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // If the required time has passed since the last burst
  if (currentMillis - lastBurstTime >= Speed) {
    lastBurstTime = currentMillis;  // Update the last burst time

    // Randomly choose two unique indices for the LEDs on the left strip
    int idex1_L = random(0, leds_L->numPixels());
    int idex2_L = random(0, leds_L->numPixels());
    
    // Ensure both indices are not the same on the left strip
    while (idex2_L == idex1_L) {
      idex2_L = random(0, leds_L->numPixels());
    }

    // Randomly choose two unique indices for the LEDs on the right strip
    int idex1_R = random(0, leds_R->numPixels());
    int idex2_R = random(0, leds_R->numPixels());
    
    // Ensure both indices are not the same on the right strip
    while (idex2_R == idex1_R) {
      idex2_R = random(0, leds_R->numPixels());
    }

    // Random hue for both LEDs on the left strip
    int ihue1_L = random(0, 65530);
    int ihue2_L = random(0, 65530);

    // Random hue for both LEDs on the right strip
    int ihue1_R = random(0, 65530);
    int ihue2_R = random(0, 65530);

    // Set the two LEDs to random colors on the left strip
    leds_L->setPixelColor(idex1_L, leds_L->ColorHSV(ihue1_L, 255, 255));
    leds_L->setPixelColor(idex2_L, leds_L->ColorHSV(ihue2_L, 255, 255));

    // Set the two LEDs to random colors on the right strip
    leds_R->setPixelColor(idex1_R, leds_R->ColorHSV(ihue1_R, 255, 255));
    leds_R->setPixelColor(idex2_R, leds_R->ColorHSV(ihue2_R, 255, 255));

    // Display the bursts on both strips
    leds_L->show();
    leds_R->show();

    // Clear the pixels on both strips after a short time
    leds_L->clear();
    leds_R->clear();
    leds_L->show();
    leds_R->show();
  }
}


/*______________________________________________ FLICKER ______________________________________________*/
//-----------------------------------------random strobe light------------------------------------------
unsigned long previousMillis = 0;  // To store the last time the flicker occurred
bool flickerState = false;  // Tracks whether flickering is active or not

void flicker(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R) {
  unsigned long currentMillis = millis();  // Get the current time
  int flickerInterval = map(EffectSpeed, 1, 255, 5, 200);

  // Check if it's time for the next flicker
  if (currentMillis - previousMillis >= flickerInterval) {
    previousMillis = currentMillis;  // Save the current time for the next check

    // Generate random brightness and color for the flicker on the left strip
    int random_bright_L = random(0, 255);
    int random_bool_L = random(0, random_bright_L);

    // Generate random brightness and color for the flicker on the right strip
    int random_bright_R = random(0, 255);
    int random_bool_R = random(0, random_bright_R);

    // If the random condition is met, simulate the flicker on the left strip
    if (random_bool_L < 10) {
      // Set all pixels to the flicker color (e.g., yellowish) on the left strip
      for (int i = 0; i < leds_L->numPixels(); i++) {
        leds_L->setPixelColor(i, leds_L->ColorHSV(160, 50, random_bright_L));
      }
      leds_L->show();  // Update the left strip with the new color
    } else {
      // Optionally turn off all LEDs when no flicker is needed on the left strip
      leds_L->clear();
      leds_L->show();
    }

    // If the random condition is met, simulate the flicker on the right strip
    if (random_bool_R < 10) {
      // Set all pixels to the flicker color (e.g., yellowish) on the right strip
      for (int i = 0; i < leds_R->numPixels(); i++) {
        leds_R->setPixelColor(i, leds_R->ColorHSV(160, 50, random_bright_R));
      }
      leds_R->show();  // Update the right strip with the new color
    } else {
      // Optionally turn off all LEDs when no flicker is needed on the right strip
      leds_R->clear();
      leds_R->show();
    }
  }
}

/* ________________________________________ RANDOM COLOR POP ________________________________________*/
//-------------------------------- the madness of random flashes -------------------------------------
unsigned long lastPopTime = 0;  // To track when the next color pop should happen
void randomColorPop(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R) {
  unsigned long currentMillis = millis();  // Get the current time
  int popDelay = map(EffectSpeed, 1, 255, 5, 200);

  // Check if enough time has passed since the last color pop
  if (currentMillis - lastPopTime >= popDelay) {
    lastPopTime = currentMillis;  // Update the last pop time

    // Choose a random index for the left strip
    int idex_L = random(0, leds_L->numPixels());
    leds_L->clear();  // Clear previous colors
    leds_L->setPixelColor(idex_L, leds_L->Color(random(0, 255), random(0, 255), random(0, 255), random(0, 255)));
    leds_L->show();  // Display the new color on the left strip

    // Choose a random index for the right strip
    int idex_R = random(0, leds_R->numPixels());
    leds_R->clear();  // Clear previous colors
    leds_R->setPixelColor(idex_R, leds_R->Color(random(0, 255), random(0, 255), random(0, 255), random(0, 255)));
    leds_R->show();  // Display the new color on the right strip
  }
}

/*___________________________________________ SPARKLE ________________________________________________*/
//-----------------------------------random flashes of white--------------------------------------
unsigned long lastSparkleTime = 0;  // To track the last time the sparkle was shown

void sparkle(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R) {
  unsigned long currentMillis = millis();  // Get the current time
  int SparkleSpeed = map(EffectSpeed, 1, 255, 5, 200);

  // Check if enough time has passed to trigger the next sparkle
  if (currentMillis - lastSparkleTime >= SparkleSpeed) {
    lastSparkleTime = currentMillis;  // Update the last sparkle time

    // Choose a random pixel on the left strip
    int Pixel_L = random(leds_L->numPixels());
    // Choose a random pixel on the right strip
    int Pixel_R = random(leds_R->numPixels());

    // Generate random RGB values for the left strip pixel
    byte red_L = random(0, 256);    // Random red value (0 to 255)
    byte green_L = random(0, 256);  // Random green value (0 to 255)
    byte blue_L = random(0, 256);   // Random blue value (0 to 255)

    // Generate random RGB values for the right strip pixel
    byte red_R = random(0, 256);    // Random red value (0 to 255)
    byte green_R = random(0, 256);  // Random green value (0 to 255)
    byte blue_R = random(0, 256);   // Random blue value (0 to 255)

    // Set the random color on the chosen pixel on the left strip
    leds_L->setPixelColor(Pixel_L, red_L, green_L, blue_L);
    leds_L->show();  // Display the sparkle on the left strip

    // Set the random color on the chosen pixel on the right strip
    leds_R->setPixelColor(Pixel_R, red_R, green_R, blue_R);
    leds_R->show();  // Display the sparkle on the right strip

    // Turn off the sparkle after a brief moment on the left strip
    leds_L->setPixelColor(Pixel_L, 0, 0, 0);
    leds_L->show();  // Turn off the sparkle on the left strip

    // Turn off the sparkle after a brief moment on the right strip
    leds_R->setPixelColor(Pixel_R, 0, 0, 0);
    leds_R->show();  // Turn off the sparkle on the right strip
  }
}

/*____________________________________________ COLOR BOUNCE ___________________________________________*/
//--------------------------------------------running pixel---------------------------------------------
void colorBounce(Adafruit_NeoPixel *strip, uint32_t stripColor) {
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == strip->numPixels()) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  for (int i = 0; i < strip->numPixels(); i++) {
    if (i == idex) {
      strip->setPixelColor(i, strip->Color((stripColor >> 16) & 0xFF, (stripColor >> 8) & 0xFF, stripColor & 0xFF));
    } else {
      strip->setPixelColor(i, strip->Color(0, 0, 0));
    }
  }
  strip->show();
  delay(EffectSpeed);
}



/*________________________________________ COLOR BOUNCE FADE __________________________________________________*/
//-------------------------------------running train of pixels-------------------------------------------------
int adjacent_cw(uint16_t NumLeds, int i) {
  int r;
  if (i < NumLeds - 1) {
    r = i + 1;
  } else {
    r = 0;
  }
  return r;
}


int adjacent_ccw(uint16_t NumLeds, int i) {
  int r;
  if (i > 0) {
    r = i - 1;
  } else {
    r = NumLeds - 1;
  }
  return r;
}


void colorBounceFade(Adafruit_NeoPixel *strip, uint32_t stripColor) {
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == strip->numPixels()) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  int iL1 = adjacent_cw(strip->numPixels(), idex);
  int iL2 = adjacent_cw(strip->numPixels(), iL1);
  int iL3 = adjacent_cw(strip->numPixels(), iL2);
  int iR1 = adjacent_ccw(strip->numPixels(), idex);
  int iR2 = adjacent_ccw(strip->numPixels(), iR1);
  int iR3 = adjacent_ccw(strip->numPixels(), iR2);

  for (int i = 0; i < strip->numPixels(); i++) {
    if (i == idex) {
      strip->setPixelColor(i, stripColor);
    } else if (i == iL1) {
      strip->setPixelColor(i, strip->Color(((stripColor >> 16) & 0xFF) * 0.6, ((stripColor >> 8) & 0xFF) * .6, (stripColor & 0xFF)) * .6);
    } else if (i == iL2) {
      strip->setPixelColor(i, strip->Color(((stripColor >> 16) & 0xFF) * 0.3, ((stripColor >> 8) & 0xFF) * .3, (stripColor & 0xFF)) * .3);
    } else if (i == iL3) {
      strip->setPixelColor(i, strip->Color(((stripColor >> 16) & 0xFF) * 0.08, ((stripColor >> 8) & 0xFF) * .08, (stripColor & 0xFF)) * .08);
    } else if (i == iR1) {
      strip->setPixelColor(i, strip->Color(((stripColor >> 16) & 0xFF) * 0.6, ((stripColor >> 8) & 0xFF) * .6, (stripColor & 0xFF)) * .6);
    } else if (i == iR2) {
      strip->setPixelColor(i, strip->Color(((stripColor >> 16) & 0xFF) * 0.3, ((stripColor >> 8) & 0xFF) * .3, (stripColor & 0xFF)) * .3);
    } else if (i == iR3) {
      strip->setPixelColor(i, strip->Color(((stripColor >> 16) & 0xFF) * 0.08, ((stripColor >> 8) & 0xFF) * .08, (stripColor & 0xFF)) * .08);
    } else {
      strip->setPixelColor(i, strip->ColorHSV(0, 0, 0));
    }
  }
  strip->show();
  delay(EffectSpeed);
}



/*_____________________________________________ RED BLUE BOUNCE ______________________________________________*/
int antipodal_index(uint16_t TOP_INDEX, int i) {
  int iN = i + TOP_INDEX;
  if (i >= TOP_INDEX) {
    iN = (i + TOP_INDEX) % (TOP_INDEX * 2);
  }
  return iN;
}

void redBlueBounce(Adafruit_NeoPixel *strip) {
  idex++;
  if (idex >= strip->numPixels()) {
    idex = 0;
  }
  int idexR = idex;
  int idexB = antipodal_index(strip->numPixels() / 2, idexR);
  int thathue = (hue + 160) % 255;

  for (int i = 0; i < strip->numPixels(); i++) {
    if (i == idexR) {
      strip->setPixelColor(i, strip->ColorHSV(hue, isat, 255));
    } else if (i == idexB) {
      strip->setPixelColor(i, strip->ColorHSV(thathue, isat, 255));
      leds_R->setPixelColor(i, leds_R->ColorHSV(thathue, isat, 255));
    } else {
      strip->setPixelColor(i, strip->ColorHSV(0, 0, 0));
    }
  }
  strip->show();
  delay(EffectSpeed);
}



/*____________________________________________ ROTATING RED/BLUE _______________________________________________*/
//---------------------------------------------red/blue rotation-------------------------------------------------
void rotatingRedBlue(Adafruit_NeoPixel *strip) {
  idex++;
  if (idex >= strip->numPixels()) {
    idex = 0;
  }
  int idexR = idex;
  int idexB = antipodal_index(strip->numPixels() / 2, idexR);
  strip->setPixelColor(idexR, strip->Color(255, 0, 0, 0));
  strip->setPixelColor(idexB, strip->Color(0, 0, 255, 0));
  strip->show();
  delay(EffectSpeed);
}



/*_________________________________________________ RADIATION _________________________________________________*/
void radiation(Adafruit_NeoPixel *strip) {
  uint16_t NumLeds = strip->numPixels();
  //fadeall();
  int N3 = int(NumLeds / 3);
  int N6 = int(NumLeds / 6);
  int N12 = int(NumLeds / 12);
  for (int i = 0; i < N6; i++) {
    rcount = rcount + .02;
    if (rcount > 3.14) {
      rcount = 0.0;
    }
    ibright = int(sin(rcount) * 255);
    int j0 = (i + NumLeds - N12) % NumLeds;
    int j1 = (j0 + N3) % NumLeds;
    int j2 = (j1 + N3) % NumLeds;
    strip->setPixelColor(j0, strip->ColorHSV(hue, isat, ibright));
    strip->setPixelColor(j1, strip->ColorHSV(hue, isat, ibright));
    strip->setPixelColor(j2, strip->ColorHSV(hue, isat, ibright));
  }
  strip->show();
  delay(EffectSpeed);
}



/*____________________________________________ PACMAN __________________________________________________*/
//------------------------------------- pacman chomping effect------------------------------------------
int pcounter = 0;
void pacman(Adafruit_NeoPixel *strip) {
  uint16_t NumLeds = strip->numPixels();
  int s = int(NumLeds / 4);
  pcounter++;
  if (pcounter > 5) {
    pcounter = 0;
  }
  if (pcounter == 0) {
    for (int i = 0; i < NumLeds; i++) {
      strip->setPixelColor(i, strip->Color(255, 255, 0, 0));
    }
  }
  if (pcounter == 1 || pcounter == 5) {
    strip->fill(strip->Color(255, 255, 0, 0), 0, NumLeds - 1);
    strip->setPixelColor(s, strip->Color(0, 0, 0, 0));
  }
  if (pcounter == 2 || pcounter == 4) {
    strip->fill(strip->Color(255, 255, 0, 0), 0, NumLeds - 1);
    strip->setPixelColor(s - 1, strip->Color(0, 0, 0, 0));
    strip->setPixelColor(s, strip->Color(0, 0, 0, 0));
    strip->setPixelColor(s + 1, strip->Color(0, 0, 0, 0));
  }
  if (pcounter == 3) {
    strip->fill(strip->Color(255, 255, 0, 0), 0, NumLeds - 1);
    strip->setPixelColor(s - 2, strip->Color(0, 0, 0, 0));
    strip->setPixelColor(s - 1, strip->Color(0, 0, 0, 0));
    strip->setPixelColor(s, strip->Color(0, 0, 0, 0));
    strip->setPixelColor(s + 1, strip->Color(0, 0, 0, 0));
    strip->setPixelColor(s + 2, strip->Color(0, 0, 0, 0));
  }
  strip->show();
  delay(_delay);
}



/*____________________________________________________ POP HORIZONTAL _________________________________________________*/
//-----------------------------------------pop from left to right up the ring-------------------------------------------
void popHorizontal(Adafruit_NeoPixel *strip, uint32_t stripColor) {
  uint16_t TOP_INDEX = uint8_t(strip->numPixels() / 2);
  int ix;
  if (bouncedirection == 0) {
    bouncedirection = 1;
    ix = idex;
  } else if (bouncedirection == 1) {
    bouncedirection = 0;
    ix = horizontal_index(idex, TOP_INDEX);
    idex++;
    if (idex > TOP_INDEX) {
      idex = 0;
    }
  }
  for (int i = 0; i < strip->numPixels(); i++) {
    if (i == ix) {
      strip->setPixelColor(i, stripColor);
    } else {
      strip->clear();
    }
  }
  strip->show();
  delay(EffectSpeed);
}



/*______________________________________________________ SNOW SPARKLE _____________________________________________________*/
void snowSparkle(Adafruit_NeoPixel *strip) {
  uint8_t red = 0x10;
  uint8_t green = 0x10;
  uint8_t blue = 0x10;
  uint8_t sparkleDelay = 40;
  uint8_t speedDelay = random(100, 1000);
  uint16_t NumLeds = strip->numPixels();
  strip->fill(strip->Color(red, green, blue, 255), 0, NumLeds - 1);

  int pixel = random(NumLeds);
  strip->setPixelColor(pixel, strip->Color(0xff, 0xff, 0xff, 0xFF));
  strip->show();
  delay(sparkleDelay);
  strip->setPixelColor(pixel, strip->Color(red, green, blue));
  strip->show();
  delay(speedDelay);
}



/*______________________________________________________ RWB MARCH ___________________________________________________*/
//------------------------------------------- white blue red run in a circle  -----------------------------------------
void rwbMarch(Adafruit_NeoPixel *strip) {
  int iCCW;
  idex++;
  if (idex > 2) {
    idex = 0;
  }
  switch (idex) {
    case 0:
      strip->setPixelColor(0, strip->Color(255, 0, 0));
      break;
    case 1:
      strip->setPixelColor(0, strip->Color(255, 255, 255));
      break;
    case 2:
      strip->setPixelColor(0, strip->Color(0, 0, 255));
      break;
  }
  for (int i = 1; i < strip->numPixels(); i++) {
    iCCW = adjacent_ccw(strip->numPixels(), i);
    strip->setPixelColor(i, strip->getPixelColor(iCCW));
  }
  strip->show();
  delay(EffectSpeed);
}



/*_____________________________________________________ FLAME ______________________________________________________*/
//-------------------------------------------------- flame effect----------------------------------------------------
void flame(Adafruit_NeoPixel *strip) {
  uint16_t TOP_INDEX = strip->numPixels() / 2;
  int idelay = random(0, 20);
  float hmin = 0.1;
  float hmax = 45.0;
  float hdif = hmax - hmin;
  int randtemp = random(0, 3);
  float hinc = (hdif / float(TOP_INDEX)) + randtemp;
  int ihue = hmin;
  for (int i = 0; i <= TOP_INDEX; i++) {
    ihue = ihue + hinc;
    strip->setPixelColor(i, strip->ColorHSV(ihue, isat, 255));
    leds_R->setPixelColor(i, leds_R->ColorHSV(ihue, isat, 255));
    int ih = horizontal_index(strip->numPixels(), i);
    strip->setPixelColor(ih, strip->ColorHSV(ihue, isat, 255));
    strip->setPixelColor(TOP_INDEX, strip->Color(160, 160, 160));
    strip->show();
    delay(idelay);
  }
}



/*___________________________________________________ CandyCane _______________________________________________*/
void CandyCane(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, uint32_t leftColor, uint32_t rightColor, int iterations) {
  int numPixels_L = leds_L->numPixels();  // Get the number of pixels on the left strip
  int numPixels_R = leds_R->numPixels();  // Get the number of pixels on the right strip
  static int offset_L = 0;  // Static variable to maintain offset for the left strip
  static int offset_R = 0;  // Static variable to maintain offset for the right strip
  static unsigned long previousMillis = 0;  // To track time for non-blocking animation
  unsigned long currentMillis = millis();
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Loop for the number of iterations (apply this effect for both strips)
  for (int j = 0; j < iterations; j++) {
    // Check if the delay has passed (non-blocking)
    if (currentMillis - previousMillis >= Speed) {
      previousMillis = currentMillis;  // Update the last time we updated the LED strips

      // Update the left strip colors based on the offset
      for (int i = 0; i < numPixels_L; i++) {
        uint32_t color = ((i + offset_L) % 6 < 3) ? leftColor : rightColor;
        // Only set the color if it's different from the current color (optimization)
        if (leds_L->getPixelColor(i) != color) {
          leds_L->setPixelColor(i, color);
        }
      }

      // Update the right strip colors based on the offset
      for (int i = 0; i < numPixels_R; i++) {
        uint32_t color = ((i + offset_R) % 6 < 3) ? leftColor : rightColor;
        // Only set the color if it's different from the current color (optimization)
        if (leds_R->getPixelColor(i) != color) {
          leds_R->setPixelColor(i, color);
        }
      }

      // Refresh the strips with the updated colors
      leds_L->show();  // Refresh the left strip
      leds_R->show();  // Refresh the right strip

      // Update offsets for the next iteration of the candy cane pattern
      offset_L = (offset_L + 1) % 6;
      offset_R = (offset_R + 1) % 6;
    }

    currentMillis = millis();  // Update the current time
  }
}


/*_______________________________________________ TheaterChase______________________________________________________*/

void theaterChaseRainbow(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R) {
  unsigned long currentMillis = millis();  // Get current time

  int TheaterSpeed = map(EffectSpeed, 1, 255, 5, 200);

  // Check if it's time to update the animation
  if (currentMillis - previousMillis >= TheaterSpeed) {
    previousMillis = currentMillis;  // Update the last time

    // Generate a random color for the chase
    byte red = random(0, 256);    // Random red value (0 to 255)
    byte green = random(0, 256);  // Random green value (0 to 255)
    byte blue = random(0, 256);   // Random blue value (0 to 255)

    // Turn off all pixels first on both LED strips
    for (int i = 0; i < leds_L->numPixels(); i++) {
      leds_L->setPixelColor(i, 0, 0, 0);
    }
    for (int i = 0; i < leds_R->numPixels(); i++) {
      leds_R->setPixelColor(i, 0, 0, 0);
    }

    // Turn on every third pixel, based on the current step (currentStep mod 3) for both strips
    for (int i = currentStep; i < leds_L->numPixels(); i += 3) {
      leds_L->setPixelColor(i, red, green, blue);
    }
    for (int i = currentStep; i < leds_R->numPixels(); i += 3) {
      leds_R->setPixelColor(i, red, green, blue);
    }

    // Show the update on both strips
    leds_L->show();
    leds_R->show();

    // Move to the next step (0, 1, or 2)
    currentStep = (currentStep + 1) % 3;  // Keeps the step within 0, 1, or 2
  }
}




/*__________________________________________________________ STROBE _______________________________________________________*/
//---------------------------------------------------- stroboscopic effect -------------------------------------------------
unsigned long flashDelayMillis = 0;
unsigned long endPauseMillis = 0;
int strobeStep = 0;
int currentStrobeCount = 0;

void strobe(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, byte red, byte green, byte blue, int StrobeCount,int EndPause) {
  unsigned long currentMillis = millis();
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Initializing step and timing when the function is first called
  if (strobeStep == 0) {
    previousMillis = currentMillis;
    flashDelayMillis = Speed;
    endPauseMillis = EndPause;
    currentStrobeCount = 0;
    strobeStep = 1; // Proceed to the first flash
  }

  // Handle strobe flashes for both strips
  if (strobeStep == 1 && currentStrobeCount < StrobeCount) {
    if (currentMillis - previousMillis >= flashDelayMillis) {
      previousMillis = currentMillis;

      // Toggle between turning the LEDs on and off for both strips
      if (leds_L->getPixelColor(0) == 0) {
        leds_L->fill(leds_L->Color(red, green, blue, 0), 0, leds_L->numPixels());
      } else {
        leds_L->clear();
      }

      if (leds_R->getPixelColor(0) == 0) {
        leds_R->fill(leds_R->Color(red, green, blue, 0), 0, leds_R->numPixels());
      } else {
        leds_R->clear();
      }

      leds_L->show();  // Update the left strip
      leds_R->show();  // Update the right strip

      currentStrobeCount++;
      
      // If the count reaches the number of strobe flashes, move to the end pause
      if (currentStrobeCount >= StrobeCount) {
        strobeStep = 2;  // End pause step
        previousMillis = currentMillis;  // Reset timer for end pause
      }
    }
  }

  // Handle the end pause for both strips
  if (strobeStep == 2) {
    if (currentMillis - previousMillis >= endPauseMillis) {
      strobeStep = 0;  // Reset for the next strobe sequence
    }
  }
}

/* ____________________________________________________ POLICE BLINKER ____________________________________________________*/
int blinkerStep = 0;
bool isBluePhase = true;
int blinkCount = 0;

void policeBlinker(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R) {
  unsigned long currentMillis = millis();
  uint16_t NumLeds_L = leds_L->numPixels();  // Number of LEDs on the left strip
  uint16_t NumLeds_R = leds_R->numPixels();  // Number of LEDs on the right strip
  int PoliceSpeed = map(EffectSpeed, 1, 255, 5, 200);
  // Check if it's time to update the state
  if (currentMillis - previousMillis >= PoliceSpeed) {
    previousMillis = currentMillis;  // Update the time tracker

    // Alternate between blue and red phases for both strips
    if (isBluePhase) {
      if (blinkerStep == 0) {
        // Turn on the blue lights on the left half of the left strip
        for (int i = 0; i < NumLeds_L / 2; i++) {
          leds_L->setPixelColor(i, leds_L->Color(0, 0, 255));  // Blue color
        }
        leds_L->show();  // Update the left strip
        
        // Turn on the blue lights on the left half of the right strip
        for (int i = 0; i < NumLeds_R / 2; i++) {
          leds_R->setPixelColor(i, leds_R->Color(0, 0, 255));  // Blue color
        }
        leds_R->show();  // Update the right strip

        blinkerStep = 1;
      } else {
        // Turn off the lights on both strips
        leds_L->clear();
        leds_R->clear();
        leds_L->show();
        leds_R->show();
        blinkerStep = 0;
        blinkCount++;
      }

      // Switch to red phase after 3 blinks
      if (blinkCount >= 3) {
        blinkCount = 0;
        isBluePhase = false;
      }
    } else {
      if (blinkerStep == 0) {
        // Turn on the red lights on the right half of the left strip
        for (int i = NumLeds_L / 2; i < NumLeds_L; i++) {
          leds_L->setPixelColor(i, leds_L->Color(255, 0, 0));  // Red color
        }
        leds_L->show();  // Update the left strip

        // Turn on the red lights on the right half of the right strip
        for (int i = NumLeds_R / 2; i < NumLeds_R; i++) {
          leds_R->setPixelColor(i, leds_R->Color(255, 0, 0));  // Red color
        }
        leds_R->show();  // Update the right strip

        blinkerStep = 1;
      } else {
        // Turn off the lights on both strips
        leds_L->clear();
        leds_R->clear();
        leds_L->show();
        leds_R->show();
        blinkerStep = 0;
        blinkCount++;
      }

      // Switch to blue phase after 3 blinks
      if (blinkCount >= 3) {
        blinkCount = 0;
        isBluePhase = true;
      }
    }
  }
}



/*______________________________________________________ KITT ________________________________________________________________*/
void kitt(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, uint32_t leftColor,uint32_t RightColor) {
    int Speed = map(EffectSpeed, 1, 255, 5, 200);

  uint16_t TOP_INDEX_L = leds_L->numPixels() / 2;  // Middle index for left strip
  uint16_t TOP_INDEX_R = leds_R->numPixels() / 2;  // Middle index for right strip

  int rand = random(0, TOP_INDEX_L) * 2;  // Random range for how many LEDs will light up

  unsigned long startMillis = millis();

  // Left strip: create the KITT pattern on the left
  for (int i = 0; i < rand; i++) {
    leds_L->setPixelColor(TOP_INDEX_L + i, leftColor);  // Set the LED to the color
    leds_L->setPixelColor(TOP_INDEX_L - i, leftColor);  // Set the LED to the color
    leds_L->show();
    while (millis() - startMillis < Speed / (rand * 2)) {}
  }

  // Right strip: create the KITT pattern on the right
  for (int i = 0; i < rand; i++) {
    leds_R->setPixelColor(TOP_INDEX_R + i, RightColor);  // Set the LED to the color
    leds_R->setPixelColor(TOP_INDEX_R - i, RightColor);  // Set the LED to the color
    leds_R->show();
    while (millis() - startMillis < Speed / (rand * 2)) {}
  }

  startMillis = millis();

  // Left strip: reset LEDs after the KITT pattern
  for (int i = rand; i > 0; i--) {
    leds_L->setPixelColor(TOP_INDEX_L + i, leds_L->Color(0, 0, 0));  // Turn off the LED
    leds_L->setPixelColor(TOP_INDEX_L - i, leds_L->Color(0, 0, 0));  // Turn off the LED
    leds_L->show();
    while (millis() - startMillis < _delay / (rand)) {}
  }

  // Right strip: reset LEDs after the KITT pattern
  for (int i = rand; i > 0; i--) {
    leds_R->setPixelColor(TOP_INDEX_R + i, leds_R->Color(0, 0, 0));  // Turn off the LED
    leds_R->setPixelColor(TOP_INDEX_R - i, leds_R->Color(0, 0, 0));  // Turn off the LED
    leds_R->show();
    while (millis() - startMillis < Speed / (rand)) {}
  }
}


/*____________________________________________________ FADE VERTICAL _________________________________________________________*/
//-----------------------------------------------smooth brightness change-----------------------------------------------------
int horizontal_index(int i, int TOP_INDEX) {
  int EVENODD = (TOP_INDEX * 2) % 2;
  if (i == 0) {
    return 0;
  }
  if (i == TOP_INDEX && EVENODD == 1) {
    return TOP_INDEX + 1;
  }
  if (i == TOP_INDEX && EVENODD == 0) {
    return TOP_INDEX;
  }
  return TOP_INDEX * 2 - i;
}

void fadeVertical(Adafruit_NeoPixel *strip, uint32_t stripColor) {
  uint16_t TOP_INDEX = strip->numPixels() / 2;
  idex++;
  if (idex > TOP_INDEX) {
    idex = 0;
  }
  int idexA = idex;
  int idexB = horizontal_index(idexA, TOP_INDEX);
  ibright = ibright + 10;
  if (ibright > 255) {
    ibright = 0;
  }
  strip->setPixelColor(idexA, strip->Color(((stripColor >> 16) & 0xFF) * map(ibright, 0, 255, 0, 1), ((stripColor >> 8) & 0xFF) * map(ibright, 0, 255, 0, 1), (stripColor & 0xFF)) * map(ibright, 0, 255, 0, 1));
  strip->setPixelColor(idexB, strip->Color(((stripColor >> 16) & 0xFF) * map(ibright, 0, 255, 0, 1), ((stripColor >> 8) & 0xFF) * map(ibright, 0, 255, 0, 1), (stripColor & 0xFF)) * map(ibright, 0, 255, 0, 1));
  strip->show();
  delay(_delay);
}



/*_____________________________________________________ RUNNER CHAMELEON ___________________________________________________________*/
//----------------------------------------------a steam train running in a circle----------------------------------------------------
void runnerChameleon(Adafruit_NeoPixel *strip, uint32_t stripColor) {
  for (int i = 0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, stripColor);
    strip->show();
    delay(10);
    strip->clear();
    strip->show();
  }
}




void blende() {
  for (int i = 0; i < leds_L->numPixels(); i++) {
    leds_L->setPixelColor(i, leftColor);
    leds_L->show();
    leds_R->setPixelColor(i, RightColor);
    leds_R->show();
    leds_3->setPixelColor(i, thrdColor);
    leds_3->show();
    delay(EffectSpeed);
    fadeall();
  }
}

/*______________________________________________________ BLENDE 2 ___________________________________________________________*/
void blende_2(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R ) {
  // Blend effect for left strip (leds_L)
  for (int i = 0; i < leds_L->numPixels(); i++) {
    leds_L->setPixelColor(i, leftColor);
    leds_L->show();
    delay(10);  // Small delay for blending effect
    fadeall();  // Assume fadeall() is implemented elsewhere
  }

  // Blend effect for right strip (leds_R)
  for (int i = 0; i < leds_R->numPixels(); i++) {
    leds_R->setPixelColor(i, RightColor);
    leds_R->show();
    delay(10);  // Small delay for blending effect
    fadeall();  // Assume fadeall() is implemented elsewhere
  }

  // Reverse blending for left strip (leds_L)
  for (int i = leds_L->numPixels() - 1; i >= 0; i--) {
    leds_L->setPixelColor(i, leftColor);
    leds_L->show();
    delay(10);  // Small delay for blending effect
    fadeall();  // Assume fadeall() is implemented elsewhere
  }

  // Reverse blending for right strip (leds_R)
  for (int i = leds_R->numPixels() - 1; i >= 0; i--) {
    leds_R->setPixelColor(i, RightColor);
    leds_R->show();
    delay(10);  // Small delay for blending effect
    fadeall();  // Assume fadeall() is implemented elsewhere
  }
}

/*________________________________________________ CENTER TO OUTSIDE ________________________________________________________*/
unsigned long previousReturnMillis = 0;
bool animationRunning = true;
bool returning = false;

void CenterToOutside(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, uint32_t stripColor, int EyeSize ,int ReturnDelay) {
  byte red = (stripColor >> 16) & 0xFF;
  byte green = (stripColor >> 8) & 0xFF;
  byte blue = stripColor & 0xFF;
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  unsigned long currentMillis = millis();
  int centerIndex_L = leds_L->numPixels() / 2;  // Find the center of the left strip
  int centerIndex_R = leds_R->numPixels() / 2;  // Find the center of the right strip

  // Check if it's time to update the animation
  if (animationRunning && (currentMillis - previousMillis >= Speed)) {
    previousMillis = currentMillis;

    // Clear the strips before updating
    leds_L->clear();
    leds_R->clear();
    leds_L->show();
    leds_R->show();

    if (currentStep < centerIndex_L) {
      // Move outward from the center on the left strip
      int leftIndex_L = centerIndex_L - currentStep - 1;   // Left side index on the left strip
      int rightIndex_L = centerIndex_L + currentStep + 1;  // Right side index on the left strip

      // Set pixel colors for the left strip
      leds_L->setPixelColor(leftIndex_L, red / 10, green / 10, blue / 10);  // Dim edge pixel
      for (int j = 1; j <= EyeSize; j++) {
        leds_L->setPixelColor(leftIndex_L + j, red, green, blue);  // Eye pixels on the left side
      }
      leds_L->setPixelColor(leftIndex_L + EyeSize + 1, red / 10, green / 10, blue / 10);  // Dim next pixel

      leds_L->setPixelColor(rightIndex_L, red / 10, green / 10, blue / 10);  // Dim edge pixel
      for (int j = 1; j <= EyeSize; j++) {
        leds_L->setPixelColor(rightIndex_L - j, red, green, blue);  // Eye pixels on the right side
      }
      leds_L->setPixelColor(rightIndex_L - EyeSize - 1, red / 10, green / 10, blue / 10);  // Dim next pixel

      // Move outward from the center on the right strip
      int leftIndex_R = centerIndex_R - currentStep - 1;   // Left side index on the right strip
      int rightIndex_R = centerIndex_R + currentStep + 1;  // Right side index on the right strip

      // Set pixel colors for the right strip
      leds_R->setPixelColor(leftIndex_R, red / 10, green / 10, blue / 10);  // Dim edge pixel
      for (int j = 1; j <= EyeSize; j++) {
        leds_R->setPixelColor(leftIndex_R + j, red, green, blue);  // Eye pixels on the left side
      }
      leds_R->setPixelColor(leftIndex_R + EyeSize + 1, red / 10, green / 10, blue / 10);  // Dim next pixel

      leds_R->setPixelColor(rightIndex_R, red / 10, green / 10, blue / 10);  // Dim edge pixel
      for (int j = 1; j <= EyeSize; j++) {
        leds_R->setPixelColor(rightIndex_R - j, red, green, blue);  // Eye pixels on the right side
      }
      leds_R->setPixelColor(rightIndex_R - EyeSize - 1, red / 10, green / 10, blue / 10);  // Dim next pixel

      leds_L->show();
      leds_R->show();

      currentStep++;
    } else {
      // End of animation, prepare for return delay
      animationRunning = false;
      returning = true;
      previousReturnMillis = currentMillis;
    }
  }

  // Return delay before restarting the animation
  if (returning && (currentMillis - previousReturnMillis >= ReturnDelay)) {
    currentStep = 0;  // Reset step
    animationRunning = true;  // Start a new animation
    returning = false;  // End the return phase
  }
}

/*_________________________________________________ RANDOM RED _______________________________________________________*/
void random_red(Adafruit_NeoPixel *strip) {
  strip->clear();
  strip->show();
  int temprand;
  for (int i = 0; i < strip->numPixels(); i++) {
    temprand = random(0, 100);
    if (temprand > 50) {
      strip->setPixelColor(i, strip->Color(255, 0, 0));
    }
    if (temprand <= 50) {
      strip->setPixelColor(i, strip->Color(0, 0, 0, 0));
    }
  }
  strip->show();
}



/*________________________________________________ OUTSIDE TO CENTER ____________________________________________________*/
void OutsideToCenter(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, uint32_t stripColor, int EyeSize, int ReturnDelay) {
  byte red = (stripColor >> 16) & 0xFF;
  byte green = (stripColor >> 8) & 0xFF;
  byte blue = stripColor & 0xFF;

  unsigned long currentMillis = millis();
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Get the number of LEDs for each strip
  int numLeds_L = leds_L->numPixels();
  int numLeds_R = leds_R->numPixels();

  // Calculate the center index for each strip
  int centerIndex_L = numLeds_L / 2;
  int centerIndex_R = numLeds_R / 2;

  // Check if it's time to update the animation
  if (animationRunning && (currentMillis - previousMillis >= Speed)) {
    previousMillis = currentMillis;

    // Clear both LED strips
    leds_L->clear();
    leds_R->clear();

    int i = currentStep;
    if (i <= (numLeds_L - EyeSize)) {
      // Left side LEDs
      leds_L->setPixelColor(centerIndex_L - i - 1, red / 10, green / 10, blue / 10); // Dim pixel
      for (int j = 1; j <= EyeSize; j++) {
        leds_L->setPixelColor(centerIndex_L - i + j, red, green, blue); // Eye pixels
      }
      leds_L->setPixelColor(centerIndex_L - i + EyeSize + 1, red / 10, green / 10, blue / 10); // Dim next pixel

      // Right side LEDs
      leds_R->setPixelColor(centerIndex_R + i + 1, red / 10, green / 10, blue / 10); // Dim pixel
      for (int j = 1; j <= EyeSize; j++) {
        leds_R->setPixelColor(centerIndex_R + i - j, red, green, blue); // Eye pixels
      }
      leds_R->setPixelColor(centerIndex_R + i - EyeSize - 1, red / 10, green / 10, blue / 10); // Dim next pixel

      // Show updates on both strips
      leds_L->show();
      leds_R->show();

      currentStep++;
    } else {
      // End of animation, prepare for return delay
      animationRunning = false;
      returning = true;
      previousReturnMillis = currentMillis;
    }
  }

  // Return delay before restarting the animation
  if (returning && (currentMillis - previousReturnMillis >= ReturnDelay)) {
    currentStep = 0;  // Reset step
    animationRunning = true;  // Start a new animation
    returning = false;  // End the return phase
  }
}


/*__________________________________________________ LEFT TO RIGHT ______________________________________________________*/
void LeftToRight(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, uint32_t stripColor, int EyeSize,int ReturnDelay) {
  byte red = (stripColor >> 16) & 0xFF;
  byte green = (stripColor >> 8) & 0xFF;
  byte blue = stripColor & 0xFF;

  unsigned long currentMillis = millis();
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Get the number of LEDs for each strip
  int numLeds_L = leds_L->numPixels();
  int numLeds_R = leds_R->numPixels();

  // Check if it's time to update the animation
  if (animationRunning && (currentMillis - previousMillis >= Speed)) {
    previousMillis = currentMillis;

    // Clear both LED strips
    leds_L->clear();
    leds_R->clear();

    if (currentStep < numLeds_L - EyeSize) {
      // Left strip animation
      leds_L->setPixelColor(currentStep, red / 10, green / 10, blue / 10); // Dim pixel
      for (int j = 1; j <= EyeSize; j++) {
        leds_L->setPixelColor(currentStep + j, red, green, blue); // Eye pixels
      }
      leds_L->setPixelColor(currentStep + EyeSize + 1, red / 10, green / 10, blue / 10); // Dim next pixel

      // Right strip animation (mirrored)
      leds_R->setPixelColor(currentStep, red / 10, green / 10, blue / 10); // Dim pixel
      for (int j = 1; j <= EyeSize; j++) {
        leds_R->setPixelColor(currentStep + j, red, green, blue); // Eye pixels
      }
      leds_R->setPixelColor(currentStep + EyeSize + 1, red / 10, green / 10, blue / 10); // Dim next pixel

      // Show updates on both strips
      leds_L->show();
      leds_R->show();

      currentStep++;
    } else {
      // End of animation, prepare for return delay
      animationRunning = false;
      returning = true;
      previousReturnMillis = currentMillis;
    }
  }

  // Return delay before restarting the animation
  if (returning && (currentMillis - previousReturnMillis >= ReturnDelay)) {
    currentStep = 0;  // Reset step
    animationRunning = true;  // Start a new animation
    returning = false;  // End the return phase
  }
}


/*________________________________________________ DISSOLVE RANDOM ______________________________________________________*/
unsigned long previousDissolveMillis = 0;
int numDissolve_L = 0;
int numDissolve_R = 0;
int *ledIndices_L = nullptr;  // Dynamic array for left LED indices
int *ledIndices_R = nullptr;  // Dynamic array for right LED indices

void dissolveRandom(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R) {
  int numPixels_L = leds_L->numPixels();
  int numPixels_R = leds_R->numPixels();
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Initialize the LED index arrays for both strips
  if (ledIndices_L == nullptr) {
    ledIndices_L = new int[numPixels_L];
    for (int i = 0; i < numPixels_L; i++) {
      ledIndices_L[i] = i;
    }
    numDissolve_L = numPixels_L;
  }
  if (ledIndices_R == nullptr) {
    ledIndices_R = new int[numPixels_R];
    for (int i = 0; i < numPixels_R; i++) {
      ledIndices_R[i] = i;
    }
    numDissolve_R = numPixels_R;
  }

  unsigned long currentMillis = millis();

  // Check if it's time to update the animation
  if ((numDissolve_L > 0 || numDissolve_R > 0) && (currentMillis - previousDissolveMillis >= Speed)) {
    previousDissolveMillis = currentMillis;

    // Handle random dissolve for the left strip
    if (numDissolve_L > 0) {
      int index_L = random(numDissolve_L);
      int ledIndex_L = ledIndices_L[index_L];

      // Remove the selected LED index from the array by shifting others
      for (int i = index_L; i < numDissolve_L - 1; i++) {
        ledIndices_L[i] = ledIndices_L[i + 1];
      }

      // Set the color of the selected LED to a random color
      leds_L->setPixelColor(ledIndex_L, leds_L->Color(random(200), random(200), random(200), random(255)));
      numDissolve_L--;
    }

    // Handle random dissolve for the right strip
    if (numDissolve_R > 0) {
      int index_R = random(numDissolve_R);
      int ledIndex_R = ledIndices_R[index_R];

      // Remove the selected LED index from the array by shifting others
      for (int i = index_R; i < numDissolve_R - 1; i++) {
        ledIndices_R[i] = ledIndices_R[i + 1];
      }

      // Set the color of the selected LED to a random color
      leds_R->setPixelColor(ledIndex_R, leds_R->Color(random(200), random(200), random(200), random(255)));
      numDissolve_R--;
    }

    // Show updates on both strips
    leds_L->show();
    leds_R->show();
  }

  // Clean up after the effect finishes
  if (numDissolve_L == 0 && numDissolve_R == 0) {
    // Turn off all LEDs
    for (int i = 0; i < numPixels_L; i++) {
      leds_L->setPixelColor(i, 0, 0, 0);  // Turn off the LED
    }
    for (int i = 0; i < numPixels_R; i++) {
      leds_R->setPixelColor(i, 0, 0, 0);  // Turn off the LED
    }
    leds_L->show();
    leds_R->show();

    // Free dynamically allocated memory
    delete[] ledIndices_L;
    delete[] ledIndices_R;
    ledIndices_L = nullptr;
    ledIndices_R = nullptr;
  }
}


/*____________________________________________________ SOLID COLOR FILL ___________________________________________________*/
void solid(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, uint32_t leftColor, uint32_t rightColor) {
  // Fill the left strip with the specified color
  int numPixels_L = leds_L->numPixels();
  for (int i = 0; i < numPixels_L; i++) {
    leds_L->setPixelColor(i, leftColor);
  }

  // Fill the right strip with the specified color
  int numPixels_R = leds_R->numPixels();
  for (int i = 0; i < numPixels_R; i++) {
    leds_R->setPixelColor(i, rightColor);
  }

  // Show updates on both strips
  leds_L->show();
  leds_R->show();
}



/*________________________________________________________ SCANNER ________________________________________________________*/

int currentPosition = 0;           // The current position of the moving scan
int direction = 1;                 // 1 for forward, -1 for reverse
int scanWidth = 6;                 // Number of LEDs to move at a time

void Scanner(Adafruit_NeoPixel* leds_L, Adafruit_NeoPixel* leds_R, Adafruit_NeoPixel* leds_3, uint32_t leftColor, uint32_t rightColor, uint32_t thirdColor) {

  int numPixelsLeft = leds_L->numPixels();
  int numPixelsRight = leds_R->numPixels();
  int numPixels3 = leds_3->numPixels();
  
  unsigned long currentMillis = millis();  // Get the current time
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= Speed) {
    previousMillis = currentMillis;  // Update the last update time

    // Clear strips
    leds_L->clear();
    leds_R->clear();
    leds_3->clear();

    // Update LEDs in the current direction
    for (int i = 0; i < scanWidth; i++) {
      if (currentPosition + i < numPixelsLeft) {
        leds_L->setPixelColor(currentPosition + i, leftColor);
      }
      if (currentPosition + i < numPixelsRight) {
        leds_R->setPixelColor(currentPosition + i, rightColor);
      }
      if (currentPosition + i < numPixels3) {
        leds_3->setPixelColor(currentPosition + i, thirdColor);
      }
    }

    // Show updated LEDs
    leds_L->show();
    leds_R->show();
    leds_3->show();

    // Move the position
    currentPosition += direction * scanWidth;

    // Reverse direction when hitting the end
    if (currentPosition >= max(max(numPixelsLeft, numPixelsRight), numPixels3) - scanWidth || currentPosition < 0) {
      direction *= -1;  // Change direction
    }
  }
}
/*___________________________________________________________ KNIGHT RIDER ______________________________________________*/
void knightRider(int numLEDsToLight) {
  unsigned long previousMillis = 0;  // stores the time when the animation was last updated
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  int numPixelsLeft = leds_L->numPixels();
  int numPixelsRight = leds_R->numPixels();
  int numPixelsExtra = leds_3->numPixels();

  int i = 0;  // index of the leftmost LED to light up

  while (i < numPixelsLeft + numLEDsToLight) {
    unsigned long currentMillis = millis();  // get the current time

    // Check if it's time to update the animation
    if (currentMillis - previousMillis >= Speed) {
      previousMillis = currentMillis;  // save the last update time

      for (int j = 0; j < numPixelsLeft; j++) {
        if (j >= i && j < i + numLEDsToLight) {
          leds_L->setPixelColor(j, leftColor);  // Set LED color (red)
          leds_R->setPixelColor(j, RightColor);
          leds_3->setPixelColor(j, thrdColor);

        } else {
          leds_L->setPixelColor(j, 0);  // Turn the LED off
          leds_R->setPixelColor(j, 0);
          leds_3->setPixelColor(j, 0);
        }

        if (j >= numPixelsLeft - i - numLEDsToLight && j < numPixelsLeft - i) {
          leds_L->setPixelColor(j, leftColor);  // Set LED color (red)
          leds_R->setPixelColor(j, RightColor);
          leds_3->setPixelColor(j, thrdColor);

        } else {
          leds_L->setPixelColor(numPixelsLeft - 1 - j, 0);  // Turn the LED off
          leds_R->setPixelColor(numPixelsRight - 1 - j, 0);
          leds_3->setPixelColor(numPixelsExtra - 1 - j, 0);
        }
      }

      leds_L->show();
      leds_R->show();
      leds_3->show();

      i++;  // move to the next LED

    }  // end if
  }    // end while
}



/*______________________________________________________________________ MIDDLE 3 OUT __________________________________________________*/
int step = 0;
bool animating = false;

void Middle3Out(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, uint32_t leftColor, uint32_t rightColor) {
  unsigned long currentMillis = millis();
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Initialize once
  static int numPixels_L, numPixels_R, middlePixel_L, middlePixel_R;
  if (!animating) {
    numPixels_L = leds_L->numPixels();
    numPixels_R = leds_R->numPixels();
    middlePixel_L = numPixels_L / 2;
    middlePixel_R = numPixels_R / 2;
    animating = true;
  }

  // Check if it's time to update the animation
  if (currentMillis - previousMillis >= Speed) {
    previousMillis = currentMillis;  // Update the previous time

    // Clear both LED strips
    leds_L->clear();
    leds_R->clear();

    // First half of the animation: from center to outside
    if (step <= middlePixel_L || step <= middlePixel_R) {
      // Left strip: Animate from middle outwards
      for (int i = 0; i < numPixels_L; i++) {
        if (i >= middlePixel_L - step && i <= middlePixel_L + step) {
          leds_L->setPixelColor(i, leftColor); // Apply left color
        }
      }

      // Right strip: Animate from middle outwards
      for (int i = 0; i < numPixels_R; i++) {
        if (i >= middlePixel_R - step && i <= middlePixel_R + step) {
          leds_R->setPixelColor(i, rightColor); // Apply right color
        }
      }

      leds_L->show();
      leds_R->show();
      step++;
    }
    // Second half of the animation: from outside back to center
    else if (step > middlePixel_L && step <= numPixels_L) {
      // Left strip: Animate from outside back to middle
      for (int i = 0; i < numPixels_L; i++) {
        if (i >= middlePixel_L - (numPixels_L - step) && i <= middlePixel_L + (numPixels_L - step)) {
          leds_L->setPixelColor(i, leftColor); // Apply left color
        }
      }

      // Right strip: Animate from outside back to middle
      for (int i = 0; i < numPixels_R; i++) {
        if (i >= middlePixel_R - (numPixels_R - step) && i <= middlePixel_R + (numPixels_R - step)) {
          leds_R->setPixelColor(i, rightColor); // Apply right color
        }
      }

      leds_L->show();
      leds_R->show();
      step++;
    }
    // Reset animation after finishing the cycle
    else {
      step = 0;
      animating = false;
    }
  }
}

/*__________________________________________________________________ MIDDLE 4 OUT STACKER___________________________________________________*/
int lastOffLED_L = 0, lastOffLED_R = 0;  // Track last off LED for both strips

void Middle4OutStacker(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, uint32_t Color) {
  unsigned long currentMillis = millis();
  int Speed = map(EffectSpeed, 1, 255, 5, 200);

  int numPixels_L = leds_L->numPixels();
  int numPixels_R = leds_R->numPixels();
  int middlePixel_L = numPixels_L / 2;  // Middle index for left strip
  int middlePixel_R = numPixels_R / 2;  // Middle index for right strip

  // Check if enough time has passed to update the animation
  if (currentMillis - previousMillis >= Speed) {
    previousMillis = currentMillis;  // Update the last update time

    // Left strip: Light up pixels from the middle outward and keep stacking them
    for (int i = 0; i <= lastOffLED_L; i++) {
      leds_L->setPixelColor(middlePixel_L - i, Color); // Left side outwards
      leds_L->setPixelColor(middlePixel_L + i, Color); // Right side outwards
    }

    // Show the changes on the left strip
    leds_L->show();

    // Update the stacker logic for the left strip: turn on the next LED outward
    if (lastOffLED_L < middlePixel_L) {
      lastOffLED_L++;  // Move outward
    }

    // Right strip: Light up pixels from the middle outward and keep stacking them
    for (int i = 0; i <= lastOffLED_R; i++) {
      leds_R->setPixelColor(middlePixel_R - i, Color); // Left side outwards
      leds_R->setPixelColor(middlePixel_R + i, Color); // Right side outwards
    }

    // Show the changes on the right strip
    leds_R->show();

    // Update the stacker logic for the right strip: turn on the next LED outward
    if (lastOffLED_R < middlePixel_R) {
      lastOffLED_R++;  // Move outward
    }

    // If both strips have fully stacked outward, reset for the next cycle
    if (lastOffLED_L >= middlePixel_L && lastOffLED_R >= middlePixel_R) {
      // Reset both strips' variables to start the animation over
      lastOffLED_L = 0;
      lastOffLED_R = 0;
    }
  }
}



/*__________________________________________________________________ MIDDLE 40 OUT STACKER___________________________________________________
unsigned long previousStackerMillis = 0;
int current_middle_pixel = 0;

void Middle4OutStacker(Adafruit_NeoPixel *strip, int wait_time, int stacker_wait_time, uint32_t LeftColor, uint32_t RightColor) {
  unsigned long currentMillis = millis();
  numPixels = strip->numPixels();
  middlePixel = numPixels / 2;

  if (current_middle_pixel == 0) {
    previousMillis = currentMillis;
    previousStackerMillis = currentMillis;
  }

  // Check if it's time to update the animation step
  if (currentMillis - previousMillis >= wait_time) {
    previousMillis = currentMillis;  // Update the previousMillis timestamp

    // Expand outward from the center
    for (int i = 0; i <= current_middle_pixel; i++) {
      for (int j = 0; j < numPixels; j++) {
        if (j >= middlePixel - i && j <= middlePixel + i) {
          strip->setPixelColor(j, LeftColor);  // Color for left side
        } else {
          strip->setPixelColor(j, 0, 0, 0);  // Turn off other LEDs
        }
      }

      strip->show();

      // After expanding, check for stacker delay
      if (currentMillis - previousStackerMillis >= stacker_wait_time) {
        previousStackerMillis = currentMillis;  // Update the stacker wait time
        current_middle_pixel++;
        if (current_middle_pixel > middlePixel) {
          current_middle_pixel = 0;
        }
      }
    }
  }

  // Check if we need to reverse the animation
  if (currentMillis - previousMillis >= wait_time && current_middle_pixel != 0) {
    // Collapse the stack back to the center
    for (int i = current_middle_pixel; i >= 0; i--) {
      for (int j = 0; j < numPixels; j++) {
        if (j >= middlePixel - i && j <= middlePixel + i) {
          strip->setPixelColor(j, LeftColor);  // Color for left side
        } else {
          strip->setPixelColor(j, 0, 0, 0);  // Turn off other LEDs
        }
      }

      strip->show();

      // Wait for stacker delay before reversing
      if (currentMillis - previousStackerMillis >= stacker_wait_time) {
        previousStackerMillis = currentMillis;  // Update the stacker wait time
        current_middle_pixel--;
        if (current_middle_pixel < 0) {
          current_middle_pixel = 0;
        }
      }
    }
  }
}*/


/*
int currentPixel = 0;

void Middle40OutStacker(Adafruit_NeoPixel *strip, int wait_time, int stacker_wait_time, uint32_t leftColor, uint32_t rightColor) {
  unsigned long currentMillis = millis();
  
  numPixels = strip->numPixels();
  middlePixel = numPixels / 2;

  // Initialize times at the start of the animation
  if (previousMillis == 0) {
    previousMillis = currentMillis;
    previousStackerMillis = currentMillis;
  }

  // Check if enough time has passed to update the animation
  if (currentMillis - previousMillis >= wait_time) {
    previousMillis = currentMillis;  // Update the last update time

    // Clear the LED strip
    strip->clear();

    // Light up pixels from the middle outward up to the currentPixel distance
    for (int i = 0; i <= currentPixel; i++) {
      // Light up pixels from the middle outward
      if (middlePixel - i >= 0) {
        strip->setPixelColor(middlePixel - i, leftColor); // Left side outwards
        strip->setPixelColor(middlePixel + i, leftColor); // Right side outwards
      }
    }

    // Show the changes on the strip
    strip->show();

    // Check if the middle pixel reached the limit
    if (currentPixel >= middlePixel) {
      // Fill the entire strip with color and wait before restarting
      strip->fill(leftColor);
      strip->show();

      // Wait before restarting the animation
      if (currentMillis - previousStackerMillis >= stacker_wait_time) {
        previousStackerMillis = currentMillis;  // Update stacker wait time
        currentPixel = 0; // Reset for a new animation cycle
      }
    } else {
      currentPixel++; // Move to the next pixel outward
    }
  }
}*/
/*void Middle4Out(int wait_time) {
  int numPixelsLeft = leds_L->numPixels();
  int numPixelsRight = leds_R->numPixels();
  int numPixels = max(numPixelsLeft, numPixelsRight);
  int middlePixel = numPixels / 2;
  int current_middle_pixel = 0;
  uint32_t last_update_time = 0;
  bool animation_done = false;

  while (!animation_done) {
    uint32_t current_time = millis();

    if ((current_time - last_update_time) >= wait_time) {
      last_update_time = current_time;

      float progress = (float)current_middle_pixel / (float)middlePixel;

      for (int i = 0; i <= current_middle_pixel; i++) {
        for (int j = 0; j < numPixelsLeft; j++) {
          if (j >= middlePixel - i && j <= middlePixel + i) {
            leds_L->setPixelColor(j, leftColor);
          } else {
            leds_L->setPixelColor(j, 0, 0, 0);
          }
        }
        for (int j = 0; j < numPixelsRight; j++) {
          if (j >= middlePixel - i && j <= middlePixel + i) {
            leds_R->setPixelColor(j, RightColor);
          } else {
            leds_R->setPixelColor(j, 0, 0, 0);
          }
        }
        leds_L->show();
        leds_R->show();
      }

      if (current_middle_pixel >= middlePixel) {
        for (int i = 0; i <= middlePixel; i++) {
          for (int j = 0; j < numPixelsLeft; j++) {
            if (j >= middlePixel - i && j <= middlePixel + i) {
              leds_L->setPixelColor(j, leftColor);
            } else {
              leds_L->setPixelColor(j, 0, 0, 0);
            }
          }
          for (int j = 0; j < numPixelsRight; j++) {
            if (j >= middlePixel - i && j <= middlePixel + i) {
              leds_R->setPixelColor(j, RightColor);
            } else {
              leds_R->setPixelColor(j, 0, 0, 0);
            }
          }
          leds_L->show();
          leds_R->show();
        }
        for (int i = middlePixel - 1; i >= 0; i--) {
          for (int j = 0; j < numPixelsLeft; j++) {
            if (j >= middlePixel - i && j <= middlePixel + i) {
              leds_L->setPixelColor(j, leftColor);
            } else {
              leds_L->setPixelColor(j, 0, 0, 0);
            }
          }
          for (int j = 0; j < numPixelsRight; j++) {
            if (j >= middlePixel - i && j <= middlePixel + i) {
              leds_R->setPixelColor(j, RightColor);
            } else {
              leds_R->setPixelColor(j, 0, 0, 0);
            }
          }
          leds_L->show();
          leds_R->show();
        }
        animation_done = true;
      }

      current_middle_pixel++;
    }
  }

  for (int i = 0; i < numPixelsLeft; i++) {
    leds_L->setPixelColor(i, 0, 0, 0);
  }
  for (int i = 0; i < numPixelsRight; i++) {
    leds_R->setPixelColor(i, 0, 0, 0);
  }
  leds_L->show();
  leds_R->show();
}/*/

/*_____________________________________________________________ BREATHE ANIMATION __________________________________________________*/
void breatheAnimation(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, Adafruit_NeoPixel *leds_3, uint32_t leftColor, uint32_t rightColor, uint32_t thrdColor) {
  static const int minBrightness = 10;   // Minimum brightness value
  static const int maxBrightness = 255;  // Maximum brightness value
    int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Store brightness and direction in arrays for easier management
  static int brightness[3] = {minBrightness, minBrightness, minBrightness};  // Array for brightness of LEDs
  static int direction[3] = {1, 1, 1};  // Array for direction of brightness changes (1 for increasing, -1 for decreasing)

  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= Speed) {
    // Update LED colors and brightness
    updateLEDColor(leds_L, leftColor, brightness[0]);
    updateLEDColor(leds_R, rightColor, brightness[1]);
    updateLEDColor(leds_3, thrdColor, brightness[2]);

    // Change brightness and direction for all strips
    for (int i = 0; i < 3; i++) {
      brightness[i] += direction[i];
      if (brightness[i] >= maxBrightness || brightness[i] <= minBrightness) {
        direction[i] *= -1;  // Reverse direction when min/max is reached
      }
    }

    // Show the updated colors and brightness
    leds_L->show();
    leds_R->show();
    leds_3->show();

    // Update time
    previousMillis = currentMillis;
  }
}

void breatheAnimationRandom(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, Adafruit_NeoPixel *leds_3, uint32_t leftColor, uint32_t rightColor, uint32_t thrdColor) {

  static const int minBrightness = 10;   // Minimum brightness value
  static const int maxBrightness = 255;  // Maximum brightness value
      int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Store brightness, direction, and current colors in arrays for easier management
  static int brightness[3] = {minBrightness, minBrightness, minBrightness};  // Array for brightness of LEDs
  static int direction[3] = {1, 1, 1};  // Array for direction of brightness changes (1 for increasing, -1 for decreasing)
  static uint32_t currentColors[3] = {leftColor, rightColor, thrdColor}; // Array to store current colors

  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= Speed) {
    // Update LED colors and brightness
    updateLEDColor(leds_L, currentColors[0], brightness[0]);
    updateLEDColor(leds_R, currentColors[1], brightness[1]);
    updateLEDColor(leds_3, currentColors[2], brightness[2]);

    // Change brightness and direction for all strips
    for (int i = 0; i < 3; i++) {
      brightness[i] += direction[i];
      if (brightness[i] >= maxBrightness || brightness[i] <= minBrightness) {
        direction[i] *= -1;  // Reverse direction when min/max is reached

        // When brightness is at minimum, choose a new random color
        if (brightness[i] <= minBrightness) {
          currentColors[i] = random();  // Generate a new random color
        }
      }
    }

    // Show the updated colors and brightness
    leds_L->show();
    leds_R->show();
    leds_3->show();

    // Update time
    previousMillis = currentMillis;
  }
}

// Helper function to update the LED color with brightness
void updateLEDColor(Adafruit_NeoPixel *leds, uint32_t color, int brightness) {
  uint8_t r = (color >> 16) & 0xFF;  // Red component
  uint8_t g = (color >> 8) & 0xFF;   // Green component
  uint8_t b = color & 0xFF;          // Blue component
  
  // Fill all LEDs with the color and apply brightness
  leds->fill(leds->Color(r, g, b));
  leds->setBrightness(brightness);
}




/*__________________________________________________________________ COLOR BOUNCE RAIN ___________________________________________________*/
int currentDelay = 0;              // Store the delay between LED moves
int position_L = 0, position_R = 0;  // Current LED positions for left and right strips
uint32_t color = random(0xFFFFFF); // Random initial color
int direction_L = 1, direction_R = 1; // Direction for both strips (1 for right, -1 for left)

void colorBounceRain(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, int numLEDsLit) {
  unsigned long currentMillis = millis();  // Get the current time
      int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Check if enough time has passed to update the LED positions
  if (currentMillis - previousMillis >= Speed) {
    previousMillis = currentMillis;  // Update last update time

    // Clear all LEDs
    leds_L->clear();
    leds_R->clear();

    // Set the color for the lit LEDs on the left strip
    for (int i = position_L; i < position_L + numLEDsLit; i++) {
      if (i >= 0 && i < leds_L->numPixels()) {  // Ensure we're within bounds
        leds_L->setPixelColor(i, color);
      }
    }

    // Set the color for the lit LEDs on the right strip
    for (int i = position_R; i < position_R + numLEDsLit; i++) {
      if (i >= 0 && i < leds_R->numPixels()) {  // Ensure we're within bounds
        leds_R->setPixelColor(i, color);
      }
    }

    // Show the updates for both strips
    leds_L->show();
    leds_R->show();

    // Move the positions for both strips
    position_L += direction_L;
    position_R += direction_R;

    // Reverse direction when hitting the end for both strips
    if (position_L >= (leds_L->numPixels() - numLEDsLit) || position_L <= 0) {
      direction_L *= -1;  // Reverse the direction for the left strip
      color = random(0xFFFFFF);  // Random 24-bit color
    }

    if (position_R >= (leds_R->numPixels() - numLEDsLit) || position_R <= 0) {
      direction_R *= -1;  // Reverse the direction for the right strip
      color = random(0xFFFFFF);  // Random 24-bit color
    }
  }
}

/*__________________________________________________________________ COLOR BOUNCE _____________________________________________________________*/

void colorBounce(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, uint32_t color,int numLEDsLit) {
  unsigned long currentMillis = millis();  // Get the current time
      int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= Speed) {
    previousMillis = currentMillis;  // Update the last update time

    // Clear all LEDs
    leds_L->clear();
    leds_R->clear();

    // Set the color for the lit LEDs on the left strip
    for (int i = position_L; i < position_L + numLEDsLit; i++) {
      if (i >= 0 && i < leds_L->numPixels()) {  // Ensure we're within bounds
        leds_L->setPixelColor(i, color);
      }
    }

    // Set the color for the lit LEDs on the right strip
    for (int i = position_R; i < position_R + numLEDsLit; i++) {
      if (i >= 0 && i < leds_R->numPixels()) {  // Ensure we're within bounds
        leds_R->setPixelColor(i, color);
      }
    }

    // Show the updates for both strips
    leds_L->show();
    leds_R->show();

    // Move the positions for both strips
    position_L += direction_L;
    position_R += direction_R;

    // Reverse direction when hitting the end for both strips
    if (position_L == (leds_L->numPixels() - numLEDsLit) || position_L == 0) {
      direction_L *= -1;  // Reverse the direction for the left strip
    }

    if (position_R == (leds_R->numPixels() - numLEDsLit) || position_R == 0) {
      direction_R *= -1;  // Reverse the direction for the right strip
    }
  }
}


/*__________________________________________________________ TETRIS ANIMATION ________________________________________________________________*/
void tetrisAnimation(Adafruit_NeoPixel *strip, int SPEED_MS, uint32_t leftColor, uint32_t rightColor) {
  static int ledPosition = 0;                        // LED position tracker
  static bool isColor1Active = true;                 // Flag to toggle between colors

  // Shift all LEDs one position to the right (creates the stacking effect)
  for (int i = NUM_LEDS_L - 1; i > 0; i--) {
    strip->setPixelColor(i, strip->getPixelColor(i - 1));
  }

  // Set the color for the current LED position
  uint32_t currentColor = isColor1Active ? leftColor : rightColor;
  strip->setPixelColor(0, currentColor);  // Set the first LED (bottom LED)

  // Show the updated LED state
  strip->show();

  // Delay to control the animation speed
  delay(SPEED_MS);

  // Move to the next LED
  ledPosition++;

  // Check if all LEDs have been lit
  if (ledPosition >= NUM_LEDS_L) {
    isColor1Active = !isColor1Active; // Toggle between colors
    ledPosition = 0; // Reset to the first LED
  }
}




/*___________________________________________________________STARTUP ANIMATION _______________________________________________________________*/
void Startupanimation(Adafruit_NeoPixel *strip, int SPEED_MS, uint32_t leftColorFull) {
  static int currentLed = 0;    // Keeps track of the currently lit LED
  static int fullyLitLeds = 0;  // Number of fully lit LEDs in each pass
  static unsigned long previousMillis = 0;
  static bool lightVersion = true;  // Flag to control which version of the animation is active
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= SPEED_MS) {
    previousMillis = currentMillis;

    // Clear all LEDs
    for (int i = 0; i < NUM_LEDS_L; i++) {
      strip->setPixelColor(i, strip->Color(0, 0, 0));
    }

    // Extract the red, green, and blue components of the leftColorFull
    uint8_t red = (leftColorFull >> 16) & 0xFF;
    uint8_t green = (leftColorFull >> 8) & 0xFF;
    uint8_t blue = leftColorFull & 0xFF;

    red = red / 2;
    green = green / 2;
    blue = blue / 2;

    // Combine the components to create the new color
    uint32_t leftColorLight = strip->Color(red, green, blue);

    // Check if all LEDs are fully lit in the "light" version
    if (fullyLitLeds >= NUM_LEDS_L) {
      lightVersion = false;  // Switch to the "full" version
    }

    // Turn on the LED at the currentLed position with the currentColor
    strip->setPixelColor(currentLed, lightVersion ? leftColorLight : leftColorFull);

    // Turn on additional fully lit LEDs starting from the last LED with the currentColor
    for (int i = NUM_LEDS_L - 1; i >= NUM_LEDS_L - fullyLitLeds; i--) {
      strip->setPixelColor(i, lightVersion ? leftColorLight : leftColorFull);
    }

    strip->show();  // Update the LED strip

    // Move to the next LED upward
    currentLed++;

    // If we've reached the top of the strip, reset to the bottom and increment fully lit LEDs
    if (currentLed >= NUM_LEDS_L) {
      currentLed = 0;
      fullyLitLeds++;

      // If all LEDs are fully lit in the "light" version, switch to the "full" version
      if (fullyLitLeds >= NUM_LEDS_L) {
        lightVersion = false;
      }
    }
  }
}

/*static int currentLed = 0;   // Keeps track of the currently lit LED
  static int fullyLitLeds = 0; // Number of fully lit LEDs in each pass
  static unsigned long previousMillis = 0;
  static bool lightVersion = true; // Flag to control which version of the animation is active
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= SPEED_MS) {
    previousMillis = currentMillis;

    // Clear all LEDs
    for (int i = 0; i < NUM_LEDS_L; i++) {
      strip->setPixelColor(i, strip->Color(0, 0, 0));
    }

    // Set the color based on the flag (lightVersion)
    uint32_t currentColor = lightVersion ? leftColorLight : leftColorFull;

    // Turn on the LED at the currentLed position with the currentColor
    strip->setPixelColor(currentLed, currentColor);

    // Turn on additional fully lit LEDs starting from the last LED with the currentColor
    for (int i = NUM_LEDS_L - 1; i >= NUM_LEDS_L - fullyLitLeds; i--) {
      strip->setPixelColor(i, currentColor);
    }

    strip->show(); // Update the LED strip

    // Move to the next LED upward
    currentLed++;

    // If we've reached the top of the strip, reset to the bottom and increment fully lit LEDs
    if (currentLed >= NUM_LEDS_L) {
      currentLed = 0;
      fullyLitLeds++;

      // If all LEDs are fully lit, reset fullyLitLeds to 0 and switch to the full version
      if (fullyLitLeds >= NUM_LEDS_L) {
        fullyLitLeds = 0;
        lightVersion = !lightVersion; // Toggle between light and full versions
      }
    }
  }
}
*/

/*void Startup(Adafruit_NeoPixel* strip, int speed){
 for (int i = 0; i < NUM_LEDS_L; i++) {
    for (int j = 0; j <= i; j++) {
      strip->setPixelColor(j, strip->Color(DRLColor)); // set the color of the LED
      strip->show(); // turn on the LED
    }
    delay(speed); // wait for a short amount of time
    if (i == NUM_LEDS_L - 1) {
      while (true) {
        for (int k = 0; k < NUM_LEDS_L; k++) {
          strip->setPixelColor(k, strip->Color(DRLColor)); // set the color of the LED
        }
        strip->show(); // turn on all LEDs
        delay(speed); // wait for a short amount of time
      }
    }
    for (int j = 0; j <= i; j++) {
      strip->setPixelColor(j, strip->Color(0, 0, 0)); // turn off the LED
      strip->show(); // update the strip
    }
  }
}*/
//use for sequential fade
/*void Fade(Adafruit_NeoPixel* strip, int speed) {
  for (int i = 0; i < NUM_LEDS_L; i++) {
    strip->setPixelColor(i, strip->Color(255, 255, 255)); // set the color of the LED
    strip->show(); // turn on the LED
    delay(speed); // wait for a short amount of time
    strip->setPixelColor(i, strip->Color(0, 0, 0)); // turn off the LED
    strip->show(); // update the strip
  }
}*/




/*_______________________________________________________________ SWIPE RANDOM ANIMATIONS _____________________________________________________*/
int currentIndex_L = 0, currentIndex_R = 0;
bool isTurningOff_L = false, isTurningOff_R = false;

void SwipeRandomAnimation(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R) {
    int Speed = map(EffectSpeed, 1, 255, 5, 200);

  unsigned long currentMillis = millis();
  int numLeds_L = leds_L->numPixels();
  int numLeds_R = leds_R->numPixels();

  // Generate a new random color only at the start of each full swipe
  if (currentIndex_L == 0 && !isTurningOff_L) {
    randomColor = random(0, 0xFFFFFF + 1);
  }

  // Check if it's time to move to the next step
  if (currentMillis - previousMillis >= Speed) {
    previousMillis = currentMillis;

    // Clear both strips if the animation is restarting
    if (currentIndex_L == 0 && currentIndex_R == 0) {
      leds_L->clear();
      leds_R->clear();
    }

    // For the left strip
    if (!isTurningOff_L) {
      // Light up LEDs in a sweeping pattern for the left strip
      leds_L->setPixelColor(numLeds_L - 1 - currentIndex_L, randomColor);
      leds_L->setPixelColor(currentIndex_L, randomColor);
      currentIndex_L++;

      // Check if the end of the left strip has been reached
      if (currentIndex_L >= numLeds_L / 2) {
        currentIndex_L = 0;  // Reset the index for left strip
        isTurningOff_L = true;  // Switch to turning off LEDs for left strip
      }
    } else {
      // Turn off LEDs sequentially in reverse pattern for the left strip
      leds_L->setPixelColor(currentIndex_L, 0);
      leds_L->setPixelColor(numLeds_L - 1 - currentIndex_L, 0);
      currentIndex_L++;

      // Check if the left strip is fully turned off
      if (currentIndex_L >= numLeds_L / 2) {
        currentIndex_L = 0;  // Reset the index for left strip
        isTurningOff_L = false;  // Prepare for the next swipe with a new color for left strip
      }
    }

    // For the right strip
    if (!isTurningOff_R) {
      // Light up LEDs in a sweeping pattern for the right strip
      leds_R->setPixelColor(numLeds_R - 1 - currentIndex_R, randomColor);
      leds_R->setPixelColor(currentIndex_R, randomColor);
      currentIndex_R++;

      // Check if the end of the right strip has been reached
      if (currentIndex_R >= numLeds_R / 2) {
        currentIndex_R = 0;  // Reset the index for right strip
        isTurningOff_R = true;  // Switch to turning off LEDs for right strip
      }
    } else {
      // Turn off LEDs sequentially in reverse pattern for the right strip
      leds_R->setPixelColor(currentIndex_R, 0);
      leds_R->setPixelColor(numLeds_R - 1 - currentIndex_R, 0);
      currentIndex_R++;

      // Check if the right strip is fully turned off
      if (currentIndex_R >= numLeds_R / 2) {
        currentIndex_R = 0;  // Reset the index for right strip
        isTurningOff_R = false;  // Prepare for the next swipe with a new color for right strip
      }
    }

    // Show the updates on both strips
    leds_L->show();
    leds_R->show();
  }
}

/*_________________________________________________________ STACKING ANIMATION _________________________________________________________________*/

int numLitLEDs = 0;                // Number of LEDs that should stay lit

void stackingAnimationStarting(Adafruit_NeoPixel *strip) {
  int numPixels = strip->numPixels();  // Get the number of LEDs in the strip
  
  unsigned long currentMillis = millis();  // Get the current time
    int Speed = map(EffectSpeed, 1, 255, 5, 200);

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= Speed) {
    previousMillis = currentMillis;  // Update the last update time

    // Clear the strip and keep the LEDs that should stay lit
    for (int i = 0; i < numPixels; i++) {
      if (i <= numLitLEDs) {
        strip->setPixelColor(i, strip->Color(255, 255, 255));  // Keep previous LEDs lit (white color)
      } else {
        strip->setPixelColor(i, 0);  // Turn off the rest of the LEDs
      }
    }

    // Turn on the current moving LED
    if (currentPosition < numPixels) {
      strip->setPixelColor(currentPosition, strip->Color(255, 255, 255));  // White color for the moving LED
    }

    // Show the updated strip
    strip->show();

    // Update the position for the next LED (move down one step)
    currentPosition++;

    // If the current position exceeds the number of LEDs, reset the animation
    if (currentPosition >= numPixels) {
      currentPosition = 0;    // Reset to the top of the strip
      numLitLEDs++;           // Increase the number of LEDs that should stay lit
      if (numLitLEDs >= numPixels) {
        numLitLEDs = numPixels - 1;  // Stop lighting more LEDs once the entire strip is lit
      }
    }
  }
}
void stackingAnimationReverseddelay( int EffectSpeed, bool reverse_L, bool reverse_R) {
  static int currentPosition_L = 0;        // Separate position trackers for left and right
  static int currentPosition_R = 0;
  static int numLitLEDs_L = 0;
  static int numLitLEDs_R = 0;

  // Left Strip Animation
  int numPixels_L = leds_L->numPixels();
  for (int i = 0; i < numPixels_L; i++) {
    if (i <= numLitLEDs_L) {
      leds_L->setPixelColor(i, leds_L->Color(255, 255, 255));  // Keep previous LEDs lit (white color)
    } else {
      leds_L->setPixelColor(i, 0);  // Turn off the rest of the LEDs
    }
  }
  int actualPosition_L = reverse_L ? numPixels_L - 1 - currentPosition_L : currentPosition_L;
  if (actualPosition_L < numPixels_L) {
    leds_L->setPixelColor(actualPosition_L, leds_L->Color(255, 255, 255));  // Moving LED
  }
  leds_L->show();

  currentPosition_L++;
  if (currentPosition_L >= numPixels_L) {
    // Reset to start without lit LEDs once max LEDs are lit
    currentPosition_L = 0;
    if (numLitLEDs_L < numPixels_L - 1) {
      numLitLEDs_L++;  // Increase the number of LEDs that should stay lit
    } else {
      numLitLEDs_L = 0;  // Restart with no LEDs lit
    }
  }

  // Delay to control the animation speed
  delay(EffectSpeed);

  // Right Strip Animation
  int numPixels_R = leds_R->numPixels();
  for (int i = 0; i < numPixels_R; i++) {
    if (i <= numLitLEDs_R) {
      leds_R->setPixelColor(i, leds_R->Color(255, 255, 255));  // Keep previous LEDs lit (white color)
    } else {
      leds_R->setPixelColor(i, 0);  // Turn off the rest of the LEDs
    }
  }
  int actualPosition_R = reverse_R ? numPixels_R - 1 - currentPosition_R : currentPosition_R;
  if (actualPosition_R < numPixels_R) {
    leds_R->setPixelColor(actualPosition_R, leds_R->Color(255, 255, 255));  // Moving LED
  }
  leds_R->show();

  currentPosition_R++;
  if (currentPosition_R >= numPixels_R) {
    // Reset to start without lit LEDs once max LEDs are lit
    currentPosition_R = 0;
    if (numLitLEDs_R < numPixels_R - 1) {
      numLitLEDs_R++;  // Increase the number of LEDs that should stay lit
    } else {
      numLitLEDs_R = 0;  // Restart with no LEDs lit
    }
  }

  // Delay to control the animation speed
  delay(EffectSpeed);
}


void stackingAnimationReversed(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, int EffectSpeed, bool reverse_L, bool reverse_R) {
  static unsigned long previousMillis = 0;  // Static to persist across calls
  static int currentPosition_L = 0;        // Separate position trackers for left and right
  static int currentPosition_R = 0;
  static int numLitLEDs_L = 0;
  static int numLitLEDs_R = 0;

  unsigned long currentMillis = millis();  // Get the current time

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= EffectSpeed) {
    previousMillis = currentMillis;  // Update the last update time

    // Left Strip Animation
    int numPixels_L = leds_L->numPixels();
    for (int i = 0; i < numPixels_L; i++) {
      if (i <= numLitLEDs_L) {
        leds_L->setPixelColor(i, leds_L->Color(255, 255, 255));  // Keep previous LEDs lit (white color)
      } else {
        leds_L->setPixelColor(i, 0);  // Turn off the rest of the LEDs
      }
    }
    int actualPosition_L = reverse_L ? numPixels_L - 1 - currentPosition_L : currentPosition_L;
    if (actualPosition_L < numPixels_L) {
      leds_L->setPixelColor(actualPosition_L, leds_L->Color(255, 255, 255));  // Moving LED
    }
    leds_L->show();

    currentPosition_L++;
    if (currentPosition_L >= numPixels_L) {
      // Reset to start without lit LEDs once max LEDs are lit
      currentPosition_L = 0;
      if (numLitLEDs_L < numPixels_L - 1) {
        numLitLEDs_L++;  // Increase the number of LEDs that should stay lit
      } else {
        numLitLEDs_L = 0;  // Restart with no LEDs lit
      }
    }

    // Right Strip Animation
    int numPixels_R = leds_R->numPixels();
    for (int i = 0; i < numPixels_R; i++) {
      if (i <= numLitLEDs_R) {
        leds_R->setPixelColor(i, leds_R->Color(255, 255, 255));  // Keep previous LEDs lit (white color)
      } else {
        leds_R->setPixelColor(i, 0);  // Turn off the rest of the LEDs
      }
    }
    int actualPosition_R = reverse_R ? numPixels_R - 1 - currentPosition_R : currentPosition_R;
    if (actualPosition_R < numPixels_R) {
      leds_R->setPixelColor(actualPosition_R, leds_R->Color(255, 255, 255));  // Moving LED
    }
    leds_R->show();

    currentPosition_R++;
    if (currentPosition_R >= numPixels_R) {
      // Reset to start without lit LEDs once max LEDs are lit
      currentPosition_R = 0;
      if (numLitLEDs_R < numPixels_R - 1) {
        numLitLEDs_R++;  // Increase the number of LEDs that should stay lit
      } else {
        numLitLEDs_R = 0;  // Restart with no LEDs lit
      }
    }
  }
}



void stackingToZeroAllLitAnimation(Adafruit_NeoPixel *strip, int EffectSpeed) {
  static unsigned long previousMillis = 0;  // Keep track of the last update time
  static int currentPosition = strip->numPixels() - 1;  // Start from the last LED
  static int numLitLEDs = 0;                            // Number of LEDs permanently lit at position 0
  static uint32_t currentColor = 0xFFFFFF;              // Initial color (white)

  int numPixels = strip->numPixels();                   // Total number of LEDs in the strip
  unsigned long currentMillis = millis();               // Get the current time

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= EffectSpeed) {
    previousMillis = currentMillis;  // Update the last update time

    // Clear the strip, but preserve permanently lit LEDs at position 0
    for (int i = 0; i < numLitLEDs; i++) {
      strip->setPixelColor(i, currentColor);  // Keep permanently lit LEDs at position 0
    }

    // Set the animation for the remaining LEDs
    for (int i = numLitLEDs; i < numPixels; i++) {
      int offset = (i - currentPosition + numPixels) % numPixels;  // Circular offset calculation
      uint32_t color = strip->Color(
        (currentColor >> 16) * offset / numPixels,  // Dimmed red
        (currentColor >> 8 & 0xFF) * offset / numPixels,  // Dimmed green
        (currentColor & 0xFF) * offset / numPixels   // Dimmed blue
      );
      strip->setPixelColor(i, color);  // All animated LEDs lit
    }

    // Show the updated strip
    strip->show();

    // Move the current LED closer to position 0
    currentPosition--;

    // If the current LED reaches position 0, stack it permanently
    if (currentPosition < numLitLEDs) {
      currentPosition = numPixels - 1;                  // Reset to the last LED
      numLitLEDs++;                                     // Increment the stack
      currentColor = strip->Color(random(0, 256), random(0, 256), random(0, 256));  // Generate new random color

      // Stop the animation if all LEDs are permanently stacked
      if (numLitLEDs >= numPixels) {
        numLitLEDs = numPixels;  // Prevent exceeding the total number of LEDs
        return;  // End the function to stop further updates
      }
    }
  }
}

void stackingAnimationSolidRandomColor(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, int EffectSpeed, bool reverse_L, bool reverse_R) {
  static unsigned long previousMillis = 0;      // Keep track of the last update time
  static int currentPosition_L = 0;               // Current position of the moving LED for the left strip
  static int currentPosition_R = 0;               // Current position of the moving LED for the right strip
  static int numLitLEDs_L = 0;                    // Number of LEDs that should stay lit for the left strip
  static int numLitLEDs_R = 0;                    // Number of LEDs that should stay lit for the right strip
  static uint32_t currentColor_L = 0xFFFFFF;      // Initial color for the left strip (white)
  static uint32_t currentColor_R = 0xFFFFFF;      // Initial color for the right strip (white)

  int numPixels_L = leds_L->numPixels();           // Get the number of LEDs in the left strip
  int numPixels_R = leds_R->numPixels();           // Get the number of LEDs in the right strip
  unsigned long currentMillis = millis();          // Get the current time

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= EffectSpeed) {
    previousMillis = currentMillis;  // Update the last update time

    // Left Strip Animation
    for (int i = 0; i < numPixels_L; i++) {
      if (i < numLitLEDs_L) {  // Keep the stacked LEDs lit
        leds_L->setPixelColor(i, currentColor_L);  // Set color for lit LEDs
      } else {
        leds_L->setPixelColor(i, 0);  // Turn off LEDs that are not lit
      }
    }

    // Calculate the actual position for the moving LED based on direction
    int actualPosition_L = reverse_L ? numPixels_L - 1 - currentPosition_L : currentPosition_L;
    if (actualPosition_L < numPixels_L) {
      leds_L->setPixelColor(actualPosition_L, currentColor_L);  // Set moving LED color
    }
    leds_L->show();

    currentPosition_L++;
    if (currentPosition_L >= numPixels_L) {
      currentPosition_L = 0;  // Reset the position to the start
      if (numLitLEDs_L < numPixels_L) {
        numLitLEDs_L++;            // Add one more LED to the "stack"
      } else {
        numLitLEDs_L = 0;          // Reset to no LEDs lit when the entire strip is filled
      }
      // Assign a new random color for the moving LEDs on the left strip
      currentColor_L = leds_L->Color(random(0, 256), random(0, 256), random(0, 256));
    }

    // Right Strip Animation
    for (int i = 0; i < numPixels_R; i++) {
      if (i < numLitLEDs_R) {  // Keep the stacked LEDs lit
        leds_R->setPixelColor(i, currentColor_R);  // Set color for lit LEDs
      } else {
        leds_R->setPixelColor(i, 0);  // Turn off LEDs that are not lit
      }
    }

    // Calculate the actual position for the moving LED based on direction
    int actualPosition_R = reverse_R ? numPixels_R - 1 - currentPosition_R : currentPosition_R;
    if (actualPosition_R < numPixels_R) {
      leds_R->setPixelColor(actualPosition_R, currentColor_R);  // Set moving LED color
    }
    leds_R->show();

    currentPosition_R++;
    if (currentPosition_R >= numPixels_R) {
      currentPosition_R = 0;  // Reset the position to the start
      if (numLitLEDs_R < numPixels_R) {
        numLitLEDs_R++;            // Add one more LED to the "stack"
      } else {
        numLitLEDs_R = 0;          // Reset to no LEDs lit when the entire strip is filled
      }
      // Assign a new random color for the moving LEDs on the right strip
      currentColor_R = leds_R->Color(random(0, 256), random(0, 256), random(0, 256));
    }
  }
}


void RandomFlowBothEnds(Adafruit_NeoPixel *strip, int EffectSpeed, bool reverse) {
  static unsigned long previousMillis = 0;  // Keep track of the last update time
  static int currentPosition = 0;           // Current position of the moving LED
  static uint32_t currentColor = 0xFFFFFF;  // Initial color (white)
  static int numPixels = strip->numPixels(); // Get the number of LEDs in the strip

  unsigned long currentMillis = millis();  // Get the current time

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= EffectSpeed) {
    previousMillis = currentMillis;  // Update the last update time

    // Clear the strip (reset all LEDs)
    for (int i = 0; i < numPixels; i++) {
      strip->setPixelColor(i, 0);  // Turn off all LEDs
    }

    // Move LEDs continuously (without resetting)
    for (int i = 0; i < numPixels; i++) {
      // Set each LED to the current color if it is within the moving window
      if (i == currentPosition) {
        strip->setPixelColor(i, currentColor);  // Set current LED to be lit
      } else if (reverse) {
        // When moving in reverse, create a moving effect from end to start
        if (i == (numPixels - 1 - currentPosition)) {
          strip->setPixelColor(i, currentColor);
        }
      } else {
        // Normal forward movement
        if (i == currentPosition) {
          strip->setPixelColor(i, currentColor);
        }
      }
    }

    // Show the updated strip
    strip->show();

    // Update the position for the next LED
    if (!reverse) {
      currentPosition++;  // Move to the next position
    } else {
      currentPosition--;  // Move to the previous position (reverse direction)
    }

    // If the position exceeds the number of LEDs, reset it to the opposite side
    if (currentPosition >= numPixels) {
      currentPosition = 0;  // Start again from the first LED
    } else if (currentPosition < 0) {
      currentPosition = numPixels - 1;  // Start from the last LED when moving in reverse
    }

    // If all LEDs have been lit up, pick a new random color
    if (currentPosition == 0) {
      currentColor = strip->Color(random(0, 256), random(0, 256), random(0, 256));  // Generate a new random color
    }
  }
}

void stackingAnimationRandomColor(Adafruit_NeoPixel *strip, int EffectSpeed, bool reverse) {
  static unsigned long previousMillis = 0;  // Keep track of the last update time
  static int currentPosition = 0;           // Current position of the moving LED
  static int numLitLEDs = 0;                // Number of LEDs that should stay lit
  static uint32_t currentColor = 0xFFFFFF;  // Initial color (white)

  int numPixels = strip->numPixels();       // Get the number of LEDs in the strip
  unsigned long currentMillis = millis();  // Get the current time

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= EffectSpeed) {
    previousMillis = currentMillis;  // Update the last update time

    // Clear the strip
    for (int i = 0; i < numPixels; i++) {
      strip->setPixelColor(i, 0);  // Turn off all LEDs
    }

    // Calculate the current position based on the direction
    int actualPosition = reverse ? numPixels - 1 - currentPosition : currentPosition;

    // Light up all LEDs, but only the currentPosition LED stays lit
    for (int i = 0; i < numPixels; i++) {
      if (i == actualPosition) {
        strip->setPixelColor(i, currentColor);  // Current moving LED stays lit
      } else {
        // Light up the LEDs before and after in sequence (not permanent, temporary lighting)
        strip->setPixelColor(i, currentColor);  // Temporarily light the other LEDs
      }
    }

    // Show the updated strip
    strip->show();

    // Update the position for the next LED
    currentPosition++;

    // If the current position exceeds the number of LEDs, reset the animation
    if (currentPosition >= numPixels) {
      currentPosition = 0;    // Reset to the starting position
      numLitLEDs++;           // Increase the number of LEDs that should stay lit
      
      // If all LEDs are lit, restart and pick a new random color
      if (numLitLEDs >= numPixels) {
        numLitLEDs = 0;  // Reset the number of lit LEDs
        currentColor = strip->Color(random(0, 256), random(0, 256), random(0, 256));  // Generate a random color
      }
    }
  }
}

void stackingAnimationSingleRandomColor(Adafruit_NeoPixel *strip, int EffectSpeed, bool reverse) {

  static unsigned long previousMillis = 0;  // Keep track of the last update time
  static int currentPosition = 0;           // Current position of the moving LED
  static int numLitLEDs = 0;                // Number of LEDs that should stay lit
  static uint32_t currentColor = 0xFFFFFF;  // Initial color (white)

  int numPixels = strip->numPixels();       // Get the number of LEDs in the strip
  unsigned long currentMillis = millis();  // Get the current time

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= EffectSpeed) {
    previousMillis = currentMillis;  // Update the last update time

    // Clear the strip
    for (int i = 0; i < numPixels; i++) {
      strip->setPixelColor(i, 0);  // Turn off all LEDs
    }

    // Calculate the current position based on the direction
    int actualPosition = reverse ? numPixels - 1 - currentPosition : currentPosition;

    // Turn on the LEDs up to numLitLEDs and the moving LED
    for (int i = 0; i <= numLitLEDs; i++) {
      strip->setPixelColor(i, currentColor);  // Use the current stack color
    }
    if (actualPosition < numPixels) {
      strip->setPixelColor(actualPosition, currentColor);  // Moving LED with the same color
    }

    // Show the updated strip
    strip->show();

    // Update the position for the next LED
    currentPosition++;

    // If the current position exceeds the number of LEDs, reset the animation
    if (currentPosition >= numPixels) {
      currentPosition = 0;    // Reset to the starting position
      numLitLEDs++;           // Increase the number of LEDs that should stay lit
      
      // If all LEDs are lit, restart and pick a new random color
      if (numLitLEDs >= numPixels) {
        numLitLEDs = 0;  // Reset the number of lit LEDs
        currentColor = strip->Color(random(0, 256), random(0, 256), random(0, 256));  // Generate a random color
      }
    }
  }
}



bool isLeftColorActive = true;  // Boolean flag to track which color is active
bool isAnimationComplete = false; // Flag to track if the second color has completed

void stackingAnimationDUO(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, int SPEED_MS, uint32_t leftColor, uint32_t rightColor) {
  int numPixels_L = leds_L->numPixels();  // Get the number of LEDs in the left strip
  int numPixels_R = leds_R->numPixels();  // Get the number of LEDs in the right strip
  
  unsigned long currentMillis = millis();  // Get the current time

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= SPEED_MS) {
    previousMillis = currentMillis;  // Update the last update time

    // Clear the strips and keep the LEDs that should stay lit
    for (int i = 0; i < numPixels_L; i++) {
      if (i <= numLitLEDs) {
        if (isLeftColorActive) {
          leds_L->setPixelColor(i, leftColor);  // Keep previous LEDs lit with leftColor
        } else {
          leds_L->setPixelColor(i, rightColor);  // Keep previous LEDs lit with rightColor
        }
      } else {
        leds_L->setPixelColor(i, 0);  // Turn off the rest of the LEDs on the left strip
      }
    }

    for (int i = 0; i < numPixels_R; i++) {
      if (i <= numLitLEDs) {
        if (isLeftColorActive) {
          leds_R->setPixelColor(i, leftColor);  // Keep previous LEDs lit with leftColor
        } else {
          leds_R->setPixelColor(i, rightColor);  // Keep previous LEDs lit with rightColor
        }
      } else {
        leds_R->setPixelColor(i, 0);  // Turn off the rest of the LEDs on the right strip
      }
    }

    // Turn on the current moving LED with the active color on both strips
    if (currentPosition < numPixels_L) {
      if (isLeftColorActive) {
        leds_L->setPixelColor(currentPosition, leftColor);  // Color for the moving LED on the left strip
      } else {
        leds_L->setPixelColor(currentPosition, rightColor);  // Color for the moving LED on the left strip
      }
    }

    if (currentPosition < numPixels_R) {
      if (isLeftColorActive) {
        leds_R->setPixelColor(currentPosition, leftColor);  // Color for the moving LED on the right strip
      } else {
        leds_R->setPixelColor(currentPosition, rightColor);  // Color for the moving LED on the right strip
      }
    }

    // Show the updated strips
    leds_L->show();
    leds_R->show();

    // Update the position for the next LED (move down one step)
    currentPosition++;

    // If the current position exceeds the number of LEDs, reset the animation
    if (currentPosition >= numPixels_L) {
      currentPosition = 0;    // Reset to the top of the left strip
      numLitLEDs++;           // Increase the number of LEDs that should stay lit
      if (numLitLEDs >= numPixels_L) {
        numLitLEDs = numPixels_L - 1;  // Stop lighting more LEDs once the entire left strip is lit
      }
    }

    if (currentPosition >= numPixels_R) {
      currentPosition = 0;    // Reset to the top of the right strip
      numLitLEDs++;           // Increase the number of LEDs that should stay lit
      if (numLitLEDs >= numPixels_R) {
        numLitLEDs = numPixels_R - 1;  // Stop lighting more LEDs once the entire right strip is lit
      }
    }

    // After all LEDs are stacked with leftColor, switch to rightColor and repeat the animation
    if (numLitLEDs == numPixels_L - 1 && isLeftColorActive) {
      isLeftColorActive = false;  // Switch to the second color (rightColor)
      currentPosition = 0;        // Start over with the second color
      numLitLEDs = 0;             // Reset the lit LEDs counter for the second color animation
    }

    if (numLitLEDs == numPixels_R - 1 && !isLeftColorActive && !isAnimationComplete) {
      // Mark the animation as complete and prepare to reset
      isAnimationComplete = true;
      currentPosition = 0;        // Reset to the beginning
      numLitLEDs = 0;             // Reset the lit LEDs counter
      isLeftColorActive = true;   // Start with the first color (leftColor)
    }

    // If the second color has completed and animation is complete, start over
    if (isAnimationComplete && numLitLEDs == 0) {
      isAnimationComplete = false;  // Reset the completion flag
    }
  }
}





// Declare global variables for animation control


void stackingAnimation2(Adafruit_NeoPixel *strip, int SPEED_MS, uint32_t leftColor, uint32_t rightColor) {
  int numPixels = strip->numPixels();  // Get the number of LEDs in the strip
  
  unsigned long currentMillis = millis();  // Get the current time

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= SPEED_MS) {
    previousMillis = currentMillis;  // Update the last update time

    // Update the strip: 
    // Keep the LEDs lit with their current colors (leftColor or rightColor)
    for (int i = 0; i < numPixels; i++) {
      if (i <= numLitLEDs) {
        // Keep first color LEDs (leftColor) lit while stacking the second color (rightColor)
        if (isLeftColorActive) {
          strip->setPixelColor(i, leftColor);  // Keep previous LEDs lit with leftColor
        } else {
          strip->setPixelColor(i, rightColor);  // Keep previous LEDs lit with rightColor
        }
      } else {
        strip->setPixelColor(i, 0);  // Turn off the rest of the LEDs
      }
    }

    // Turn on the current moving LED with the active color
    if (currentPosition < numPixels) {
      if (isLeftColorActive) {
        strip->setPixelColor(currentPosition, leftColor);  // Color for the moving LED (leftColor)
      } else {
        strip->setPixelColor(currentPosition, rightColor);  // Color for the moving LED (rightColor)
      }
    }

    // Show the updated strip
    strip->show();

    // Update the position for the next LED (move down one step)
    currentPosition++;

    // If the current position exceeds the number of LEDs, reset the animation
    if (currentPosition >= numPixels) {
      currentPosition = 0;    // Reset to the top of the strip
      numLitLEDs++;           // Increase the number of LEDs that should stay lit
      if (numLitLEDs >= numPixels) {
        numLitLEDs = numPixels - 1;  // Stop lighting more LEDs once the entire strip is lit
      }
    }

    // After all LEDs are stacked with leftColor, switch to rightColor and repeat the animation
    if (numLitLEDs == numPixels - 1 && isLeftColorActive) {
      isLeftColorActive = false;  // Switch to the second color (rightColor)
      currentPosition = 0;        // Start over with the second color
      numLitLEDs = 0;             // Reset the lit LEDs counter for the second color animation
    }

    // Once the second color has stacked all LEDs, reset and repeat the process
    if (numLitLEDs == numPixels - 1 && !isLeftColorActive && !isAnimationComplete) {
      // Mark the animation as complete and prepare to reset
      isAnimationComplete = true;
      currentPosition = 0;        // Reset to the beginning
      numLitLEDs = 0;             // Reset the lit LEDs counter
      isLeftColorActive = true;   // Start with the first color (leftColor)
    }

    // If the second color has completed and animation is complete, start over
    if (isAnimationComplete && numLitLEDs == 0) {
      isAnimationComplete = false;  // Reset the completion flag
    }
  }
}


// Global variables for animation control






// Global variables for animation control


void stackingAnimation(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, int SPEED_MS, uint32_t leftColor, uint32_t rightColor) {
  int numPixels = leds_L->numPixels();  // Assuming both strips have the same number of LEDs
unsigned long previousMillis = 0;  // Store last update time
int currentPosition = 0;           // Current position for stacking animation
bool isAnimatingFirstColor = true; // Flag for first color animation
bool isAnimatingSecondColor = false; // Flag for second color animation
int direction = -1; // -1 for right-to-left, 1 for left-to-right
  unsigned long currentMillis = millis();  // Get the current time

  // Check if enough time has passed to update the LED position
  if (currentMillis - previousMillis >= SPEED_MS) {
    previousMillis = currentMillis;  // Update the last update time

    // Clear LEDs at the start of each animation cycle (if not already cleared)
    leds_L->clear();
    leds_R->clear();

    if (isAnimatingFirstColor) {
      // Light up the first color in a stacking animation, starting from the last LED
      if (direction == -1) { // Right to left
        // Only light up LEDs from the last towards the current position
        for (int i = numPixels - 1; i >= numPixels - currentPosition - 1; i--) {
          leds_L->setPixelColor(i, leftColor);  // Set first color
          leds_R->setPixelColor(i, leftColor);  // Set first color
        }
      }

      // Move to the next position (increment towards the lit side)
      currentPosition++;

      // If the first color animation is complete, switch to the second color animation
      if (currentPosition >= numPixels) {
        isAnimatingFirstColor = false;   // Stop animating the first color
        isAnimatingSecondColor = true;  // Start animating the second color
        currentPosition = 0;            // Reset position for second color
      }
    }

    if (isAnimatingSecondColor) {
      // Animate the second color from the unlit side (left side) towards the lit side
      if (direction == -1) { // Right to left
        // Keep the first color solid
        for (int i = numPixels - 1; i >= numPixels - currentPosition - 1; i--) {
          leds_L->setPixelColor(i, leftColor);  // Keep the first color solid
          leds_R->setPixelColor(i, leftColor);  // Keep the first color solid
        }
        // Animate second color towards the lit side
        for (int i = numPixels - currentPosition - 1; i >= 0; i--) {
          leds_L->setPixelColor(i, rightColor); // Animate second color towards lit side
          leds_R->setPixelColor(i, rightColor); // Animate second color towards lit side
        }
      }

      // Move to the next position (increment towards the lit side)
      currentPosition++;

      // If the second color animation completes, reset for continuous animation
      if (currentPosition >= numPixels) {
        currentPosition = 0;          // Reset position for another loop
        isAnimatingFirstColor = true; // Start the animation over
        isAnimatingSecondColor = false;
      }
    }

    // Show the updated strips
    leds_L->show();
    leds_R->show();
  }
}




