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
        colorWipe(leds_L, randomColor, 50);
        colorWipe(leds_R, randomColor, BlinkerSpeed);
        colorWipe(leds_3, randomColor, BlinkerSpeed);
        break;
      case 5:
        randomMarch(leds_L);
        randomMarch(leds_R);
        randomMarch(leds_3);
        _delay = 40;
        break;
      case 6:
        rgbpropeller(leds_L, BlinkerSpeed);
        rgbpropeller(leds_R, BlinkerSpeed);
        break;
      case 7:
        fire(leds_L, 55, 120, _delay);
        fire(leds_R, 55, 120, _delay);
        _delay = 15;
        break;
      case 8:
        blueFire(leds_L, 55, 250, _delay);
        blueFire(leds_R, 55, 250, _delay);
        _delay = 15;
        break;
      case 9:
        randomBurst(leds_L);
        randomBurst(leds_R);
        _delay = 20;
        break;
      case 10:
        flicker(leds_L);
        flicker(leds_R);
        _delay = 20;
        break;
      case 11:
        randomColorPop(leds_L);
        randomColorPop(leds_R);
        _delay = 35;
        break;
      case 12:
        sparkle(leds_L, 255, 255, 255, _delay);
        sparkle(leds_R, 255, 255, 255, _delay);
        _delay = 0;
        break;
      case 16:
        rotatingRedBlue(leds_L);
        rotatingRedBlue(leds_R);
        _delay = 40;
        hue = 0;
        break;
      case 20:
        snowSparkle(leds_L);
        snowSparkle(leds_R);
        _delay = 20;
        break;
      case 21:
        rwbMarch(leds_L);
        rwbMarch(leds_R);
        _delay = 80;
        break;
      case 23:
        theaterChase(leds_R, (RightColor >> 16) & 0xFF, (RightColor >> 8) & 0xFF, RightColor & 0xFF, _delay);
        _delay = BlinkerSpeed;
        theaterChase(leds_L, (leftColor >> 16) & 0xFF, (leftColor >> 8) & 0xFF, leftColor & 0xFF, _delay);
        _delay = BlinkerSpeed;
        break;
      case 24:
        strobe(leds_L, 255, 255, 255, 10, _delay, 100);
        strobe(leds_R, 255, 255, 255, 10, _delay, 100);
        _delay = 20;
        break;
      case 25:
        policeBlinker(leds_L);
        policeBlinker(leds_R);
        _delay = 25;
        break;
      case 26:
        kitt(leds_L, BlinkerSpeed, leftColor);
        kitt(leds_R, BlinkerSpeed, RightColor);
        break;
      case 27:
        SwipeRandomAnimation();
        break;
      case 28:
        tetrisAnimation(leds_L, BlinkerSpeed);
        break;
      case 29:
        blende();
        break;
      case 30:
        blende_2(leds_L, leftColor);
        blende_2(leds_R, RightColor);
        blende_2(leds_3, leftColor);
        break;

      case 31:
        CenterToOutside(leds_L, leftColor, NUM_LEDS_L / 3, 25, 20);
        CenterToOutside(leds_3, leftColor, NUM_LEDS_L / 3, 25, 20);
        CenterToOutside(leds_R, RightColor, NUM_LEDS_R / 3, 25, 20);
        break;
      case 32:
        OutsideToCenter(leds_L, leftColor, NUM_LEDS_L / 3, BlinkerSpeed, 1);
        OutsideToCenter(leds_3, leftColor, NUM_LEDS_3 / 3, BlinkerSpeed, 1);
        OutsideToCenter(leds_R, RightColor, NUM_LEDS_R / 3, BlinkerSpeed, 1);
        break;

      case 33:
        LeftToRight(leds_L, leftColor, NUM_LEDS_L / 3, 25, 20);
        LeftToRight(leds_3, leftColor, NUM_LEDS_3 / 1, 25, 20);
        LeftToRight(leds_R, RightColor, NUM_LEDS_R / 3, 25, 20);
        break;
      case 34:
        CandyCane(leds_L, leftColor, RightColor, BlinkerSpeed, 2);
        CandyCane(leds_R, leftColor, RightColor, BlinkerSpeed, 2);
        CandyCane(leds_3, leftColor, RightColor, BlinkerSpeed, 2);
        break;

      case 35:
        dissolveRandom(leds_L, BlinkerSpeed);
        dissolveRandom(leds_R, BlinkerSpeed);
        dissolveRandom(leds_3, BlinkerSpeed);
        break;
      case 36:
        solid();  // Run the rainbow runner animation with a fixed speed of 10
        break;

      case 38:
        knightRider(BlinkerSpeed, 5);
        break;
      case 39:
        Middle3Out(BlinkerSpeed);
        break;
      case 40:
        Middle4OutStacker(BlinkerSpeed, leftColor);
        break;
      case 41:
        breatheAnimation(leds_L, leds_R, leds_3, leftColor, RightColor, thrdColor, BlinkerSpeed);
        break;
      case 42:
        colorBounce(leds_L, leftColor, BlinkerSpeed, 10);
        colorBounce(leds_R, RightColor, BlinkerSpeed, 10);
        colorBounce(leds_3, thrdColor, BlinkerSpeed, 10);
        break;
      case 43:
        colorBounceRain(leds_L, BlinkerSpeed, 10);
        colorBounceRain(leds_R, BlinkerSpeed, 10);
        colorBounceRain(leds_3, BlinkerSpeed, 10);
        break;
    }
  }
}
