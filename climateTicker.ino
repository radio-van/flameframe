uint32_t climateTimer;


struct Climate {
    String sign;
    int value;
    CRGB color;
    String measurement;
};


// climate data structures with default params
Climate co2 = {"", 0, CRGB::White, "ppm"};
Climate humidity = {"", 0, CRGB::White, "%"};
Climate temperature = {"", 0, CRGB::White, ""};
Climate tvoc = {"", -1, CRGB::White, "ч"};


void climateTick() {
    if (millis() - climateTimer >= 1000) {
        climateTimer = millis();
  
        // read state of meteoSensor
        int stateSensor = meteoSensor.read();
  
        switch (stateSensor) {
          case SHT_OK:
            temperature.value = int(meteoSensor.getTemperatureC());
            humidity.value = int(meteoSensor.getHumidity());
            break;
          case SHT_ERROR_DATA:
            break;
          case SHT_ERROR_CHECKSUM:
            break;
        }
  
        // read state of co2Sensor
        if(ccs.available()) {
            if(!ccs.readData()) {
              co2.value = int(ccs.geteCO2());
              tvoc.value = int(ccs.getTVOC());
            }
        }

        // set temperature sign
        if (temperature.value > 0) {
            temperature.sign = String("+");
        }
        if (temperature.value < 0) {
            temperature.sign = String("-");
        }

        // check comfort levels
        if (temperature.value > 29) {
            temperature.color = CRGB::Green;
        } else if (temperature.value < 15) {
            temperature.color = CRGB::Red;
        } else {
            temperature.color = CRGB::White;
        }

        if (humidity.value > 60) {
            humidity.color = CRGB::Red;
        } else if (humidity.value < 30) {
            humidity.color = CRGB::Green;
        } else {
            humidity.color = CRGB::White;
        }

        if (co2.value > 500) {
            co2.color = CRGB::Green;
        } else {
            co2.color = CRGB::White;
        }

        if (tvoc.value > 10) {
            tvoc.color = CRGB::Green;
        } else {
            tvoc.color = CRGB::White;
        }

    }

    // concat sensor values with signs/measurements
    String temperature_string = String(temperature.sign);
    temperature_string.concat(temperature.value);
    String humidity_string = String(humidity.value);
    humidity_string.concat(humidity.measurement);
    String co2_string = String(co2.value);
    co2_string.concat(co2.measurement);
    String tvoc_string = String(tvoc.value);
    tvoc_string.concat(tvoc.measurement);

    // wrap climate data into {text, color} structures
    Text temperature_text = {temperature.color, temperature_string};
    Text humidity_text = {humidity.color, humidity_string};
    Text co2_text = {co2.color, co2_string};
    Text tvoc_text = {tvoc.color, tvoc_string};

    Text climateTexts[4] = {temperature_text, humidity_text, co2_text, tvoc_text};
    fillString(climateTexts, true);
}

