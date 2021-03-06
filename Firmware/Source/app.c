#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "battery.h"
#include "buttons.h"
#include "display.h"
#include "timer.h"


void gotoDiagnostics();
void gotoAutoSleep();
void gotoSleep();


uint8_t value = 0;
bool displayOn = true;
bool displayDecimal = true;


void main(void) {
    init();
    if (getBatteryPercent() <= 3) { deepSleep(); reset();  }

    displaySplash();
    initTimer();

    if (getDisplayInstantButton() && getPlusInstantButton()) { gotoDiagnostics(); }

    bool anyPressed = false;
    uint8_t idleCounter = 0;
    uint8_t batteryCounter = 0;
    while (true) {
        clrwdt();
        if (sampleButtons()) { anyPressed = true; }
        
        if (hasElapsed1s()) { //house keeping every 1s
            if (!anyPressed) { idleCounter++; } else { idleCounter = 0;}
            if (idleCounter == 120) { //auto-sleep in 2 minutes
                gotoAutoSleep();
                idleCounter = 0;
            }
            anyPressed = false;
            
            batteryCounter++;
            if (batteryCounter == 60) {
                uint8_t batteryPercent = getBatteryPercent();
                if (batteryPercent == 0) {
                    reset();
                } else if (batteryPercent < 10) {
                    displayBat(); //just flash display a moment
                    wait_250ms();
                    if (batteryPercent <= 5) { wait_250ms(); }
                    if (batteryPercent <= 3) { wait_250ms(); }
                }
                batteryCounter = 0;
            }
        }
        
        if (getPlusButton() || getPlusHeldButton()) {
            value++;
        } else {
            uint8_t buttons = getDigitButtons();
            value ^= buttons;
        }

        if (getDisplayHeldLongButton()) {
            gotoSleep();
        } else if (getDisplayHeldButton()) {
            displayOn = true;
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
    uint8_t secondsCounter = 0;
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
            if (mode == 3) { secondsCounter = 0; resetTimer(); displayDecimalNumber(0); } //reset timer
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
                if (mode == 3) { secondsCounter = 0; resetTimer(); displayDecimalNumber(0); } //reset timer
            }
        }
        
        setLed(1 << mode);
        switch(mode) {
            case 0: //self-measured supply voltage
                if (measurementWait == 0) { displayMilivolts(getBatteryVoltage()); }
                break;

            case 1: //supply voltage in percents
                if (measurementWait == 0) { displayDecimalNumber(getBatteryPercent()); }
                break;
                
            case 2: //test timer
                if (hasElapsed1s()) {
                    secondsCounter++;
                    displayDecimalNumber(secondsCounter);
                }
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


void sleep() {
    setLed(0x00);
    displayNothing();

    doze();
    while(!sampleButtons()) { clrwdt(); }
    wake();

    //reset values
    value = 0;
    displayOn = true;
    displayDecimal = true;
}

void gotoAutoSleep() {
    displayOff();
    
    uint8_t idleCounter = 0;
    while (idleCounter < 10) { //about 10 seconds
        clrwdt();
        if (hasElapsed1s()) { idleCounter++; }
        if (sampleButtons()) { return; } //cancel sleep since someone touched the button
    }
    
    sleep();
}

void gotoSleep() {
    setLed(0x00);
    displayOff();
    wait_1000ms();

    clrwdt();
    while(getDisplayInstantButton());
}
