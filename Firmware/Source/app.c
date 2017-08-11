#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "battery.h"
#include "buttons.h"
#include "led.h"


void gotoDiagnostics();
void gotoSleep();


uint8_t value = 0;
bool displayOn = true;
bool displayDecimal = true;


void main(void) {
    init();
    displaySplash();

    if (getDisplayInstantButton() && getPlusInstantButton()) { gotoDiagnostics(); }

    
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


void gotoDiagnostics() {
    displayDot();
    while(sampleButtons()) { clrwdt(); } //wait for user to release all buttons

    uint8_t measurementWait = 0;
    uint8_t mode = 0;
    while(true) {
        clrwdt();
        sampleButtons();
        if (getDisplayButton()) {
            setLed(0);
            displayNothing();
            while(sampleButtons()) { clrwdt(); } //wait for user to release all buttons
            reset();
        } else if (getPlusButton() || getPlusHeldButton()) {
            mode = ++mode % 8;
            measurementWait = 0;
        } else { //detect only a single button press
            uint8_t buttons = getDigitButtons();
            if (buttons > 0) {
                switch (buttons) {
                    case 0b00000001: mode = 0; break;
                    case 0b00000010: mode = 1; break;
                    case 0b00000100: mode = 2; break;
                    case 0b00001000: mode = 3; break;
                    case 0b00010000: mode = 4; break;
                    case 0b00100000: mode = 5; break;
                    case 0b01000000: mode = 6; break;
                    case 0b10000000: mode = 7; break;
                }
                measurementWait = 0;
            }
        }
        
        setLed(1 << mode);
        switch(mode) {
            case 0: //self-measured supply voltage
                if (measurementWait == 0) { displayMilivolts(getSupplyVoltage()); }
                break;
                
            case 1: //measure battery voltage
                if (measurementWait == 0) { displayMilivolts(getBatteryVoltage()); }
                break;

            case 2: //supply voltage in percents
                if (measurementWait == 0) { displayDecimalNumber(getSupplyVoltageAsPercent()); }
                break;

            case 5: //show third digit
                if (measurementWait == 0) { setDigit1Segments(0x00); setDigit2Segments(0x00); setDigit3Segments(0xFF); }
                break;

            case 6: //show second digit
                if (measurementWait == 0) { setDigit1Segments(0x00); setDigit2Segments(0xFF); setDigit3Segments(0x00); }
                break;

            case 7: //show first digit
                if (measurementWait == 0) { setDigit1Segments(0xFF); setDigit2Segments(0x00); setDigit3Segments(0x00); }
                break;
                
            default: //not implemented yet
                displayDot();
                break;
        }
        
        measurementWait++; //to avoid flickering display too much
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
