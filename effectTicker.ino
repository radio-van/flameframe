uint32_t effTimer;

void effectsTick() {
    //     passed time in millisec                     if not noise            if noise
    if (millis() - effTimer >= ((currentMode > 3) ? modes[currentMode].speed : 50) ) {
      effTimer = millis();

      switch (currentMode) {
        case 0: fireRoutine();
          break;
        case 1: snowRoutine();
          break;
        case 2: matrixRoutine();
          break;
        case 3: sparklesRoutine();
          break;
        case 4: madnessNoise();
          break;
        case 5: cloudNoise();
          break;
      }
      FastLED.show();
  }
}
