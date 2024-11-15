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
uint32_t randomColor = random(0xFFFFFF);  // Generate a random color

//------------------------------- RADIATION ---------------------------------------
float rcount = 0.0;


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
void colorWipe(Adafruit_NeoPixel *strip, uint32_t color, int wait) {
  for (int i = 0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, color);
    strip->show();
    delay(wait);
  }
}



//_____________________________________________ RANDOM MARCH _________________________________________*/
//--------------------------------------the madness of random leds_L-----------------------------------
void randomMarch(Adafruit_NeoPixel *strip) {
  int iCCW;
  // if()
  strip->setPixelColor(0, strip->Color(random(0, 255), random(0, 255), random(0, 255)));
  for (int idex = 1; idex < strip->numPixels(); idex++) {
    iCCW = adjacent_ccw(strip->numPixels(), idex);
    strip->setPixelColor(idex, strip->getPixelColor(iCCW));
  }
  strip->show();
  delay(BlinkerSpeed);
}



/*_____________________________________________ RGB PROPELLER _____________________________________*/
void rgbpropeller(Adafruit_NeoPixel *strip, int speed) {
  unsigned long t = millis();
  int shift = (t / speed) % NUM_LEDS_L;

  // set each pixel to left or right color based on its position
  for (int i = 0; i < NUM_LEDS_L; i++) {
    if ((i + shift) % NUM_LEDS_L >= NUM_LEDS_L / 2) {
      strip->setPixelColor(i, RightColor);
    } else {
      strip->setPixelColor(i, leftColor);
    }
  }

  strip->show();
  delay(10);  // small delay to prevent flickering
}



/*___________________________________________________ FIRE ______________________________________*/
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

