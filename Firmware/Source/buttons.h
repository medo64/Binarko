#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdbool.h>
#include <stdint.h>


bool sampleButtons(void);

uint8_t getDigitButtons();
bool getPlusButton(void);
bool getPlusHeldButton(void);
bool getDisplayButton(void);
bool getDisplayHeldButton(void);
bool getDisplayHeldLongButton(void);
bool getDisplayInstantButton(void);

#endif
