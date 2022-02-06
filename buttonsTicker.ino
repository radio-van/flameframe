boolean changingStateFlag = false;  // flag to prevent multiple actions on one button press


void buttonsTick() {

    // read buttons states
    bool button_mode_pressed = digitalRead(BUTTON_MODE_PIN);
    bool button_next_pressed = digitalRead(BUTTON_NEXT_PIN);
    bool button_prev_pressed = digitalRead(BUTTON_PREV_PIN);
  
    // DEBUG
    //button_mode_pressed = false;
    button_next_pressed = false;
    button_prev_pressed = false;
  
    if (button_mode_pressed) {
        if (!changingStateFlag) {
            changingStateFlag = true;
  
            FastLED.clear(true);
  
            // switch global mode
            if (global_mode == 0) {
                global_mode = 1;
            } else {
                global_mode = 0;
            }
  
        }
    }
  
    if (button_next_pressed) {
        if (!changingStateFlag) {
            changingStateFlag = true;
  
            FastLED.clear(true);
  
            if (global_mode == 0) {  // effects mode
                // switch to next effect
                currentMode++;
                if (currentMode > MODE_AMOUNT) {
                    // return to first mode
                    currentMode = 0;
                }
            } else {
                brightness += 5;
                FastLED.setBrightness(brightness);
                if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
            }
        }
    }
  
    if (button_prev_pressed) {
        if (!changingStateFlag) {
            changingStateFlag = true;
  
            FastLED.clear(true);
  
            if (global_mode == 0) {  // effects mode
                // switch to next effect
                currentMode--;
                if (currentMode < 0) {
                    // return to last mode
                    currentMode = MODE_AMOUNT;
                }
            } else {
                brightness -= 5;
                FastLED.setBrightness(brightness);
                if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
            }
        }
    }
  
    // if no buttons pressed - allow reading their state again
    if (!button_mode_pressed && !button_next_pressed && !button_prev_pressed) {
        changingStateFlag = false;
    }

}
