
/*Car Part Functions

------------------------THESE FUNCTIONS ARE CALLED FROM THE CAR INPUT HANDLING TO DISPLAY THE RELEAVANT OUTPUT FROM PRESSED INPUTS---------------------------

*/

/*..........................UPDATABLE FUNCTIONS............................S*/
void MiddleOff() {
}

void BrakeMiddle() {
}

void ParkMiddle() {
}


/*____________________________________ PARK FULL ________________________________________*/

void ParkFull2() {
  // Check if left blinker pin is high, if so, turn off left LEDs
  if (digitalRead(LeftSignal) == HIGH) {
    // Turn off all LEDs in the left strip
    for (int i = 0; i < NUM_LEDS_L; i++) {
      leds_L->setPixelColor(i, 0);  // Set color to off (0)
    }
    leds_L->show();  // Show the updated state

    // Delay for 1 second
    delay(1000);

    // After delay, check again if left blinker is still active
    if (digitalRead(LeftSignal) == HIGH) {
      // Still active after delay, turn left LEDs back on
      for (int i = 0; i < NUM_LEDS_L; i++) {
        leds_L->setPixelColor(i, DRLColor);
      }
      leds_L->show();  // Show the color on the left LEDs
    }
  } else {
    // Set all LEDs in the left strip to the specified color
    for (int i = 0; i < NUM_LEDS_L; i++) {
      leds_L->setPixelColor(i, DRLColor);
    }
    leds_L->show();  // Show the color on the left LEDs
  }

  // Check if right blinker pin is high, if so, turn off right LEDs
  if (digitalRead(RightSignal) == HIGH) {
    // Turn off all LEDs in the right strip
    for (int i = 0; i < NUM_LEDS_R; i++) {
      leds_R->setPixelColor(i, 0);  // Set color to off (0)
    }
    leds_R->show();  // Show the updated state

    // Delay for 1 second
    delay(1000);

    // After delay, check again if right blinker is still active
    if (digitalRead(RightSignal) == HIGH) {
      // Still active after delay, turn right LEDs back on
      for (int i = 0; i < NUM_LEDS_R; i++) {
        leds_R->setPixelColor(i, DRLColor);
      }
      leds_R->show();  // Show the color on the right LEDs
    }
  } else {
    // Set all LEDs in the right strip to the specified color
    for (int i = 0; i < NUM_LEDS_R; i++) {
      leds_R->setPixelColor(i, DRLColor);
    }
    leds_R->show();  // Show the color on the right LEDs
  }
}

/*__________________________________________ PARK FULL __________________________________*/
void ParkFull() {
  for (int i = 0; i < NUM_LEDS_L; i++) {
    leds_L->setPixelColor(i, DRLColor);
  }
  leds_L->show();  // Show the color on the left LEDs

  // Set all LEDs in the right strip to the specified color
  for (int i = 0; i < NUM_LEDS_R; i++) {
    leds_R->setPixelColor(i, DRLColor);
  }
  leds_R->show();  // Show the color on the right LEDs
}

/*_______________________________________REVERSE________________________________________*/
void Reverse() {

  leds_L->fill(DRLColor);
  leds_R->fill(DRLColor);
  leds_L->show();
  leds_R->show();
}

void fadeall() {
  leds_3->clear();
  leds_3->show();
  leds_L->clear();
  leds_L->show();
  leds_R->clear();
  leds_R->show();
}


/*_____________________________________ BRAKE FULL ____________________________________*/
void BrakeFull() {
  leds_L->fill(BrakeColor);
  leds_R->fill(BrakeColor);
  leds_L->show();
  leds_R->show();
  if (Strobe == 1 && strobePerformed == 0) {
    for (int i = 0; i < 5; i++) {
      fadeall();
      delay(200);
      leds_L->fill(BrakeColor);
      leds_R->fill(BrakeColor);
      leds_L->show();
      leds_R->show();
      leds_L->setBrightness(100);
      leds_R->setBrightness(100);
    }
    strobePerformed = 1;
  }
}

/*___________________________________ ALL OFF _________________________________________*/
void AllOff() {
  // Turn off LEDs for left strip
  for (int i = 0; i < leds_L->numPixels(); i++) {
    leds_L->setPixelColor(i, 0);
  }
  leds_L->show();

  // Turn off LEDs for right strip
  for (int i = 0; i < leds_R->numPixels(); i++) {
    leds_R->setPixelColor(i, 0);
  }
  leds_R->show();

  // Turn off LEDs for third strip
  for (int i = 0; i < leds_3->numPixels(); i++) {
    leds_3->setPixelColor(i, 0);
  }
  leds_3->show();
}

// =============================================== LEFT LEDS FUNCTIONS ========================files==========================================

/*___________________________________LEFT LEDS OFF ____________________________________*/
void LeftOff() {
  leds_L->clear();
  leds_L->show();
}


