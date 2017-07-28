#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "voltage.h"
#include "buttons.h"
#include "led.h"


void main(void) {
    init();
    displaySplash();

    sampleButtons();
    if (getDisplayInstantButton()) {
        displayMilivolts(getBatteryVoltage());
        wait_250ms(); wait_250ms(); wait_250ms(); wait_250ms();
        displayMilivolts(getSupplyVoltage());
        wait_250ms(); wait_250ms(); wait_250ms(); wait_250ms();
    }

    uint8_t value = 0;
    bool displayOn = true;
        
    while (true) {
        sampleButtons();
        
        if (getPlusButton() || getPlusLongButton()) {
            value++;
        } else {
            uint8_t buttons = getDigitButtons();
            value ^= buttons;
        }
        
        if (getDisplayButton()) {
            displayOn = !displayOn;
        }
        
        setLed(value);
        if (displayOn) {
            displayDecimalNumber(value);
        } else {
            displayOff();
        }
    }
}
