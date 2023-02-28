#include <Arduino.h>
#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <EEPROM.h>

const int VALVE_OPEN = 1;
const int VALVE_CLOSED = 0;
const int VALVE_ADDRESS = 0;

int valveState;

void closeValve(bool save = true) {
  valveState = VALVE_CLOSED;
  MFS.write("CLSD");
  MFS.writeLeds(LED_1, OFF);

  if(save)
    EEPROM.write(VALVE_ADDRESS, valveState);
}

void openValve(bool save = true) {
  valveState = VALVE_OPEN;
  MFS.write("OPEN");
  MFS.writeLeds(LED_1, ON);

  if(save)
    EEPROM.write(VALVE_ADDRESS, valveState);
}

void setup() {
  Timer1.initialize();
  MFS.initialize(&Timer1);

  MFS.write("    "); // clear

  valveState = EEPROM.read(VALVE_ADDRESS);
  if(valveState == VALVE_OPEN) {
    openValve(false);
  } else {
    closeValve(false);
  }
}

void loop() {
  
  byte btn = MFS.getButton();
  if (btn == BUTTON_1_PRESSED) {
    if(valveState == VALVE_OPEN) {
      closeValve();
    } else {
      openValve();
    }
  }

  delay(50);
}