/*_________________________________ RIGHT BLINKER FUNCTIONS __________________________________________*/
void RightBlinker() {
  if (BlinkerAnimation == 1) {
    RightHeartBeat();
  } else if (BlinkerAnimation == 2) {
    RightSequential();
  } else if (BlinkerAnimation == 3) {
    RightOriginal();
  } else {
    RightSequentialSolid();
  }
}

void RightSequential() {

  if (RightDirection == 1) {
    // Forward direction
    for (int i = 0; i < BlinkerLEDs; i++) {
      leds_R->setPixelColor(i, RightColor);
      delay(BlinkerSpeed);
      leds_R->show();
    }
  } else if (RightDirection == 2) {
    // Reverse direction
    for (int i = BlinkerLEDs - 1; i >= 0; i--) {
      leds_R->setPixelColor(i, RightColor);
      delay(BlinkerSpeed);
      leds_R->show();
    }
  }
}

void RightSequentialSolid() {
  // Turn on the LEDs sequentially based on the direction
  if (RightDirection == 1) {
    // Forward direction
    for (int i = 0; i < BlinkerLEDs; i++) {
      leds_R->setPixelColor(i, RightColor);  // Set RGB color
    }
  } else if (RightDirection == 2) {
    // Reverse direction
    for (int i = BlinkerLEDs - 1; i >= 0; i--) {
      leds_R->setPixelColor(i, RightColor);  // Set RGB color
    }
  }
  leds_R->show();
  delay(1000);  // Adjust this delay to determine how long the tail lights stay on

  // Clear LEDs before starting the turn-off animation
  leds_R->clear();
  leds_R->show();

  // Turn off the LEDs sequentially based on the direction
  if (RightDirection == 1) {
    // Forward direction for turning off
    for (int i = 0; i < BlinkerLEDs; i++) {
      leds_R->setPixelColor(i, 0);  // Turn off the LED
      leds_R->show();
      delay(BlinkerSpeed);  // Adjust this delay to control the speed of turning off
    }
  } else if (RightDirection == 2) {
    // Reverse direction for turning off
    for (int i = BlinkerLEDs - 1; i >= 0; i--) {
      leds_R->setPixelColor(i, 0);  // Turn off the LED
      leds_R->show();
      delay(BlinkerSpeed);  // Adjust this delay to control the speed of turning off
    }
  }

  // Clear LEDs at the end of the animation
  leds_R->clear();
  leds_R->show();
}
void RightOriginal() {
  leds_R->clear();
  leds_R->show();
  // blink the Right strip
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, RightColor);
  }
  leds_R->show();
  delay(BlinkerSpeed);
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, 0x000000);
  }
  leds_R->show();
  delay(BlinkerSpeed);
}

/*__________________________ RIGHT HEARTBEAT _____________________________________________*/
void RightHeartBeat() {
  const int FadeSteps = 100;  // Number of steps for the fade effect
  leds_R->clear();
  leds_R->show();
  for (int brightness = 0; brightness <= 255; brightness += 255 / FadeSteps) {
    for (int i = BlinkerLEDs - 1; i >= 0; i--) {
      uint8_t r = (RightColor >> 16) & 0xFF;
      uint8_t g = (RightColor >> 8) & 0xFF;
      uint8_t b = RightColor & 0xFF;
      uint32_t fadedColor = leds_R->Color((r * brightness) / 255, (g * brightness) / 255, (b * brightness) / 255);
      leds_R->setPixelColor(i, fadedColor);
    }
    leds_R->show();
    delay(BlinkerSpeed);
  }
  for (int brightness = 255; brightness >= 0; brightness -= 255 / FadeSteps) {
    for (int i = BlinkerLEDs - 1; i >= 0; i--) {
      uint8_t r = (RightColor >> 16) & 0xFF;
      uint8_t g = (RightColor >> 8) & 0xFF;
      uint8_t b = RightColor & 0xFF;
      uint32_t fadedColor = leds_R->Color((r * brightness) / 255, (g * brightness) / 255, (b * brightness) / 255);
      leds_R->setPixelColor(i, fadedColor);
    }
    leds_R->show();
    delay(BlinkerSpeed);
  }
}

/*________________________ RIGHT SEQUENCIAL SOLID ________________________________________*/

/*_____________________________ RIGHT LEDS OFF _________________________________________*/
void RightOff() {
  leds_R->clear();
  leds_R->show();
}
/*_____________________________ RIGHT DIM ______________________________________________*/
void RightDim() {
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, DRLColor);
  }
  leds_R->show();
}

/*_____________________________ RIGHT DIM OFF __________________________________________*/
void RightDimOff() {
  for (int i = 0; i < NUM_LEDS_R; i++) {
    leds_R->setPixelColor(i, leds_R->Color(0, 0, 0,0));  // RGB values set to 0
  }
  leds_R->show();  // Show the updated state of the LEDs
  

}

/*_____________________________ RIGHT LIT _______________________________________________*/
void RightLit() {

  leds_R->fill(RightColor);
  leds_R->show();
}

/*_________________________________________ RIGHT FULL __________________________________________________*/
void RightFull() {

  leds_R->fill(DRLColor);
  leds_R->show();
}





