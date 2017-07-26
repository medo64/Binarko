#include <pic.h>
#include <stdbool.h>
#include <stdint.h>
#include "buttons.h"


#define BUTTON_D1       PORTCbits.RC7
#define BUTTON_D2       PORTDbits.RD4
#define BUTTON_D3       PORTDbits.RD5
#define BUTTON_D4       PORTDbits.RD6
#define BUTTON_D5       PORTDbits.RD7
#define BUTTON_D6       PORTCbits.RC1
#define BUTTON_D7       PORTCbits.RC0
#define BUTTON_D8       PORTAbits.RA6
#define BUTTON_DISPLAY  PORTAbits.RA7
#define BUTTON_PLUS     PORTCbits.RC6

#define MAX_SHORT     5
#define MAX_LONG     50
#define MAX_LONGER  200

uint8_t buttonCounter[10];
bool buttonPressed[10];
bool buttonPressedLong[10] = { false, false, false, false, false, false, false, false, false, false };

void sampleButtons() {
    bool buttonState[10];
    buttonState[0] = !BUTTON_D1;
    buttonState[1] = !BUTTON_D2;
    buttonState[2] = !BUTTON_D3;
    buttonState[3] = !BUTTON_D4;
    buttonState[4] = !BUTTON_D5;
    buttonState[5] = !BUTTON_D6;
    buttonState[6] = !BUTTON_D7;
    buttonState[7] = !BUTTON_D8;
    buttonState[8] = !BUTTON_PLUS;
    buttonState[9] = !BUTTON_DISPLAY;

    for (uint8_t i=0; i<10; i++) {
        buttonPressed[i] = false; //all buttons are marked non-active
        if (buttonState[i]) {
            if (buttonCounter[i] < MAX_LONGER) { buttonCounter[i]++; } //just count how long has it been pressed
        } else { //check if button has been pressed on release
            if (buttonCounter[i] >= MAX_SHORT) { //check duration
                if (!buttonPressedLong[i]) { //filter out those who had long press
                    buttonPressed[i] = true;
                }
                buttonPressedLong[i] = false; //forget about long press
            }
            buttonCounter[i] = 0; //reset counter to start from scratch
        }
    }
}


uint8_t getDigitButtons() {
    uint8_t state = 0;
    state |= buttonPressed[0] ? 0x01 : 0x00;
    state |= buttonPressed[1] ? 0x02 : 0x00;
    state |= buttonPressed[2] ? 0x04 : 0x00;
    state |= buttonPressed[3] ? 0x08 : 0x00;
    state |= buttonPressed[4] ? 0x10 : 0x00;
    state |= buttonPressed[5] ? 0x20 : 0x00;
    state |= buttonPressed[6] ? 0x40 : 0x00;
    state |= buttonPressed[7] ? 0x80 : 0x00;
    return state;
}


bool getPlusButton() {
    return buttonPressed[8];
}

bool getPlusLongButton() {
    if (buttonCounter[8] >= MAX_LONG) {
        buttonCounter[8] = 0;
        buttonPressedLong[8] = true;
        return true;
    } else {
        return false;
    }
}


bool getDisplayButton() {
    return buttonPressed[9];
}
