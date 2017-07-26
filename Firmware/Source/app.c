#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "buttons.h"
#include "led.h"

void main(void) {
    init();
    displaySplash();

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
            setDecimalNumber(value);
        } else {
            displayOff();
        }
    }
}
