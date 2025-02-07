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
  // Read all input signals once
  int leftSignal = digitalRead(LeftSignal);
  int rightSignal = digitalRead(RightSignal);
  int brakeSignal = digitalRead(BrakeSignal);
  int parkSignal = digitalRead(ParkSignal);
  int drlSignal = digitalRead(DRLsignal);
  int reverseSignal = digitalRead(ReverseSignal);
  int extraLeds = digitalRead(Extraleds);


  // Handle reverse signal logic
  if (reverseSignal == 1) {
    effectState = 0;
    if (brakeSignal == 0) {  // Reverse Light
      Reverse();
    } else {
      BrakeFull();  //Braking while reversing
    }
    return;
  }



  // Park detection logic
  switch (ParkDetect) {
    case 0:
      if (parkSignal == 0) {
        ParkDetect = 1;
      }
      break;

    case 1:
      ParkON();
      ParkDetect = 2;
      break;

    case 2:
      if (parkSignal == 1) {
        ParkDetect = 3;
      }
      break;

    case 3:
      ParkOFF();
      ParkDetect = 0;
      break;
  }


  // Lighting logic
  if (parkSignal == 0) {
    strobePerformed = 0;

    if (reverseSignal == 0) {


      if (brakeSignal == 0 && leftSignal == 0 && rightSignal == 0 && drlSignal == 0) {
        if (effectState == 0) {
          AllOff();
          effectState = 1;
        } else {
          //playEffects();
        }
        return;
      }

      // if (extraLeds == 0) {
      //   DRLLeftLit();
      //   effectState = 0;
      //   return;
      // }

      if (rightSignal  && !leftSignal && !brakeSignal ) {
        if (drlSignal == 1) {
          DRLLeftFull();
          RightDimOff();
        }
        RightBlinker();
        effectState = 0;
        return;
      }

      if (leftSignal  && !rightSignal  && !brakeSignal ) {
        if (drlSignal == 1) {
          DRLRighttFull();
          LeftDimOff();
        }
        LeftBlinker();
        effectState = 0;
        return;
      }

      if (drlSignal  && !leftSignal && !rightSignal) {
        DRLLeftFull();
        DRLRighttFull();
        effectState = 0;
        return;
      }

      if (brakeSignal  && !leftSignal && !rightSignal  && !drlSignal ) {
        BrakeFull();
        effectState = 0;
        return;
      }

      if (rightSignal  && !leftSignal && brakeSignal ) {
        RightBlinker();
        BrakeFull();
        effectState = 0;
        strobePerformed = 0;
        return;
      }

      if (leftSignal && !rightSignal && brakeSignal ) {
        LeftBlinker();
        BrakeFull();
        effectState = 0;
        strobePerformed = 0;
        return;
      }

      if (leftSignal  && rightSignal && !brakeSignal ) {
        DualBlinker();
        effectState = 0;
        strobePerformed = 0;
        return;
      }

      if (leftSignal  && rightSignal  && brakeSignal ) {
        DualBlinker();
        BrakeFull();
        effectState = 0;
        return;
      }
    }
  }
}