//============================================== DRL LEDS CONTROL =========================================

/*________________________________________ DRL LEFT FULL ________________________________________*/


void DRLLeftFull() {
  unsigned long previousMillis = 0;
  const long interval = 0;  // Time interval for updating each LED
  unsigned long currentMillis = millis();


  // Only update if the required interval has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Loop through all LEDs and set their color
    for (int i = 0; i < BlinkerLEDs; i++) {
      leds_L->setPixelColor(i, DRLColor);  // Set the color for each LED
    }

    leds_L->show();  // Apply the changes
  }
}
/*___________________________________DRL LEFT LIT _______________________________________________*/
void DRLLeftLit() {
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_3->setPixelColor(i, DRLColor);
  }

  leds_3->show();
}

/*___________________________________DRL RIGHT LIT _______________________________________________________*/
void DRLRightLit() {

  leds_R->fill(DRLColor);
  leds_R->show();
}

/*__________________________________________ DRL RIGHT OFF _______________________________________________*/
void DRLRightOff() {
  leds_R->fill(0, 0, 0);  // Fill the LEDs with the "off" color
  leds_R->show();
}


/*___________________________________________ DRL RIGHT FULL ____________________________________*/
void DRLRighttFull() {
  unsigned long previousMillis = 0;
  const long interval = 0;  // Time interval for updating each LED
  unsigned long currentMillis = millis();


  // Only update if the required interval has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Loop through all LEDs and set their color
    for (int i = 0; i < BlinkerLEDs; i++) {
      leds_R->setPixelColor(i, DRLColor);  // Set the color for each LED
    }

    leds_R->show();  // Apply the changes
  }
}

/*____________________________________________ DRL ON ___________________________________________*/
void DRLON() {
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_L->setPixelColor(i, DRLColor);
  }
  leds_L->show();

  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, DRLColor);
  }
  leds_R->show();
}

/*_________________________________________ DRL LEFT FULLY OFF ____________________________________*/
void DRLLeftFullOff() {
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_L->setPixelColor(i, leds_L->Color(0, 0, 0));
  }
  leds_L->show();
}

/*_________________________________________ DRL RIGHT FULLY OFF ___________________________________*/
void DRLRightFullOff() {
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, leds_R->Color(0, 0, 0));
  }
  leds_R->show();
}


/*________________________________________________ DRL FULL _______________________________________________________*/
void ThirdFull() {
  leds_3->fill(thrdColor);
}




// ============================================================ DUAL LED CONTROL =========================================================================
/*________________________________________________ DUAL BLINKER ______________________________________________*/
void DualBlinker() {
  if (BlinkerAnimation == 1) {
    DualHeartBeat();
  } else if (BlinkerAnimation == 2) {
    DualSequential();
  } else if (BlinkerAnimation == 3) {
    DualOriginal();
  } else {
    DualSequentialSolid();
  }
}
/*________________________________________ DUAL SEQUENCIAL SOLID _________________________________________*/
void DualSequentialSolid() {
  int j;  // Declare j here
  for (int i = 0; i < BlinkerLEDs; i++) {
    j = BlinkerLEDs - i - 1;               // Calculate the opposite index for leds_L
    leds_L->setPixelColor(j, leftColor);   // Set color for leds_L in reverse order
    leds_R->setPixelColor(i, RightColor);  // Set color for leds_R in original order
  }
  leds_R->show();
  leds_L->show();
  delay(1000);  // Adjust this delay to determine how long the tail lights stay on

  // Sequentially turn off the tail lights
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, leds_R->Color(0, 0, 0));  // Turn off leds_R
    j = BlinkerLEDs - i - 1;                           // Calculate the opposite index for leds_L
    leds_L->setPixelColor(j, leds_L->Color(0, 0, 0));  // Turn off leds_L in reverse order
    leds_R->show();
    leds_L->show();
    delay(BlinkerSpeed);  // Adjust this delay to control the speed of turning off
  }
}

