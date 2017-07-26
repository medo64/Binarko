#ifndef LED_H
#define LED_H

#include <stdbool.h>
#include <stdint.h>


void setLed(uint8_t value);
void setDigit1Segments(uint8_t value);
void setDigit2Segments(uint8_t value);
void setDigit3Segments(uint8_t value);

void setDecimalNumber(uint8_t value);
void setHexadecimalNumber(uint8_t value);
void displayOff(void);
void displaySplash(void);

#endif
