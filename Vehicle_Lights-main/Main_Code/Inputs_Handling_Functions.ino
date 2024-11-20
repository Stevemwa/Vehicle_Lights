/*THIS CODE HANDLES THE INPUTS FROM THE CAR , CALLING THE OUT THE RESPECTFUL FUNCTIONS


                               void SETUP() INPUT PINS INITIALIZATION FUNCTION

                            void LOOP()  CAR INPUT HANDLING TO CALL RELEVANT CAR _PARTS FUNCTIONS
                            
*/


void Initialize_Inputs() {
  pinMode(Extraleds, INPUT);
  pinMode(ParkSignal, INPUT);
  pinMode(BrakeSignal, INPUT);
  pinMode(LeftSignal, INPUT);
  pinMode(RightSignal, INPUT);
  pinMode(ReverseSignal, INPUT);
  pinMode(DRLsignal, INPUT);
}




void Handle_Inputs() {
  if (digitalRead(ReverseSignal) == 1) {
    effectState = 0;
    if (digitalRead(BrakeSignal) == 0)  // Reverse Light
    {
      Reverse();
    }

    if (digitalRead(BrakeSignal) == 1)  // Brake Light
    {
      BrakeFull();
    }
  }

  if (ParkDetect == 0) {
    if (digitalRead(ParkSignal) == 0) {
      ParkDetect = 1;
    }
  }

  if (ParkDetect == 2) {
    if (digitalRead(ParkSignal) == 1) {
      ParkDetect = 3;
    }
  }

  if (ParkDetect == 1) {
    ParkON();
    ParkDetect = 2;
  }

  if (ParkDetect == 3) {
    ParkOFF();
    ParkDetect = 0;
  }

  if (digitalRead(ParkSignal) == 0) {
    strobePerformed = 0;
    if (digitalRead(ReverseSignal) == 0) {
      if ((digitalRead(BrakeSignal) == 0) && (digitalRead(LeftSignal) == 0) && (digitalRead(RightSignal) == 0) && (digitalRead(DRLsignal) == 0))  // Brake Light
      {
        if (effectState == 0) {
          AllOff();
          effectState = 1;
        } else
          playEffects();
        strobePerformed = 0;
      }

      if ((digitalRead(Extraleds) == 0))  // extraLed on
      {
        DRLLeftLit();
        effectState == 0;
      }

      if (digitalRead(RightSignal) == 1 && digitalRead(LeftSignal) == 0 && digitalRead(BrakeSignal) == 0) {  // Right Blinker
        if (digitalRead(DRLsignal) == 1) {                                                                   // With DRL
          DRLLeftFull();                                                                                     // Turn off DRL on the left side
          RightDimOff();                                                                                     // Turn off DRL on the right side
        }
        RightBlinker();
        effectState = 0;
      }

      if (digitalRead(LeftSignal) == 1 && digitalRead(RightSignal) == 0 && digitalRead(BrakeSignal) == 0) {  // Left Blinker
        if (digitalRead(DRLsignal) == 1) {                                                                   // With DRL
          DRLRightFull();                                                                                    // Turn off DRL on the right side
          LeftDimOff();                                                                                      // Turn off DRL on the left side
        }
        LeftBlinker();
        effectState = 0;
      }

      if (digitalRead(DRLsignal) == 1 && digitalRead(LeftSignal) == 0 && digitalRead(RightSignal) == 0) {  // DRL Light when no turn signals are active
        DRLLeftFull();
        DRLRightFull();
        effectState = 0;
      }

      if ((digitalRead(BrakeSignal) == 1) && (digitalRead(LeftSignal) == 0) && (digitalRead(RightSignal) == 0) && (digitalRead(DRLsignal) == 0))  // Brake Light
      {
        BrakeFull();
        effectState == 0;
      }




      if ((digitalRead(RightSignal) == 1) && (digitalRead(LeftSignal) == 0) && (digitalRead(BrakeSignal) == 1))  // Right Blinker & Brake
      {
        RightBlinker();
        BrakeFull();
        effectState == 0;
        strobePerformed = 0;
      }
      if ((digitalRead(RightSignal) == 1) && (digitalRead(LeftSignal) == 0) && (digitalRead(BrakeSignal) == 1))  // Right Blinker & Brake
      {
        LeftBlinker();
        BrakeFull();
        effectState == 0;
        strobePerformed = 0;
      }

      if ((digitalRead(LeftSignal) == 1) && (digitalRead(RightSignal) == 1) && (digitalRead(BrakeSignal) == 0))  // Dual Blinker / Hazard
      {
        DualBlinker();
        effectState == 0;
        strobePerformed = 0;
      }

      if ((digitalRead(LeftSignal) == 1) && (digitalRead(RightSignal) == 1) && (digitalRead(BrakeSignal) == 1))  // Dual Blinker / Hazard + Brake
      {
        DualBlinker();
        BrakeFull();
        effectState == 0;
      }
    }

    if (ParkDetect == 2) {
      strobePerformed = 0;
      if (digitalRead(ReverseSignal) == 0) {
        if ((digitalRead(BrakeSignal) == 0) && (digitalRead(LeftSignal) == 0) && (digitalRead(RightSignal) == 0) && (digitalRead(DRLsignal) == 0))  // Brake Light
        {
          if (effectState == 0) {
            AllOff();
            effectState = 1;
          } else
            playEffects();
        }
        if ((digitalRead(Extraleds) == 0))  // Extra Light
        {
          DRLLeftLit();
          effectState == 0;
        }
        if ((digitalRead(BrakeSignal) == 1) && (digitalRead(LeftSignal) == 0) && (digitalRead(RightSignal) == 0) && (digitalRead(DRLsignal) == 0))  // Brake Light
        {
          BrakeFull();
          effectState == 0;
        }

        if (digitalRead(RightSignal) == 1 && digitalRead(LeftSignal) == 0 && digitalRead(BrakeSignal) == 0) {  // Right Blinker
          if (digitalRead(DRLsignal) == 1) {                                                                   // With DRL
            DRLLeftFull();                                                                                     // Turn off DRL on the left side
            RightDimOff();                                                                                     // Turn off DRL on the right side
          }
          RightBlinker();
          effectState = 0;
        }

        if (digitalRead(LeftSignal) == 1 && digitalRead(RightSignal) == 0 && digitalRead(BrakeSignal) == 0) {  // Left Blinker
          if (digitalRead(DRLsignal) == 1) {                                                                   // With DRL
            DRLRightFull();                                                                                    // Turn off DRL on the right side
            LeftDimOff();                                                                                      // Turn off DRL on the left side
          }
          LeftBlinker();
          effectState = 0;
        }

        if (digitalRead(DRLsignal) == 1 && digitalRead(LeftSignal) == 0 && digitalRead(RightSignal) == 0) {  // DRL Light when no turn signals are active
          DRLLeftFull();
          DRLRightFull();
          effectState = 0;
        }

        if ((digitalRead(LeftSignal) == 1) && (digitalRead(RightSignal) == 1) && (digitalRead(BrakeSignal) == 0))  // Dual Blinker / Hazard
        {
        }

        if ((digitalRead(LeftSignal) == 1) && (digitalRead(RightSignal) == 1) && (digitalRead(BrakeSignal) == 1))  // Dual Blinker / Hazard + Brake
        {
          effectState == 0;

          BrakeMiddle();
          delay(BlinkerOffDelay);
          if ((digitalRead(RightSignal) == 1) && (digitalRead(LeftSignal) == 0) && (digitalRead(DRLsignal) == 1))  // Right Blinker & DRL
          {
            delay(BlinkerOffDelay);
            effectState == 0;
          }
        }
      }
    }
  }
}