void fire(Adafruit_NeoPixel *strip, int Cooling, int Sparking, int SpeedDelay) {
  byte heat[strip->numPixels()];
  int cooldown;

  for (int i = 0; i < strip->numPixels(); i++) {
    cooldown = random(0, ((Cooling * 10) / strip->numPixels()) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  for (int k = strip->numPixels() - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  if (random(255) < Sparking) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
  }

  for (int j = 0; j < strip->numPixels(); j++) {
    setPixelHeatColor(strip, j, heat[j]);
  }

  strip->show();
  delay(SpeedDelay);
}




/*__________________________________________________ BLUE FIRE _________________________________________*/
//----------------------------------------------- blue line fire----------------------------------------

void setPixelHeatColorBlue(Adafruit_NeoPixel *strip, int Pixel, byte temperature) {
  byte t192 = round((temperature / 255.0) * 191);
  byte heatramp = t192 & 0x03;
  heatramp <<= 2;

  if (t192 > 0x03) {
    strip->setPixelColor(Pixel, heatramp, 255, 255);
  } else if (t192 > 0x40) {
    strip->setPixelColor(Pixel, 255, heatramp, 0);
  } else {
    strip->setPixelColor(Pixel, 0, 0, heatramp);
  }
}


void blueFire(Adafruit_NeoPixel *strip, int Cooling, int Sparking, int SpeedDelay) {
  byte heat[strip->numPixels()];
  int cooldown;

  for (int i = 0; i < strip->numPixels(); i++) {
    cooldown = random(0, ((Cooling * 10) / strip->numPixels() + 2));

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }
  for (int k = strip->numPixels() - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
  if (random(255) < Sparking) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
  }
  for (int j = 0; j < strip->numPixels(); j++) {
    setPixelHeatColorBlue(strip, j, heat[j]);
  }
  strip->show();
  delay(SpeedDelay);
}


/*________________________________________________ RANDOM BURST ______________________________________*/
//--------------------------------------------- random color change-----------------------------------
void randomBurst(Adafruit_NeoPixel *strip) {
  idex = random(0, strip->numPixels());
  ihue = random(0, 65530);
  strip->setPixelColor(idex, strip->ColorHSV(ihue, isat, 255));
  strip->show();
  delay(100);
  strip->clear();
  strip->show();
}



/*______________________________________________ FLICKER ______________________________________________*/
//-----------------------------------------random strobe light------------------------------------------
void flicker(Adafruit_NeoPixel *strip) {
  strip->clear();
  strip->show();
  int random_bright = random(0, 255);
  int random_delay = random(10, 100);
  int random_bool = random(0, random_bright);
  if (random_bool < 10) {
    for (int i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, strip->ColorHSV(160, 50, random_bright));
    }
    strip->show();
    delay(random_delay);
  }
}


/* ________________________________________ RANDOM COLOR POP ________________________________________*/
//-------------------------------- the madness of random flashes -------------------------------------
void randomColorPop(Adafruit_NeoPixel *strip) {
  idex = random(0, strip->numPixels());
  strip->clear();
  strip->setPixelColor(idex, strip->Color(random(0, 255), random(0, 255), random(0, 255), random(0, 255)));
  strip->show();
  delay(_delay);
}



/*___________________________________________ SPARKLE ________________________________________________*/
//-----------------------------------random flashes of white--------------------------------------
void sparkle(Adafruit_NeoPixel *strip, byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(strip->numPixels());
  strip->setPixelColor(Pixel, red, green, blue, 255);
  strip->show();
  delay(SpeedDelay);
  strip->setPixelColor(Pixel, 0, 0, 0, 0);
  strip->show();
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
  delay(_delay);
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
  delay(_delay);
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
  delay(_delay);
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
  delay(_delay);
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
  delay(_delay);
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
  delay(_delay);
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
  delay(BlinkerSpeed);
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



/*___________________________________________________ THEATER CHASE _______________________________________________*/
void CandyCane(Adafruit_NeoPixel *strip, uint32_t leftColor, uint32_t RightColor, int BlinkerSpeed, int iterations) {
  int numPixels = strip->numPixels();
  int offset = 0;
  unsigned long previousMillis = 0;       // stores the time when the animation was last updated
  unsigned long interval = BlinkerSpeed;  // interval between animation frames (in milliseconds)

  for (int j = 0; j < numPixels * iterations; j++) {
    for (int i = 0; i < numPixels; i++) {
      if ((i + offset) % 6 < 3) {
        strip->setPixelColor(i, leftColor);
      } else {
        strip->setPixelColor(i, RightColor);
      }
    }

    strip->show();

    // Wait for a short time before the next animation frame
    unsigned long currentMillis = millis();  // get the current time
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;  // save the last update time
      offset++;
      if (offset >= 6) {
        offset = 0;
      }
      interval = BlinkerSpeed;  // update the interval variable with the BlinkerSpeed value
    }
  }
}



/*_______________________________________________ TheaterChase______________________________________________________*/
void theaterChase(Adafruit_NeoPixel *strip, byte red, byte green, byte blue, int _delay) {
  unsigned long previousMillis = 0;  // stores the time when the animation was last updated
  unsigned long interval = _delay;   // interval between animation frames (in milliseconds)

  for (int j = 0; j < 10; j++) {
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip->numPixels(); i = i + 3) {
        strip->setPixelColor(i + q, red, green, blue);
      }
      strip->show();

      // Wait for a short time before turning off pixels
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        for (int i = 0; i < strip->numPixels(); i = i + 3) {
          strip->setPixelColor(i + q, 0, 0, 0);
        }
        strip->show();
      }
    }
  }
}



/*__________________________________________________________ STROBE _______________________________________________________*/
//---------------------------------------------------- stroboscopic effect -------------------------------------------------
void strobe(Adafruit_NeoPixel *strip, byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause) {
  for (int j = 0; j < StrobeCount; j++) {
    strip->fill(strip->Color(red, green, blue, 0), 0, strip->numPixels() - 1);
    strip->show();
    delay(FlashDelay);
    strip->clear();
    strip->show();
    delay(FlashDelay);
  }

  delay(EndPause);
}



/* ____________________________________________________ POLICE BLINKER ____________________________________________________*/
void policeBlinker(Adafruit_NeoPixel *strip) {
  int hue = 0;
  uint16_t NumLeds = strip->numPixels();
  int thathue = (hue + 160) % 255;
  int thathue2 = (hue + 240) % 255;
  for (int x = 0; x < 5; x++) {
    for (int i = 0; i < NumLeds / 2; i++) {
      strip->setPixelColor(i, leds_L->Color(0, 0, 255));  // Set white
    }
    strip->show();
    delay(_delay);
    strip->clear();
    strip->show();
    delay(_delay);
  }
  for (int x = 0; x < 5; x++) {
    for (int i = NumLeds / 2; i < NumLeds; i++) {
      strip->setPixelColor(i, leds_R->Color(255, 0, 0));
    }
    strip->show();
    delay(_delay);
    strip->clear();
    strip->show();
    delay(_delay);
  }
}



