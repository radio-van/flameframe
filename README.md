#### FlameFrame

Heavily based on [GyverLamp](https://github.com/AlexGyver/GyverLamp/).  

All effects are taken from the mentioned repo (only some of them present in this firmware).  
New mode to display climate data from a couple of sensors:  
- `CCS811` effective CO2 and TVOC sensor
- `Troyka Meteo Sensor` (based on `SHT31` sensor)

Firmware uses single button to cycle through effects and climate mode.
Firmware uses 16x16 `WS2812b` LED matrix to display effects.

Core of project is `Iskra Nano Pro` (`Arduino Nano` clone). Firmware uses about 79% of its memory,  
so a more powerful controller is a good idea.