/*_________________________________________ DUAL HEARTBEAT ______________________________________________-*/
void DualHeartBeat() {
  const int FadeSteps = 100;  // Number of steps for the fade effect

  // Fade-in effect for right blinker
  for (int brightness = 0; brightness <= 255; brightness += 255 / FadeSteps) {
    for (int i = 0; i < BlinkerLEDs; i++) {
      uint8_t r = (RightColor >> 16) & 0xFF;
      uint8_t g = (RightColor >> 8) & 0xFF;
      uint8_t b = RightColor & 0xFF;

      uint8_t r2 = (leftColor >> 16) & 0xFF;
      uint8_t g2 = (leftColor >> 8) & 0xFF;
      uint8_t b2 = leftColor & 0xFF;

      uint32_t fadedColorR = leds_R->Color((r * brightness) / 255, (g * brightness) / 255, (b * brightness) / 255);
      uint32_t fadedColorL = leds_L->Color((r2 * brightness) / 255, (g2 * brightness) / 255, (b2 * brightness) / 255);
      leds_R->setPixelColor(i, fadedColorR);
      leds_L->setPixelColor(i, fadedColorL);
    }
    leds_R->show();
    leds_L->show();
    delay(BlinkerSpeed);
  }

  // Fade-out effect for right blinker
  for (int brightness = 255; brightness >= 0; brightness -= 255 / FadeSteps) {
    for (int i = 0; i < BlinkerLEDs; i++) {
      uint8_t r = (RightColor >> 16) & 0xFF;
      uint8_t g = (RightColor >> 8) & 0xFF;
      uint8_t b = RightColor & 0xFF;

      uint8_t r2 = (leftColor >> 16) & 0xFF;
      uint8_t g2 = (leftColor >> 8) & 0xFF;
      uint8_t b2 = leftColor & 0xFF;

      uint32_t fadedColorR = leds_R->Color((r * brightness) / 255, (g * brightness) / 255, (b * brightness) / 255);
      uint32_t fadedColorL = leds_L->Color((r2 * brightness) / 255, (g2 * brightness) / 255, (b2 * brightness) / 255);
      leds_R->setPixelColor(i, fadedColorR);
      leds_L->setPixelColor(i, fadedColorL);
    }
    leds_R->show();
    leds_L->show();
    delay(BlinkerSpeed);
  }
}

/*_________________________________________ DUAL ORIGINAL __________________________________________*/
void DualOriginal() {
  // Blink effect for right blinker
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, RightColor);
    leds_L->setPixelColor(i, leftColor);
  }
  leds_R->show();
  leds_L->show();
  delay(BlinkerSpeed);
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, 0x000000);
    leds_L->setPixelColor(i, 0x000000);
  }
  leds_R->show();
  leds_L->show();
  delay(BlinkerSpeed);
}

/*________________________________________________ DUAL SEQUENCIAL __________________________________________*/
void DualSequential() {
  int j;  // Declare j here

  for (int i = 0; i < BlinkerLEDs; i++) {
    j = BlinkerLEDs - i - 1;  // Calculate the opposite index for leds_L
    leds_L->setPixelColor(j, leftColor);
    leds_R->setPixelColor(i, RightColor);
    leds_L->show();
    leds_R->show();
    delay(BlinkerSpeed);
  }
}



/*_________________________________LEFT BLINKER Functions __________________________________________*/
void LeftBlinker() {
  if (BlinkerAnimation == 1) {
    HeartBeat();
  } else if (BlinkerAnimation == 2) {
    Sequential();
  } else if (BlinkerAnimation == 3) {
    Original();
  } else {
    SolidSequential();
  }
}

void HeartBeat() {
  const int FadeSteps = 100;

  for (int brightness = 0; brightness <= 255; brightness += 255 / FadeSteps) {
    for (int i = 0; i < BlinkerLEDs; i++) {  // Changed loop direction to start from 0
      uint8_t r = (leftColor >> 16) & 0xFF;
      uint8_t g = (leftColor >> 8) & 0xFF;
      uint8_t b = leftColor & 0xFF;
      uint32_t fadedColor = leds_L->Color((r * brightness) / 255, (g * brightness) / 255, (b * brightness) / 255);
      leds_L->setPixelColor(i, fadedColor);
    }
    leds_L->show();
    delay(BlinkerSpeed);
  }

  for (int brightness = 255; brightness >= 0; brightness -= 255 / FadeSteps) {
    for (int i = 0; i < BlinkerLEDs; i++) {  // Changed loop direction to start from 0
      uint8_t r = (leftColor >> 16) & 0xFF;
      uint8_t g = (leftColor >> 8) & 0xFF;
      uint8_t b = leftColor & 0xFF;
      uint32_t fadedColor = leds_L->Color((r * brightness) / 255, (g * brightness) / 255, (b * brightness) / 255);
      leds_L->setPixelColor(i, fadedColor);
    }
    leds_L->show();
    delay(BlinkerSpeed);
  }
}

void Sequential() {
  // Clear LEDs at the beginning of the animation
  leds_L->clear();
  leds_L->show();

  // Sequentially turn on LEDs based on the direction
  if (LeftDirection == 1) {
    // Forward direction
    for (int i = 0; i < BlinkerLEDs; i++) {
      leds_L->setPixelColor(i, leftColor);  // Set RGB color
      delay(BlinkerSpeed);
      leds_L->show();
    }
  } else if (LeftDirection == 2) {
    // Reverse direction
    for (int i = BlinkerLEDs - 1; i >= 0; i--) {
      leds_L->setPixelColor(i, leftColor);  // Set RGB color
      delay(BlinkerSpeed);
      leds_L->show();
    }
  }

  // Clear LEDs after the animation
  leds_L->clear();
  leds_L->show();
}

void Original() {
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_L->setPixelColor(i, leftColor);
  }
  leds_L->show();
  delay(BlinkerSpeed);
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_L->setPixelColor(i, 0);  // Turn off the LED
  }
  leds_L->show();
  delay(BlinkerSpeed);
}