/*______________________________________________________ KITT ________________________________________________________________*/
void kitt(Adafruit_NeoPixel *strip, int _delay, uint32_t leftColor) {
  uint16_t TOP_INDEX = strip->numPixels() / 2;

  int rand = random(0, TOP_INDEX) * 2;

  uint32_t startMillis = millis();

  for (int i = 0; i < rand; i++) {
    strip->setPixelColor(TOP_INDEX + i, leftColor);
    strip->setPixelColor(TOP_INDEX - i, leftColor);
    strip->show();
    while (millis() - startMillis < _delay / (rand * 2)) {}
  }

  startMillis = millis();

  for (int i = rand; i > 0; i--) {
    strip->setPixelColor(TOP_INDEX + i, strip->Color(0, 0, 0, 0));
    strip->setPixelColor(TOP_INDEX - i, strip->Color(0, 0, 0, 0));
    strip->show();
    while (millis() - startMillis < _delay / (rand)) {}
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



/*_______________________________________________________ BLENDE ___________________________________________________________*/
void blende() {
  for (int i = 0; i < leds_L->numPixels(); i++) {
    leds_L->setPixelColor(i, leftColor);
    leds_L->show();
    leds_R->setPixelColor(i, RightColor);
    leds_R->show();
    leds_3->setPixelColor(i, thrdColor);
    leds_3->show();
    delay(BlinkerSpeed);
    fadeall();
  }

  for (int i = leds_L->numPixels() - 1; i >= 0; i--) {
    leds_L->setPixelColor(i, leftColor);
    leds_L->show();
    leds_R->setPixelColor(i, RightColor);
    leds_R->show();
    leds_3->setPixelColor(i, thrdColor);
    leds_3->show();
    delay(BlinkerSpeed);
    fadeall();
  }
}



/*______________________________________________________ BLENDE 2 ___________________________________________________________*/
void blende_2(Adafruit_NeoPixel *strip, uint32_t stripColor) {
  for (int i = 0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, stripColor);
    strip->show();
    delay(10);
    fadeall();
  }
  for (int i = strip->numPixels() - 1; i >= 0; i--) {
    strip->setPixelColor(i, stripColor);
    strip->show();
    delay(10);
    fadeall();
  }
}

/*________________________________________________ CENTER TO OUTSIDE ________________________________________________________*/
void CenterToOutside(Adafruit_NeoPixel *strip, uint32_t stripColor, int EyeSize, int SpeedDelay, int ReturnDelay) {
  uint16_t NumLeds = strip->numPixels();
  byte red = (stripColor >> 16) & 0xFF;
  byte green = (stripColor >> 8) & 0xFF;
  byte blue = stripColor & 0xFF;

  for (int i = (NumLeds - EyeSize) / 2; i >= 0; i--) {
    strip->clear();

    strip->setPixelColor(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      strip->setPixelColor(i + j, red, green, blue);
    }
    strip->show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
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
void OutsideToCenter(Adafruit_NeoPixel *strip, uint32_t stripColor, int EyeSize, int BlinkerSpeed, int ReturnDelay) {
  uint16_t NumLeds = strip->numPixels();
  byte red = (stripColor >> 16) & 0xFF;
  byte green = (stripColor >> 8) & 0xFF;
  byte blue = stripColor & 0xFF;
  for (int i = 0; i <= ((NumLeds - EyeSize) / 2); i++) {
    strip->clear();
    strip->show();
    strip->setPixelColor(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      strip->setPixelColor(i + j, red, green, blue);
    }
    strip->setPixelColor(i + EyeSize + 1, red / 10, green / 10, blue / 10);

    strip->setPixelColor(NumLeds - i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      strip->setPixelColor(NumLeds - i - j, red, green, blue);
    }
    strip->setPixelColor(NumLeds - i - EyeSize - 1, red / 10, green / 10, blue / 10);

    strip->show();
    delay(BlinkerSpeed);
  }
  delay(ReturnDelay);
}



/*__________________________________________________ LEFT TO RIGHT ______________________________________________________*/
void LeftToRight(Adafruit_NeoPixel *strip, uint32_t stripColor, int EyeSize, int BlinkerSpeed, int ReturnDelay) {
  byte red = (stripColor >> 16) & 0xFF;
  byte green = (stripColor >> 8) & 0xFF;
  byte blue = stripColor & 0xFF;
  for (int i = 0; i < strip->numPixels() - EyeSize - 2; i++) {
    strip->clear();
    strip->show();
    strip->setPixelColor(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      strip->setPixelColor(i + j, red, green, blue);
    }
    strip->setPixelColor(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    strip->show();
    delay(BlinkerSpeed);
  }
  delay(ReturnDelay);
}



/*________________________________________________ DISSOLVE RANDOM ______________________________________________________*/
void dissolveRandom(Adafruit_NeoPixel *strip, int speed) {
  int numPixels = strip->numPixels();
  int numDissolve = numPixels;  // Number of LEDs to dissolve at a time

  // Create an array to store the indices of the LEDs
  int ledIndices[numPixels];
  for (int i = 0; i < numPixels; i++) {
    ledIndices[i] = i;
  }

  while (numDissolve > 0) {
    // Randomly select an LED from the array
    int index = random(numDissolve);
    int ledIndex = ledIndices[index];

    // Remove the selected LED index from the array
    for (int i = index; i < numDissolve - 1; i++) {
      ledIndices[i] = ledIndices[i + 1];
    }

    // Set the color of the selected LED to a random color
    strip->setPixelColor(ledIndex, strip->Color(random(200), random(200), random(200), random(0)));
    strip->show();

    numDissolve--;  // Decrement the number of LEDs to dissolve
    delay(speed);
  }

  // Turn off all LEDs after the effect finishes
  for (int i = 0; i < numPixels; i++) {
    strip->setPixelColor(i, 0, 0, 0);
  }
  strip->show();
}



/*____________________________________________________ SOLID COLOR FILL ___________________________________________________*/
void solid() {
  int numPixels_L = leds_L->numPixels();
  int numPixels_R = leds_R->numPixels();

  leds_L->fill(leftColor);
  leds_R->fill(RightColor);

  leds_L->show();
  leds_R->show();
}



/*________________________________________________________ SCANNER ________________________________________________________*/
void Scanner(Adafruit_NeoPixel *strip, int speed, uint32_t leftColor) {
  int numPixels = leds_L->numPixels();
  int scanWidth = 4;  // Width of the scanning light effect (number of LEDs lit at a time)

  // Run the KITT animation loop continuously
  while (true) {
    // Light up the LEDs in the forward direction
    for (int i = 0; i <= numPixels - scanWidth; i++) {
      for (int j = 0; j < scanWidth; j++) {
        strip->setPixelColor(i + j, leftColor);
      }
      strip->show();
      delay(speed);
    }
    // Light up the LEDs in the reverse direction
    for (int i = numPixels - scanWidth - 1; i >= 0; i--) {
      for (int j = 0; j < scanWidth; j++) {
        strip->setPixelColor(i + j, leftColor);
      }
      strip->show();
      delay(speed);
    }
  }
}



/*___________________________________________________________ KNIGHT RIDER ______________________________________________*/
void knightRider(int wait, int numLEDsToLight) {
  unsigned long previousMillis = 0;  // stores the time when the animation was last updated
  unsigned long interval = wait;     // interval between animation frames (in milliseconds)

  int numPixelsLeft = leds_L->numPixels();
  int numPixelsRight = leds_R->numPixels();
  int numPixelsExtra = leds_3->numPixels();

  int i = 0;  // index of the leftmost LED to light up

  while (i < numPixelsLeft + numLEDsToLight) {
    unsigned long currentMillis = millis();  // get the current time

    // Check if it's time to update the animation
    if (currentMillis - previousMillis >= interval) {
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
void Middle3Out(int wait) {
  int numPixelsLeft = leds_L->numPixels();
  int numPixelsRight = leds_R->numPixels();
  int numPixels = max(numPixelsLeft, numPixelsRight);
  int middlePixel = numPixels / 2;

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
    delay(wait);
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
    delay(wait);
  }
}



/*__________________________________________________________________ MIDDLE 4 OUT STACKER___________________________________________________*/
void Middle4OutStacker(int wait_time, uint32_t Color) {
  int numPixels = max(NUM_LEDS_L, NUM_LEDS_R);
  int lastOffLED = 0;

  while (true) {
    for (int i = 0; i < numPixels - 1; i++) {
      for (int j = 0; j <= i; j++) {
        leds_L->setPixelColor(j, Color);
        leds_R->setPixelColor(j, Color);
      }

      // Turn on the last LED that was off.
      if (lastOffLED <= i) {
        leds_L->setPixelColor(lastOffLED, Color);
        leds_R->setPixelColor(lastOffLED, Color);
      }

      leds_L->show();
      leds_R->show();
      delay(wait_time);

      for (int j = 0; j <= i; j++) {
        leds_L->setPixelColor(j, 0, 0, 0);
        leds_R->setPixelColor(j, 0, 0, 0);
      }
    }

    // Turn on the last LED that was off.
    if (lastOffLED < numPixels - 1) {
      lastOffLED++;
      leds_L->setPixelColor(lastOffLED, Color);
      leds_R->setPixelColor(lastOffLED, Color);
    }

    delay(wait_time);  // Keep all LEDs on for an extra duration.
  }
}



/*__________________________________________________________________ MIDDLE 40 OUT STACKER___________________________________________________*/
void Middle4O0utStacker(int wait_time, int stacker_wait_time, uint32_t LeftColor, uint32_t RightColor) {
  int numPixels = max(NUM_LEDS_L, NUM_LEDS_R);
  int middlePixel = numPixels / 2;
  int current_middle_pixel = 0;

  while (true) {

    for (int i = 0; i <= current_middle_pixel; i++) {
      for (int j = 0; j < NUM_LEDS_L; j++) {
        if (j >= middlePixel - i && j <= middlePixel + i) {
          leds_L->setPixelColor(j, leftColor);
        } else {
          leds_L->setPixelColor(j, 0, 0, 0);
        }
      }
      for (int j = 0; j < NUM_LEDS_R; j++) {
        if (j >= middlePixel - i && j <= middlePixel + i) {
          leds_R->setPixelColor(j, RightColor);
        } else {
          leds_R->setPixelColor(j, 0, 0, 0);
        }
      }

      if (i == current_middle_pixel && current_middle_pixel != middlePixel) {
        for (int j = current_middle_pixel + 1; j < NUM_LEDS_L; j++) {
          leds_L->setPixelColor(j, leftColor);
        }
        for (int j = current_middle_pixel + 1; j < NUM_LEDS_R; j++) {
          leds_R->setPixelColor(j, RightColor);
        }
      }

      leds_L->show();
      leds_R->show();
      delay(wait_time);
    }

    delay(stacker_wait_time);  // wait for stacker_wait_time

    for (int i = current_middle_pixel; i >= 0; i--) {
      for (int j = 0; j < NUM_LEDS_L; j++) {
        if (j >= middlePixel - i && j <= middlePixel + i) {
          leds_L->setPixelColor(j, leftColor);
        } else {
          leds_L->setPixelColor(j, 0, 0, 0);
        }
      }
      for (int j = 0; j < NUM_LEDS_R; j++) {
        if (j >= middlePixel - i && j <= middlePixel + i) {
          leds_R->setPixelColor(j, RightColor);
        } else {
          leds_R->setPixelColor(j, 0, 0, 0);
        }
      }

      if (i == 0) {
        for (int j = current_middle_pixel + 1; j < NUM_LEDS_L; j++) {
          leds_L->setPixelColor(j, leftColor);
        }
        for (int j = current_middle_pixel + 1; j < NUM_LEDS_R; j++) {
          leds_R->setPixelColor(j, RightColor);
        }
      }

      leds_L->show();
      leds_R->show();
      delay(wait_time);
    }

    delay(stacker_wait_time);  // wait for stacker_wait_time

    current_middle_pixel++;
    if (current_middle_pixel > middlePixel) {
      current_middle_pixel = 0;
    }
  }
}


void Middle40OutStacker(int wait_time, int stacker_wait_time) {
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
      bool stack_on = false;

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

        if (i == current_middle_pixel && current_middle_pixel != middlePixel) {
          stack_on = true;
        }

        if (stack_on) {
          for (int j = current_middle_pixel + 1; j < numPixelsLeft; j++) {
            leds_L->setPixelColor(j, leftColor);
          }
          for (int j = current_middle_pixel + 1; j < numPixelsRight; j++) {
            leds_R->setPixelColor(j, RightColor);
          }
        }

        leds_L->show();
        leds_R->show();
      }

      if (current_middle_pixel >= middlePixel) {
        for (int j = 0; j < numPixelsLeft; j++) {
          leds_L->setPixelColor(j, leftColor);
        }
        for (int j = 0; j < numPixelsRight; j++) {
          leds_R->setPixelColor(j, RightColor);
        }
        leds_L->show();
        leds_R->show();
        delay(stacker_wait_time);  // wait for stacker_wait_time
        current_middle_pixel = 0;  // reset to restart animation
      }

      current_middle_pixel++;
    }
  }
}
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
void breatheAnimation(Adafruit_NeoPixel *leds_L, Adafruit_NeoPixel *leds_R, Adafruit_NeoPixel *leds_3, uint32_t leftColor, uint32_t rightColor, uint32_t thrdColor, int delay_ms) {
  static int minBrightness = 10;   // Minimum brightness value
  static int maxBrightness = 255;  // Maximum brightness value
  static int brightness_L = minBrightness;
  static int brightness_R = minBrightness;
  static int brightness_3 = minBrightness;
  static int direction_L = 1;  // 1 for increasing brightness, -1 for decreasing
  static int direction_R = 1;  // 1 for increasing brightness, -1 for decreasing
  static int direction_3 = 1;  // 1 for increasing brightness, -1 for decreasing
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= delay_ms) {
    leds_L->fill(leds_L->Color(
      (uint8_t)((leftColor >> 16) & 0xFF),  // Red component
      (uint8_t)((leftColor >> 8) & 0xFF),   // Green component
      (uint8_t)(leftColor & 0xFF)           // Blue component
      ));

    leds_R->fill(leds_R->Color(
      (uint8_t)((RightColor >> 16) & 0xFF),  // Red component
      (uint8_t)((RightColor >> 8) & 0xFF),   // Green component
      (uint8_t)(RightColor & 0xFF)           // Blue component
      ));
    leds_3->fill(leds_3->Color(
      (uint8_t)((thrdColor >> 16) & 0xFF),  // Red component
      (uint8_t)((thrdColor >> 8) & 0xFF),   // Green component
      (uint8_t)(thrdColor & 0xFF)           // Blue component
      ));

    leds_L->setBrightness(brightness_L);
    leds_R->setBrightness(brightness_R);
    leds_3->setBrightness(brightness_3);

    leds_L->show();
    leds_R->show();
    leds_3->show();

    // Change brightness and direction for both strips
    brightness_L += direction_L;
    brightness_R += direction_R;
    brightness_3 += direction_3;

    if (brightness_L >= maxBrightness || brightness_L <= minBrightness) {
      direction_L *= -1;
    }

    if (brightness_R >= maxBrightness || brightness_R <= minBrightness) {
      direction_R *= -1;
    }
    if (brightness_3 >= maxBrightness || brightness_3 <= minBrightness) {
      direction_3 *= -1;
    }

    previousMillis = currentMillis;
  }
}



/*__________________________________________________________________ COLOR BOUNCE RAIN ___________________________________________________*/
void colorBounceRain(Adafruit_NeoPixel *strip, int delayMs, int numLEDsLit) {
  static int position = 0;                   // Current LED position
  static int direction = 1;                  // 1 for moving right, -1 for moving left
  static uint32_t color = random(0xFFFFFF);  // Random initial color

  // Clear all LEDs
  strip->clear();

  // Set the color for the lit LEDs
  for (int i = position; i < position + numLEDsLit; i++) {
    strip->setPixelColor(i, color);
  }

  strip->show();

  // Move the position
  position += direction;

  // Reverse direction when hitting the end
  if (position == (strip->numPixels() - 1) || position == 0) {
    direction *= -1;

    // Generate a new random color when bouncing back
    color = random(0xFFFFFF);  // Random 24-bit color
  }

  // Delay for the specified time
  delay(delayMs);
}



/*__________________________________________________________________ COLOR BOUNCE _____________________________________________________________*/
void colorBounce(Adafruit_NeoPixel *strip, uint32_t color, int delay_ms, int numLEDsLit) {
  static int position = 0;   // Current LED position
  static int direction = 1;  // 1 for moving right, -1 for moving left

  // Clear all LEDs
  strip->clear();

  // Set the color for the lit LEDs
  for (int i = position; i < position + numLEDsLit; i++) {
    strip->setPixelColor(i, color);
  }

  strip->show();

  // Move the position
  position += direction;

  // Reverse direction when hitting the end
  if (position == (strip->numPixels() - 1) || position == 0) {
    direction *= -1;
  }

  // Delay for the specified time
  delay(delay_ms);
}




/*__________________________________________________________ TETRIS ANIMATION ________________________________________________________________*/
void tetrisAnimation(Adafruit_NeoPixel *strip, int SPEED_MS) {
  static int ledPosition = 0;                        // Initialize LED position
  static uint32_t color1 = strip->Color(255, 0, 0);  // Color 1 (Red)
  static uint32_t color2 = strip->Color(0, 255, 0);  // Color 2 (Green)

  // Shift all LEDs one position to the right (creates the stacking effect)
  for (int i = NUM_LEDS_L - 1; i > 0; i--) {
    strip->setPixelColor(i, strip->getPixelColor(i - 1));
  }

  // Smooth color transition for the bottom LED
  uint32_t bottomColor = strip->getPixelColor(0);
  uint8_t r1 = (bottomColor >> 16) & 0xFF;
  uint8_t g1 = (bottomColor >> 8) & 0xFF;
  uint8_t b1 = (bottomColor)&0xFF;

  uint8_t r2 = (color2 >> 16) & 0xFF;
  uint8_t g2 = (color2 >> 8) & 0xFF;
  uint8_t b2 = (color2)&0xFF;

  r1 = (r1 + r2) / 2;
  g1 = (g1 + g2) / 2;
  b1 = (b1 + b2) / 2;

  strip->setPixelColor(0, strip->Color(r1, g1, b1));

  strip->show();

  // Delay to control the animation speed
  delay(SPEED_MS);
}
/*
  static int ledPosition = 0; // Initialize LED position
  static bool isColor1Active = true; // Flag to toggle between colors

  // Set the color for the current LED position
  if (isColor1Active) {
    strip->setPixelColor(ledPosition, COLOR1);
  } else {
    strip->setPixelColor(ledPosition, COLOR2);
  }

  // Show the current LED
  strip->show();

  // Delay to make the colors stack
  delay(SPEED_MS);

  // Move to the next LED
  ledPosition++;

  // Check if all LEDs have been lit
  if (ledPosition >= NUM_LEDS_L) {
    isColor1Active = !isColor1Active; // Toggle between colors
    ledPosition = 0; // Reset to the first LED
  }
}*/




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
void SwipeRandomAnimation() {
  // Define the random color outside of the loops
  uint32_t randomColor = random(0, 0xFFFFFF + 1);

  // First loop
  for (int j = NUM_LEDS_L - 1; j >= 0; j--) {
    leds_L->setPixelColor(j, randomColor);
    leds_R->setPixelColor(NUM_LEDS_R - j - 1, randomColor);  // Mirror position for leds_R
  }
  leds_L->show();
  leds_R->show();
  delay(StartupSpeed);

  // Second loop - turn off LEDs sequentially
  for (int i = 0; i < NUM_LEDS_L; i++) {
    leds_L->setPixelColor(i, 0);                   // Turn off LED on the left side
    leds_R->setPixelColor(NUM_LEDS_R - i - 1, 0);  // Turn off LED on the right side
  }
  leds_L->show();
  leds_R->show();
  delay(StartupSpeed);

  // Turn off LEDs after the second loop
  for (int i = 0; i < NUM_LEDS_L; i++) {
    leds_L->setPixelColor(i, 0);
    leds_R->setPixelColor(NUM_LEDS_R - i - 1, 0);  // Mirror position for leds_R
  }
  leds_L->show();
  leds_R->show();

  // Third loop
  for (int j = NUM_LEDS_L - 1; j >= 0; j--) {
    leds_L->setPixelColor(j, randomColor);
    leds_R->setPixelColor(NUM_LEDS_R - j - 1, randomColor);  // Mirror position for leds_R
  }
  leds_L->show();
  leds_R->show();
  delay(StartupSpeed);
}



/*_________________________________________________________ STACKING ANIMATION _________________________________________________________________*/
void stackingAnimation(Adafruit_NeoPixel *strip, int BlinkerSpeed) {
}



/*__________________________________________________________ SCAN SWEEP ANIMATION ______________________________________________________________*/
void scanSweepAnimation(Adafruit_NeoPixel *strip, int BlinkerSpeed, uint32_t color) {
}


//######################################################################################
// -------------------------------- MATRIX -------------------------------------
