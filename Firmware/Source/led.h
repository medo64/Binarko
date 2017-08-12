#ifndef LED_H
#define LED_H

#include <stdbool.h>
#include <stdint.h>


void setLed(uint8_t value);
void setDigit1Segments(uint8_t value);
void setDigit2Segments(uint8_t value);
void setDigit3Segments(uint8_t value);

void displaySplash(void);
void displayDecimalNumber(uint8_t value);
void displayMilivolts(uint16_t value);
void displayHexadecimalNumber(uint8_t value);
void displayOff(void);
void displayBat(void);
void displayDot(void);
void displayNothing(void);

#endif