void SolidSequential() {
  // Clear LEDs at the beginning of the animation
  leds_L->clear();
  leds_L->show();

  // Turn on the LEDs sequentially based on the direction
  if (LeftDirection == 1) {
    // Forward direction
    for (int i = 0; i < BlinkerLEDs; i++) {
      leds_L->setPixelColor(i, leftColor);  // Set RGB color
    }
  } else if (LeftDirection == -1) {
    // Reverse direction
    for (int i = BlinkerLEDs - 1; i >= 0; i--) {
      leds_L->setPixelColor(i, leftColor);  // Set RGB color
    }
  }
  leds_L->show();
  delay(1000);  // Adjust this delay to determine how long the tail lights stay on

  // Clear LEDs before starting the turn-off animation
  leds_L->clear();
  leds_L->show();

  // Turn off the LEDs sequentially based on the direction
  if (LeftDirection == 1) {
    // Forward direction for turning off
    for (int i = 0; i < BlinkerLEDs; i++) {
      leds_L->setPixelColor(i, 0);  // Turn off the LED
      leds_L->show();
      delay(BlinkerSpeed);  // Adjust this delay to control the speed of turning off
    }
  } else if (LeftDirection == 2) {
    // Reverse direction for turning off
    for (int i = BlinkerLEDs - 1; i >= 0; i--) {
      leds_L->setPixelColor(i, 0);  // Turn off the LED
      leds_L->show();
      delay(BlinkerSpeed);  // Adjust this delay to control the speed of turning off
    }
  }

  // Clear LEDs at the end of the animation
  leds_L->clear();
  leds_L->show();
}

/*____________________________________ LEFT DIM _________________________________________*/
void LeftDim() {
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_L->setPixelColor(i, DRLColor);
  }
  leds_L->show();
}

/*_____________________________________ LEFT DIM _______________________________________*/
void LeftDimOff() {
  for (int i = 0; i < NUM_LEDS_L; i++) {
     // Set the color to  black)
    leds_L->setPixelColor(i, leds_L->Color(0, 0, 0,0));  // RGB values set to 0
  }
  leds_L->show();  // Show the updated state of the LEDs
}

/*__________________________________ LEFT LIT __________________________________________*/
void LeftLit() {
  leds_L->fill(leftColor);
  leds_L->show();
}

/*___________________________________ LEFT FULL _________________________________________*/
void LeftFull() {

  for (int i = 0; i < NUM_LEDS_L; i++) {
    leds_L->setPixelColor(i, DRLColor);
  }
  leds_L->show();
}



//CAR START ANIMATIONS//
void ParkFadeIn() {
  if (!parkOnExecuted) {
    const int fadeSteps = 255;                       // Number of steps in the fade-in effect
    const int fadeDelay = StartupSpeed / fadeSteps;  // Delay between fade steps

    // Extract RGB components from DRLColor
    const uint8_t red = 255;
    const uint8_t green = 255;
    const uint8_t blue = 255;

    // Fade in all LEDs gradually
    for (int brightness = 0; brightness <= fadeSteps; brightness++) {
      // Scale each color channel based on brightness
      uint32_t scaledColor = leds_L->Color(
        red * brightness / fadeSteps,
        green * brightness / fadeSteps,
        blue * brightness / fadeSteps);

      for (int j = 0; j < NUM_LEDS_L; j++) {
        leds_L->setPixelColor(j, scaledColor);
        leds_R->setPixelColor(NUM_LEDS_R - j - 1, scaledColor);  // Mirror for leds_R
      }
      leds_L->show();
      leds_R->show();
      delay(fadeDelay);
    }

    // Set the flag to indicate that ParkFadeIn() has been executed
    parkOnExecuted = true;
  }
}

void ParkFadeOut() {
  if (!parkOffExecuted) {
    const int fadeSteps = 255;                       // Number of steps in the fade-out effect
    const int fadeDelay = StartupSpeed / fadeSteps;  // Delay between fade steps

    // Extract RGB components from DRLColor
    const uint8_t red = 255;
    const uint8_t green = 255;
    const uint8_t blue = 255;

    // Fade out all LEDs gradually
    for (int brightness = fadeSteps; brightness >= 0; brightness--) {
      // Scale each color channel based on brightness
      uint32_t scaledColor = leds_L->Color(
        red * brightness / fadeSteps,
        green * brightness / fadeSteps,
        blue * brightness / fadeSteps);

      for (int j = 0; j < NUM_LEDS_L; j++) {
        leds_L->setPixelColor(j, scaledColor);
        leds_R->setPixelColor(NUM_LEDS_R - j - 1, scaledColor);  // Mirror for leds_R
      }
      leds_L->show();
      leds_R->show();
      delay(fadeDelay);
    }

    // Ensure all LEDs are fully off after the fade-out
    for (int j = 0; j < NUM_LEDS_L; j++) {
      leds_L->setPixelColor(j, 0);
      leds_R->setPixelColor(NUM_LEDS_R - j - 1, 0);
    }
    leds_L->show();
    leds_R->show();

    // Set the flag to indicate that ParkFadeOut() has been executed
    parkOffExecuted = true;
  }
}

