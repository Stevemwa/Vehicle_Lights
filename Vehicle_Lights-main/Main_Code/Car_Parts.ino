
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






/*________________________________ PARK ON _____________________________*/
bool parkOnExecuted = false;

void ParkON() {
  if (!parkOnExecuted) {
    // First loop
    for (int j = NUM_LEDS_L - 1; j >= 0; j--) {
      leds_L->setPixelColor(j, DRLColor);
      leds_R->setPixelColor(NUM_LEDS_R - j - 1, DRLColor);  // Mirror position for leds_R
      leds_L->show();
      leds_R->show();
      delay(StartupSpeed);
    }

    // Second loop - turn off LEDs sequentially
    for (int i = 0; i < NUM_LEDS_L; i++) {
      leds_L->setPixelColor(i, 0);                   // Turn off LED on the left side
      leds_R->setPixelColor(NUM_LEDS_R - i - 1, 0);  // Turn off LED on the right side
      leds_L->show();
      leds_R->show();
      delay(StartupSpeed);
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
      delay(StartupSpeed);
    }

    // Set the flag to indicate that ParkON() has been executed
    parkOnExecuted = true;
  }
}



/*_______________________________ PARK OFF ___________________________________*/
bool parkOffExecuted = false;

void ParkOFF() {
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

// =============================================== LEFT LEDS FUNCTIONS ==================================================================

/*___________________________________LEFT LEDS OFF ____________________________________*/
void LeftOff() {
  leds_L->clear();
  leds_L->show();
}


/*_____________________________ LEFT STARTUP ANIMATION __________________________________*/
void leftStartupAnimation() {
  for (int i = NUM_LEDS_L - 1; i >= 0; i--) {
    leds_L->setPixelColor(i, thrdColor);  // Use the pre-made color
    leds_L->show();
    delay(50);
  }
  delay(500);  // Pause at the end of the animation
  leds_L->clear();
  leds_L->show();  // Turn off all pixels
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
    leds_L->setPixelColor(i, 0x000000);  // Set the color to 0x000000 (hex for black)
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



//======================================== RIGHT SIDE LEDS CONTROL ============================================================================

/*______________________________ RIGHT STARTUP ANIMATION _____________________________*/
void rightStartupAnimation() {
  for (int i = 0; i < NUM_LEDS_R; i++) {
    leds_R->setPixelColor(i, thrdColor);  // Use the pre-made color
    leds_R->show();
    delay(50);
  }
  delay(500);  // Pause at the end of the animation
  leds_R->clear();
  leds_R->show();  // Turn off all pixels
}

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
    leds_R->setPixelColor(i, 0x000000);  // Set the color to 0x000000 (hex for black)
  }
  leds_R->show();  // Show the updated state of the LEDs
}

/*_____________________________ RIGHT LIT _______________________________________________*/
void RightLit() {

  leds_R->fill(RightColor);
  leds_R->show();
}

/*____________________________ RIGHT ORIGINAL ____________________________________________*/
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

/*__________________________ RIGHT SEQUENCIAL ___________________________________________*/
void RightSequential() {
  leds_R->clear();
  leds_R->show();
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, RightColor);
    delay(BlinkerSpeed);
    leds_R->show();
  }
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
void RightSequentialSolid() {
  leds_R->clear();
  leds_R->show();
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, RightColor);
  }
  leds_R->show();
  delay(1000);  // Adjust this delay to determine how long the tail lights stay on

  // Sequentially turn off the tail lights
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, leds_R->Color(0, 0, 0));
    leds_R->show();
    delay(BlinkerSpeed);  // Adjust this delay to control the speed of turning off
  }
}

/*_________________________________________ RIGHT FULL __________________________________________________*/
void RightFull() {

  leds_R->fill(DRLColor);
  leds_R->show();
}





//============================================== DRL LEDS CONTROL =========================================

/*________________________________________ DRL LEFT FULL ________________________________________*/
void DRLLeftFull() {
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_L->setPixelColor(i, DRLColor);  // Set the color for DRL
  }
  leds_L->show();
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
void DRLRightFull() {
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_R->setPixelColor(i, DRLColor);  // Set the color for DRL
  }
  leds_R->show();
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
void DRLFull() {
  leds_3->fill(thrdColor);
}




//====================================================== BLINKER LEDS CONTROL ================================================================================

