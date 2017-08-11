#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "battery.h"
#include "buttons.h"
#include "led.h"


void gotoSleep();


uint8_t value = 0;
bool displayOn = true;
bool displayDecimal = true;


void main(void) {
    init();
    displaySplash();

    sampleButtons();
    if (getDisplayInstantButton()) {
        clrwdt();
        displayMilivolts(getBatteryVoltage());
        wait_250ms(); wait_250ms(); wait_250ms(); wait_250ms();
        clrwdt();
        displayMilivolts(getSupplyVoltage());
        wait_250ms(); wait_250ms(); wait_250ms(); wait_250ms();
    }
        
    while (true) {
        clrwdt();
        sampleButtons();
        
        if (getPlusButton() || getPlusHeldButton()) {
            value++;
        } else {
            uint8_t buttons = getDigitButtons();
            value ^= buttons;
        }

        if (getDisplayHeldLongButton()) {
            gotoSleep();
        } else if (getDisplayHeldButton()) {
            displayDecimal = !displayDecimal;
        } else if (getDisplayButton()) {
            displayOn = !displayOn;
        }
        
        setLed(value);
        if (displayOn) {
            if (displayDecimal) {
                displayDecimalNumber(value);
            } else {
                displayHexadecimalNumber(value);
            }
        } else {
            displayNothing();
        }
    }
}
    
void gotoSleep() {
    setLed(0x00);
    displayOff();
    wait_250ms(); wait_250ms(); wait_250ms(); wait_250ms();

    clrwdt();
    while(getDisplayInstantButton());

    displayNothing();
    doze();

    while(!sampleButtons()) {
        clrwdt();
    }

    wake();

    //reset values
    value = 0;
    displayOn = true;
    displayDecimal = true;
}