void CarStartAnimation() {
  if (StartAnimation == 1) {
    BlinkStartON();
  } else if (StartAnimation == 2) {
    SequentialStartON();
  } else if (StartAnimation == 3) {
    StackStartON(false, false, 1);
  } else {
    ParkFadeIn();
  }
}

void CarOffAnimation() {
  if (StartAnimation == 1) {
    BlinkStartOFF();
  } else if (StartAnimation == 2) {
    SequentialStartOFF();
  } else if (StartAnimation == 3) {
    StackStartOFF(false, false, 1);
  } else {
    ParkFadeOut();
  }
}


void BlinkStartON() {
  if (!parkOnExecuted) {
    // Blink LEDs (on/off) a few times before transitioning to solid
    for (int blink = 0; blink < 3; blink++) {  // Adjust the number of blinks as needed
      // Turn on all LEDs
      for (int j = NUM_LEDS_L - 1; j >= 0; j--) {
        leds_L->setPixelColor(j, DRLColor);
        leds_R->setPixelColor(NUM_LEDS_R - j - 1, DRLColor);  // Mirror position for leds_R
      }
      leds_L->show();
      leds_R->show();
      delay(100);

      // Turn off all LEDs
      for (int j = NUM_LEDS_L - 1; j >= 0; j--) {
        leds_L->setPixelColor(j, 0);
        leds_R->setPixelColor(NUM_LEDS_R - j - 1, 0);  // Mirror position for leds_R
      }
      leds_L->show();
      leds_R->show();
      delay(100);
    }

    // Transition to solid light
    for (int j = NUM_LEDS_L - 1; j >= 0; j--) {
      leds_L->setPixelColor(j, DRLColor);
      leds_R->setPixelColor(NUM_LEDS_R - j - 1, DRLColor);  // Mirror position for leds_R
    }
    leds_L->show();
    leds_R->show();

    // Set the flag to indicate that ParkON() has been executed
    parkOnExecuted = true;
  }
}


void BlinkStartOFF() {
  if (!parkOffExecuted) {
    // Blink LEDs (on/off) a few times before turning them off
    for (int blink = 0; blink < 3; blink++) {  // Adjust the number of blinks as needed
      // Turn on all LEDs
      for (int j = NUM_LEDS_L - 1; j >= 0; j--) {
        leds_L->setPixelColor(j, DRLColor);
        leds_R->setPixelColor(NUM_LEDS_R - j - 1, DRLColor);  // Mirror position for leds_R
      }
      leds_L->show();
      leds_R->show();
      delay(100);

      // Turn off all LEDs
      for (int j = NUM_LEDS_L - 1; j >= 0; j--) {
        leds_L->setPixelColor(j, 0);
        leds_R->setPixelColor(NUM_LEDS_R - j - 1, 0);  // Mirror position for leds_R
      }
      leds_L->show();
      leds_R->show();
      delay(100);
    }

    // Ensure all LEDs are off after the blinking phase
    for (int j = NUM_LEDS_L - 1; j >= 0; j--) {
      leds_L->setPixelColor(j, 0);
      leds_R->setPixelColor(NUM_LEDS_R - j - 1, 0);  // Mirror position for leds_R
    }
    leds_L->show();
    leds_R->show();

    // Set the flag to indicate that ParkOFF() has been executed
    parkOffExecuted = true;
  }
}

/*________________________________ PARK ON _____________________________*/

void SequentialStartON() {
  if (!parkOnExecuted) {
    // First loop
    for (int j = NUM_LEDS_L - 1; j >= 0; j--) {
      leds_L->setPixelColor(j, DRLColor);
      leds_R->setPixelColor(NUM_LEDS_R - j - 1, DRLColor);  // Mirror position for leds_R
      leds_L->show();
      leds_R->show();
      delay(100);
    }

    // Second loop - turn off LEDs sequentially
    for (int i = 0; i < NUM_LEDS_L; i++) {
      leds_L->setPixelColor(i, 0);                   // Turn off LED on the left side
      leds_R->setPixelColor(NUM_LEDS_R - i - 1, 0);  // Turn off LED on the right side
      leds_L->show();
      leds_R->show();
      delay(100);
    }

    // Ensure all LEDs are off after the second loop
    leds_L->show();
    leds_R->show();

    // Third loop
    for (int j = NUM_LEDS_L - 1; j >= 0; j--) {
      leds_L->setPixelColor(j, DRLColor);
      leds_R->setPixelColor(NUM_LEDS_R - j - 1, DRLColor);  // Mirror position for leds_R
      leds_L->show();
      leds_R->show();
      delay(100);
    }

    // Set the flag to indicate that ParkON() has been executed
    parkOnExecuted = true;
  }
}



/*_______________________________ PARK OFF ___________________________________*/

