uint32_t climateTimer;
short climate_data[4] = {0, 0, 0, -1};


void climateTick() {
    FastLED.show();

    if (!climateTimer || (millis() - climateTimer >= 10000)) {
        climateTimer = millis();
  
        // read state of meteoSensor
        int8_t stateSensor = meteoSensor.read();

        if (stateSensor == SHT_OK) {
            climate_data[0] = round(meteoSensor.getTemperatureC());
            climate_data[1] = round(meteoSensor.getHumidity());
        }

        // read state of co2Sensor
        if(ccs.available()) {
            if(!ccs.readData()) {
              climate_data[2] = round(ccs.geteCO2());
              climate_data[3] = round(ccs.getTVOC());
            } else {
              climate_data[2] = 0;
              climate_data[3] = 0;
            }

        }
    }

    // check comfort levels
    CRGB colors[4] = {};

    if (climate_data[0] > 29) {
        colors[0] = CRGB::Green;
    } else if (climate_data[0] < 15) {
        colors[0] = CRGB::Red;
    } else {
        colors[0] = CRGB::White;
    }

    if (climate_data[1] > 60) {
        colors[1] = CRGB::Red;
    } else if (climate_data[1] < 30) {
        colors[1] = CRGB::Yellow;
    } else {
        colors[1] = CRGB::White;
    }

    if (climate_data[2] > 500) {
        colors[2] = CRGB::Green;
    } else {
        colors[2] = CRGB::White;
    }

    if (climate_data[3] > 10) {
        colors[3] = CRGB::Green;
    } else {
        colors[3] = CRGB::White;
    }

    // concat sensor values with signs/measurements
    String climate_string = "";

    // set temperature sign
    if (climate_data[0] > 0) {
        climate_string = "+";
    }
    if (climate_data[0] < 0) {
        climate_string = "-";
    }
    climate_string.concat(climate_data[0]);
    climate_string.concat(" ");
    climate_string.concat(climate_data[1]);
    climate_string.concat("% ");
    climate_string.concat(climate_data[2]);
    climate_string.concat("ppm ");
    climate_string.concat(climate_data[3]);
    climate_string.concat("ч");

    fillString(climate_string, colors, true);
}
