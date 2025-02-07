/*
 SET EFFECTS FUNCTION IS USED TO SET THE VARIOUS LED ANIMATION EFFECTS FROM THE ANIMATIONS PAGE

*/

void setFavEffects(const uint8_t *arr, uint8_t count) {
  if (currentEffect > (count - 1)) {
    currentEffect = 0;
  }
  effect = arr[currentEffect++];
  lastChange = millis();
}


void setEffect(const uint8_t num) {
  if (strip_select == 3) {
    switch (num) {
      case 0:
        leds_L->fill(leftColor, 0, NUM_LEDS_L - 1);
        leds_R->fill(RightColor, 0, NUM_LEDS_R - 1);
        leds_3->fill(thrdColor, 0, NUM_LEDS_L - 1);
        break;
      case 1:
        WhiteoverRainbow(leds_L, 75, 5);
        WhiteoverRainbow(leds_R, 75, 5);
        WhiteoverRainbow(leds_3, 75, 5);
        break;
      case 2:
        RainbowLoop1(leds_L, 75, 5);
        RainbowLoop1(leds_R, 75, 5);
        RainbowLoop1(leds_3, 75, 5);
        break;
      case 3:
        RainbowLoop2(leds_L, 3, 1);
        RainbowLoop2(leds_R, 3, 1);
        RainbowLoop2(leds_3, 3, 1);
        delay(3);
        break;
      case 4:
        colorWipe(leds_L, leds_R);
        break;
      case 5:
        randomMarch(leds_L, leds_R);
        break;
      case 6:
        rgbpropeller(leds_L, leds_R);
        break;
      case 7:
        fire(leds_L, leds_R, 55, 120);
        break;
      case 8:
        fireEffect(leds_L,leds_R, 10, 50);
        break;
      case 9:
        randomBurst(leds_L, leds_R);
        break;
      case 10:
        flicker(leds_L, leds_R);
        break;
      case 11:
        randomColorPop(leds_L, leds_R);
        break;
      case 12:
        sparkle(leds_L, leds_R);
        break;
      case 13:
        rotatingRedBlue(leds_L);
        rotatingRedBlue(leds_R);
        break;
      case 14:
        snowSparkle(leds_L);
        snowSparkle(leds_R);
        break;
      case 15:
        rwbMarch(leds_L);
        rwbMarch(leds_R);
        break;
      case 16:
        theaterChaseRainbow(leds_L,leds_R);  // Red color chase
        break;
      case 17:
        strobe(leds_L, leds_R, 255, 255, 255, 10,100);
        break;
      case 18:
        policeBlinker(leds_L, leds_R);
        break;
      case 19:
        kitt(leds_L, leds_R, DRLColor, DRLColor);
        break;
      case 20:
        SwipeRandomAnimation(leds_L, leds_R);
        break;
      case 21:
        tetrisAnimation(leds_L, EffectSpeed, leftColor, RightColor);
        break;
      case 22:
        blende();
        break;
      case 23:
        blende_2(leds_L, leds_R);
        break;
      case 24:
        CenterToOutside(leds_L,leds_R, leftColor, NUM_LEDS_L / 4, 20);
        break;
      case 25:
        OutsideToCenter(leds_L,leds_R, leftColor, NUM_LEDS_L / 2, 1);
        break;
      case 26:
        LeftToRight(leds_L,leds_R, leftColor, NUM_LEDS_L / 2, 20);
        break;
      case 27:
        CandyCane(leds_L, leds_R, leftColor, RightColor, 2);
        break;
      case 28:
        dissolveRandom(leds_L,leds_R);
        break;
      case 29:
        solid(leds_L, leds_R, leftColor, RightColor);
        break;
      case 30:
        knightRider(3);
        break;
      case 31:
        Middle3Out(leds_L, leds_R,leftColor, RightColor);
        break;
      case 32:
        Middle4OutStacker(leds_L,leds_R, leftColor);
        break;
      case 33:
        breatheAnimation(leds_L, leds_R, leds_3, leftColor, RightColor, thrdColor);
        break;
      case 34:
        colorBounce(leds_L,leds_R, leftColor, 10);
        break;
      case 35:
        colorBounceRain(leds_L, leds_R,10);
        break;
      case 36:
        Scanner(leds_L, leds_R, leds_3, leftColor, RightColor, thrdColor);
        break;
      case 37:
       stackingAnimationReverseddelay(EffectSpeed, true, true);
        break;
      case 38:
        breatheAnimationRandom(leds_L,leds_R,leds_3,leftColor, RightColor,thrdColor);
        break;
      case 39:
  stackingAnimationSolidRandomColor(leds_L, leds_R, EffectSpeed, true, true);  // Left strip forwards, right strip backwards
        break;
    }
  }
}