void SequentialStartOFF() {
  if (!parkOffExecuted) {
    // First loop - turn on LEDs sequentially in the opposite direction
    for (int j = 0; j < NUM_LEDS_L; j++) {
      leds_L->setPixelColor(NUM_LEDS_L - j - 1, DRLColor);  // Opposite direction for leds_L
      leds_R->setPixelColor(j, DRLColor);                   // Opposite direction for leds_R
      leds_L->show();
      leds_R->show();
      delay(StartupSpeed);
    }

    // Second loop - turn off LEDs from the beginning to the end
    for (int i = NUM_LEDS_L - 1; i >= 0; i--) {
      leds_L->setPixelColor(NUM_LEDS_L - i - 1, 0);  // Opposite direction for leds_L
      leds_R->setPixelColor(i, 0);                   // Opposite direction for leds_R
      leds_L->show();
      leds_R->show();
      delay(StartupSpeed);
    }

    // Ensure all LEDs are off after the second loop
    leds_L->show();
    leds_R->show();

    // Third loop - turn off LEDs sequentially from the end to the beginning
    for (int j = 0; j < NUM_LEDS_L; j++) {
      leds_L->setPixelColor(NUM_LEDS_L - j - 1, 0);  // Opposite direction for leds_L
      leds_R->setPixelColor(j, 0);                   // Opposite direction for leds_R
      leds_L->show();
      leds_R->show();
      delay(StartupSpeed);
    }

    // Set the flag to indicate that ParkOFF() has been executed
    parkOffExecuted = true;
  }
}


void StackStartON(bool reverse_L, bool reverse_R, int animationSpeed) {
  int numPixels_L = leds_L->numPixels();
  int numPixels_R = leds_R->numPixels();

  int currentPosition_L = 0;
  int currentPosition_R = 0;

  int numLitLEDs_L = 0;
  int numLitLEDs_R = 0;

  // Variable to track the last update time
  unsigned long lastUpdateTime = 0;

  // Ensure the function only runs the animation once
  if (!parkOnExecuted) {
    // Animation loop for the left and right strips
    while (numLitLEDs_L < numPixels_L || numLitLEDs_R < numPixels_R) {
      // Check if the desired delay has passed
      if (millis() - lastUpdateTime >= animationSpeed) {
        // Update the last update time
        lastUpdateTime = millis();

        // Left Strip Animation
        for (int i = 0; i < numPixels_L; i++) {
          if (i <= numLitLEDs_L) {
            leds_L->setPixelColor(i, DRLColor);  // Keep previous LEDs lit (white color)
          } else {
            leds_L->setPixelColor(i, 0);  // Turn off the rest of the LEDs
          }
        }
        int actualPosition_L = reverse_L ? numPixels_L - 1 - currentPosition_L : currentPosition_L;
        if (actualPosition_L < numPixels_L) {
          leds_L->setPixelColor(actualPosition_L, DRLColor);  // Moving LED
        }
        leds_L->show();

        currentPosition_L++;
        if (currentPosition_L >= numPixels_L) {
          currentPosition_L = 0;
          if (numLitLEDs_L < numPixels_L - 1) {
            numLitLEDs_L++;
          } else {
            numLitLEDs_L = numPixels_L;  // Stop incrementing when all LEDs are lit
          }
        }

        // Right Strip Animation
        for (int i = 0; i < numPixels_R; i++) {
          if (i <= numLitLEDs_R) {
            leds_R->setPixelColor(i, DRLColor);  // Keep previous LEDs lit (white color)
          } else {
            leds_R->setPixelColor(i, 0);  // Turn off the rest of the LEDs
          }
        }
        int actualPosition_R = reverse_R ? numPixels_R - 1 - currentPosition_R : currentPosition_R;
        if (actualPosition_R < numPixels_R) {
          leds_R->setPixelColor(actualPosition_R, DRLColor);  // Moving LED
        }
        leds_R->show();

        currentPosition_R++;
        if (currentPosition_R >= numPixels_R) {
          currentPosition_R = 0;
          if (numLitLEDs_R < numPixels_R - 1) {
            numLitLEDs_R++;
          } else {
            numLitLEDs_R = numPixels_R;  // Stop incrementing when all LEDs are lit
          }
        }
      }
    }

    // After animation completes, keep all LEDs solidly lit
    for (int i = 0; i < numPixels_L; i++) {
      leds_L->setPixelColor(i, DRLColor);  // Set all LEDs to solid white
    }
    leds_L->show();

    for (int i = 0; i < numPixels_R; i++) {
      leds_R->setPixelColor(i, DRLColor);  // Set all LEDs to solid white
    }
    leds_R->show();

    // Mark parkOffExecuted as true to indicate the animation has completed
    parkOnExecuted = true;
  }
}