/*________________________________________________ DUAL BLINKER ______________________________________________*/
void DualBlinker() {
  if (LeftSignal == 1 && RightSignal == 1) {
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
}
/*void DualBlinker()
{
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
*/


/*_____________________________________________ BLINKER EXECUTED _____________________________________________________*/
bool blinkerExecuted = false;
bool leftBlinkerActive = false ;
bool rightBlinkerActive = false;
void BlinkerControl() {
  if (!blinkerExecuted) {
    // If left blinker is active
    if (leftBlinkerActive) {
      // Turn off DRLLeftFull and DRLRightFull
      for (int i = 0; i < NUM_LEDS_L; i++) {
        leds_L->setPixelColor(i, 0);         // Turn off LED on the left side
        leds_R->setPixelColor(i, DRLColor);  // Turn off LED on the right side
      }
      leds_L->show();
      leds_R->show();

      // Call LeftBlinker function to handle left blinker logic
      LeftBlinker();

    } else if (rightBlinkerActive) {
      // Turn off DRLLeftFull and DRLRightFull
      for (int i = 0; i < NUM_LEDS_L; i++) {
        leds_L->setPixelColor(i, DRLColor);  // Turn off LED on the left side
        leds_R->setPixelColor(i, 0);         // Turn off LED on the right side
      }
      leds_L->show();
      leds_R->show();

      // Call RightBlinker function to handle right blinker logic
      RightBlinker();

    } else {
      // No blinker active, set LEDs to white
      for (int i = 0; i < NUM_LEDS_L; i++) {
        leds_L->setPixelColor(i, DRLColor);  // Set LED on the left side to white
        leds_R->setPixelColor(i, DRLColor);  // Set LED on the right side to white
      }
      leds_L->show();
      leds_R->show();
    }

    // Set the flag to indicate that BlinkerControl() has been executed
    blinkerExecuted = true;
  }
}

/*_________________________________LEFT BLINKER __________________________________________*/
bool leftBlinkerExecuted = false;
void LeftBlinker() {
  leftBlinkerExecuted = true;

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

/*_________________________________ RIGHT BLINKER __________________________________________*/
void RightBlinker() {
  leds_R->clear();
  leds_R->show();
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
/*void RightBlinker()
{
    // Your provided Right Blinker logic
    if (BlinkerAnimation == 1) {
      RightHeartBeat();
    } else if (BlinkerAnimation == 2) {
      RightSequential();
    } else if (BlinkerAnimation == 3) {
      RightOriginal();
    } else {
      RightSequentialSolid();
    }
}*/
/*_________________________________________________ RESET BLINKER CONTROL __________________________________________*/
// Reset the blinkerExecuted flag whenever needed
void ResetBlinkerControl() {
  blinkerExecuted = false;
}


// ============================================================ DUAL LED CONTROL =========================================================================

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







// --------------------------------------------------------------------------------------------------------------------------------------------------
/*________________________________________________ FADE ALL _______________________________________________________*/
void fadeall() {
  leds_3->clear();
  leds_3->show();
  leds_L->clear();
  leds_L->show();
  leds_R->clear();
  leds_R->show();
}


/*_____________________________________SET WHITE LEDS ____________________________________*/
void SetWhiteLEDs() {
  for (int i = 0; i < NUM_LEDS_L; i++) {
    leds_L->setPixelColor(i, DRLColor);
  }
  for (int i = 0; i < NUM_LEDS_R; i++) {
    leds_R->setPixelColor(i, DRLColor);
  }
  leds_L->show();
  leds_R->show();
}



/*__________________________________ HEART BEAT EFFECT ____________________________________*/
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


/*________________________________________ ORIGINAL ________________________________________*/
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

/*_____________________________________ ORIGINAL 2 ___________________________________________*/
void Original2() {
  for (int i = 0; i < BlinkerLEDs; i++) {
    uint32_t currentColor = leds_L->getPixelColor(i);
    // Extract the white component from DRLColor
    uint8_t whiteComponent = (DRLColor >> 24) & 0xFF;

    // Extract the RGB components from leftColor
    uint8_t r = (leftColor >> 16) & 0xFF;
    uint8_t g = (leftColor >> 8) & 0xFF;
    uint8_t b = leftColor & 0xFF;

    // Combine the RGB components from leftColor with the white component from DRLColor
    uint32_t combinedColor = leds_L->Color(r, g, b, whiteComponent);

    // Set the pixel color, preserving the white component
    leds_L->setPixelColor(i, combinedColor);
  }
  leds_L->show();
  delay(BlinkerSpeed);
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_L->setPixelColor(i, leds_L->Color(0, 0, 0));
  }
  leds_L->show();
  delay(BlinkerSpeed);
}

/*______________________________________SEQUENTIAL LEFT LEDS _________________________________*/
void Sequential() {
  for (int i = BlinkerLEDs - 1; i >= 0; i--) {
    leds_L->setPixelColor(i, leftColor);
    delay(BlinkerSpeed);
    leds_L->show();
  }
}


/*________________________________________ SOLID SEQUENTIAL __________________________________*/
void SolidSequential() {
  for (int i = 0; i < BlinkerLEDs; i++) {
    leds_L->setPixelColor(i, leftColor);  // Set RGB color
  }
  leds_L->show();
  delay(1000);  // Adjust this delay to determine how long the tail lights stay on

  // Sequentially turn off the RGB LEDs
  for (int i = BlinkerLEDs - 1; i >= 0; i--) {
    leds_L->setPixelColor(i, 0);  // Turn off the LED
    leds_L->show();
    delay(BlinkerSpeed);  // Adjust this delay to control the speed of turning off
  }
}



/*_________________________________________TURN OFF LEDS __________________________________________*/
uint32_t offColor = leds_L->Color(0, 0, 0);  // Define the off color (black)
void turnOffLEDs() {
  for (int i = 0; i < NUM_LEDS_L; i++) {
    leds_L->setPixelColor(i, offColor);  // Set color to 'off'
  }
  leds_L->show();  // Update the LED strip with the new color values
}

/*_____________________________________ TURN OFF LEDS RIGHT _______________________________________*/
void turnOffLEDsRight() {
  for (int i = 0; i < NUM_LEDS_R; i++) {
    leds_R->setPixelColor(i, 0);  // Set color to 'off'
  }
  leds_R->show();  // Update the LED strip with the new color values
}

