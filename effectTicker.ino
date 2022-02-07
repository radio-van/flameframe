uint32_t effTimer;

void effectsTick() {
    //     passed time in millisec                     if not noise            if noise
    if (millis() - effTimer >= ((currentMode > 4) ? 100 : 30) ) {
      effTimer = millis();

      switch (currentMode) {
        case 0:
          climateTick();
          FastLED.setBrightness(10);
          break;
        case 1: fireRoutine();
          break;
        case 2: snowRoutine();
          break;
        case 3: matrixRoutine();
          break;
        case 4: madnessNoise();
          break;
        case 5: cloudNoise();
          break;
        case 6: sparklesRoutine();
          break;
      }
      if (currentMode > 0) FastLED.setBrightness(BRIGHTNESS);
      if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
      FastLED.show();
  }
}