void StackStartOFF(bool reverse_L, bool reverse_R, int animationSpeed) {
  int numPixels_L = leds_L->numPixels();
  int numPixels_R = leds_R->numPixels();

  int currentPosition_L = numPixels_L - 1;  // Start at the last LED
  int currentPosition_R = numPixels_R - 1;
  int numLitLEDs_L = numPixels_L;  // All LEDs lit initially
  int numLitLEDs_R = numPixels_R;

  // Variable to track the last update time
  unsigned long lastUpdateTime = 0;

  // Ensure the function only runs the animation once
  if (!parkOffExecuted) {
    // Animation loop for the left and right strips
    while (numLitLEDs_L > 0 || numLitLEDs_R > 0) {
      // Check if the desired delay has passed
      if (millis() - lastUpdateTime >= animationSpeed) {
        // Update the last update time
        lastUpdateTime = millis();

        // Left Strip Animation
        for (int i = 0; i < numPixels_L; i++) {
          if (i < numLitLEDs_L) {
            leds_L->setPixelColor(i, DRLColor);  // Keep remaining LEDs lit (white color)
          } else {
            leds_L->setPixelColor(i, 0);  // Turn off LEDs that are unwound
          }
        }
        int actualPosition_L = reverse_L ? numPixels_L - 1 - currentPosition_L : currentPosition_L;
        if (actualPosition_L >= 0) {
          leds_L->setPixelColor(actualPosition_L, DRLColor);  // Current LED turning off
        }
        leds_L->show();

        currentPosition_L--;
        if (currentPosition_L < 0) {
          currentPosition_L = numPixels_L - 1;
          if (numLitLEDs_L > 0) {
            numLitLEDs_L--;
          }
        }

        // Right Strip Animation
        for (int i = 0; i < numPixels_R; i++) {
          if (i < numLitLEDs_R) {
            leds_R->setPixelColor(i, DRLColor);  // Keep remaining LEDs lit (white color)
          } else {
            leds_R->setPixelColor(i, 0);  // Turn off LEDs that are unwound
          }
        }
        int actualPosition_R = reverse_R ? numPixels_R - 1 - currentPosition_R : currentPosition_R;
        if (actualPosition_R >= 0) {
          leds_R->setPixelColor(actualPosition_R, DRLColor);  // Current LED turning off
        }
        leds_R->show();

        currentPosition_R--;
        if (currentPosition_R < 0) {
          currentPosition_R = numPixels_R - 1;
          if (numLitLEDs_R > 0) {
            numLitLEDs_R--;
          }
        }
      }
    }

    // After animation completes, ensure all LEDs are off
    for (int i = 0; i < numPixels_L; i++) {
      leds_L->setPixelColor(i, 0);  // Turn off all LEDs
    }
    leds_L->show();

    for (int i = 0; i < numPixels_R; i++) {
      leds_R->setPixelColor(i, 0);  // Turn off all LEDs
    }
    leds_R->show();

    // Mark parkOffExecuted as true to indicate the animation has completed
    parkOffExecuted = true;
  }
}

/*________________________________ PARK ON _____________________________*/
//bool parkOnExecuted = false;

void ParkON() {
  if (parkOnExecuted) return;

  // Helper lambda to update and show LEDs
  auto updateLEDs = [&](int leftIndex, int rightIndex, uint32_t color) {
    leds_L->setPixelColor(leftIndex, color);
    leds_R->setPixelColor(rightIndex, color);
    leds_L->show();
    leds_R->show();
  };

  // First loop - turn on LEDs sequentially
  for (int i = NUM_LEDS_L - 1; i >= 0; i--) {
    updateLEDs(i, NUM_LEDS_R - i - 1, DRLColor);
    delay(StartupSpeed);
  }

  // Second loop - turn off LEDs sequentially
  for (int i = 0; i < NUM_LEDS_L; i++) {
    updateLEDs(i, NUM_LEDS_R - i - 1, 0);
    delay(StartupSpeed);
  }

  // Third loop - turn on LEDs sequentially again
  for (int i = NUM_LEDS_L - 1; i >= 0; i--) {
    updateLEDs(i, NUM_LEDS_R - i - 1, DRLColor);
    delay(StartupSpeed);
  }

  // Set the flag to indicate ParkON()  execution
  parkOnExecuted = true;
}


/*_______________________________ PARK OFF ___________________________________*/
//bool parkOffExecuted = false;
void ParkOFF() {
  if (parkOffExecuted) return;

  // Helper lambda to update and show LEDs
  auto updateLEDs = [&](int leftIndex, int rightIndex, uint32_t color) {
    leds_L->setPixelColor(leftIndex, color);
    leds_R->setPixelColor(rightIndex, color);
    leds_L->show();
    leds_R->show();
  };

  // First loop - turn on LEDs sequentially in the opposite direction
  for (int i = 0; i < NUM_LEDS_L; i++) {
    updateLEDs(NUM_LEDS_L - i - 1, i, DRLColor);
    delay(StartupSpeed);
  }

  // Second loop - turn off LEDs from the beginning to the end
  for (int i = NUM_LEDS_L - 1; i >= 0; i--) {
    updateLEDs(NUM_LEDS_L - i - 1, i, 0);
    delay(StartupSpeed);
  }

  // Third loop - turn off LEDs sequentially from the end to the beginning
  for (int i = 0; i < NUM_LEDS_L; i++) {
    updateLEDs(NUM_LEDS_L - i - 1, i, 0);
    delay(StartupSpeed);
  }

  // Set the flag to indicate execution
  parkOffExecuted = true;
}
