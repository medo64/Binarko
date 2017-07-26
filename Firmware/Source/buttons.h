#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdbool.h>
#include <stdint.h>


void sampleButtons(void);

uint8_t getDigitButtons();
bool getPlusButton(void);
bool getPlusLongButton(void);
bool getDisplayButton(void);
bool getDisplayHeldButton(void);

#endif
