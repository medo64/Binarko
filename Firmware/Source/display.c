#include <pic.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "config.h"


#define DIGIT_1  LATB0
#define DIGIT_2  LATB1
#define DIGIT_3  LATB2
#define DIGIT_4  LATB3
#define DIGIT_5  LATF4
#define DIGIT_6  LATA4
#define DIGIT_7  LATA5
#define DIGIT_8  LATE0

#define SEGMENT_A1   LATF3
#define SEGMENT_B1   LATC2
#define SEGMENT_C1   LATA3
#define SEGMENT_D1   LATE1
#define SEGMENT_E1   LATE2
#define SEGMENT_F1   LATF2
#define SEGMENT_G1   LATF1
#define SEGMENT_DP1  LATA2

#define SEGMENT_A2   LATD1
#define SEGMENT_B2   LATC4
#define SEGMENT_C2   LATB5
#define SEGMENT_D2   LATA0
#define SEGMENT_E2   LATA1
#define SEGMENT_F2   LATC3
#define SEGMENT_G2   LATD0

#define SEGMENT_A3   LATD3
#define SEGMENT_B3   LATD2
#define SEGMENT_C3   LATF5
#define SEGMENT_D3   LATF7
#define SEGMENT_E3   LATB4
#define SEGMENT_F3   LATC5
#define SEGMENT_G3   LATF6


void setLed(uint8_t value) {
    DIGIT_1 = ((value & 0x01) != 0);
    DIGIT_2 = ((value & 0x02) != 0);
    DIGIT_3 = ((value & 0x04) != 0);
    DIGIT_4 = ((value & 0x08) != 0);
    DIGIT_5 = ((value & 0x10) != 0);
    DIGIT_6 = ((value & 0x20) != 0);
    DIGIT_7 = ((value & 0x40) != 0);
    DIGIT_8 = ((value & 0x80) != 0);
}

void setDigit1Segments(uint8_t value) {
    SEGMENT_A1 = ((value & 0x01) != 0);
    SEGMENT_B1 = ((value & 0x02) != 0);
    SEGMENT_C1 = ((value & 0x04) != 0);
    SEGMENT_D1 = ((value & 0x08) != 0);
    SEGMENT_E1 = ((value & 0x10) != 0);
    SEGMENT_F1 = ((value & 0x20) != 0);
    SEGMENT_G1 = ((value & 0x40) != 0);
    SEGMENT_DP1 = ((value & 0x80) != 0);
}

void setDigit2Segments(uint8_t value) {
    SEGMENT_A2 = ((value & 0x01) != 0);
    SEGMENT_B2 = ((value & 0x02) != 0);
    SEGMENT_C2 = ((value & 0x04) != 0);
    SEGMENT_D2 = ((value & 0x08) != 0);
    SEGMENT_E2 = ((value & 0x10) != 0);
    SEGMENT_F2 = ((value & 0x20) != 0);
    SEGMENT_G2 = ((value & 0x40) != 0);
}

void setDigit3Segments(uint8_t value) {
    SEGMENT_A3 = ((value & 0x01) != 0);
    SEGMENT_B3 = ((value & 0x02) != 0);
    SEGMENT_C3 = ((value & 0x04) != 0);
    SEGMENT_D3 = ((value & 0x08) != 0);
    SEGMENT_E3 = ((value & 0x10) != 0);
    SEGMENT_F3 = ((value & 0x20) != 0);
    SEGMENT_G3 = ((value & 0x40) != 0);
}

void setDigitSegments(uint8_t digit1, uint8_t digit2, uint8_t digit3) {
    switch(digit1) {
        case 0: setDigit1Segments(0b00111111); break;
        case 1: setDigit1Segments(0b00000110); break;
        case 2: setDigit1Segments(0b01011011); break;
        case 3: setDigit1Segments(0b01001111); break;
        case 4: setDigit1Segments(0b01100110); break;
        case 5: setDigit1Segments(0b01101101); break;
        case 6: setDigit1Segments(0b01111101); break;
        case 7: setDigit1Segments(0b00000111); break;
        case 8: setDigit1Segments(0b01111111); break;
        case 9: setDigit1Segments(0b01101111); break;
        case 10: setDigit1Segments(0b01110111); break;
        case 11: setDigit1Segments(0b01111100); break;
        case 12: setDigit1Segments(0b00111001); break;
        case 13: setDigit1Segments(0b01011110); break;
        case 14: setDigit1Segments(0b01111001); break;
        case 15: setDigit1Segments(0b01110001); break;
        case 16: setDigit1Segments(0b01110100); break;
        default: setDigit1Segments(0); break;
    }

    switch(digit2) {
        case 0: setDigit2Segments(0b00111111); break;
        case 1: setDigit2Segments(0b00000110); break;
        case 2: setDigit2Segments(0b01011011); break;
        case 3: setDigit2Segments(0b01001111); break;
        case 4: setDigit2Segments(0b01100110); break;
        case 5: setDigit2Segments(0b01101101); break;
        case 6: setDigit2Segments(0b01111101); break;
        case 7: setDigit2Segments(0b00000111); break;
        case 8: setDigit2Segments(0b01111111); break;
        case 9: setDigit2Segments(0b01101111); break;
        case 10: setDigit2Segments(0b01110111); break;
        case 11: setDigit2Segments(0b01111100); break;
        case 12: setDigit2Segments(0b00111001); break;
        case 13: setDigit2Segments(0b01011110); break;
        case 14: setDigit2Segments(0b01111001); break;
        case 15: setDigit2Segments(0b01110001); break;
        default: setDigit2Segments(0); break;
    }

    switch(digit3) {
        case 0: setDigit3Segments(0b00111111); break;
        case 1: setDigit3Segments(0b00000110); break;
        case 2: setDigit3Segments(0b01011011); break;
        case 3: setDigit3Segments(0b01001111); break;
        case 4: setDigit3Segments(0b01100110); break;
        case 5: setDigit3Segments(0b01101101); break;
        case 6: setDigit3Segments(0b01111101); break;
        case 7: setDigit3Segments(0b00000111); break;
        case 8: setDigit3Segments(0b01111111); break;
        case 9: setDigit3Segments(0b01101111); break;
        case 10: setDigit3Segments(0b01110111); break;
        case 11: setDigit3Segments(0b01111100); break;
        case 12: setDigit3Segments(0b00111001); break;
        case 13: setDigit3Segments(0b01011110); break;
        case 14: setDigit3Segments(0b01111001); break;
        case 15: setDigit3Segments(0b01110001); break;
        default: setDigit3Segments(0); break;
    }
}


void displayDecimalNumber(uint8_t value) {
    uint8_t digit1 = (value / 100);
    uint8_t digit2 = ((value / 10) % 10);
    uint8_t digit3 = (value % 10);
    if (value < 10) {
        setDigitSegments(255, 255, digit3);
    } else if (value < 100) {
        setDigitSegments(255, digit2, digit3);
    } else {
        setDigitSegments(digit1, digit2, digit3);
    }
}

void displayHexadecimalNumber(uint8_t value) {
    uint8_t digit1 = (value / 16); //not bitshifted to keep timings
    uint8_t digit2 = (value % 16); //not bitshifted to keep timings
    uint8_t digitM = ((value / 10) % 10); //keep calculation to keep timings

    setDigitSegments(16, digit1, digit2);
}

void displayMilivolts(uint16_t value) {
    if (value <= 9999) {
        uint8_t digit1 = (value / 1000);
        uint8_t digit2 = ((value / 100) % 10);
        uint8_t digit3 = (value / 10) % 10;
        setDigitSegments(digit1, digit2, digit3);
    } else {
        setDigitSegments(0, 255, 255);
    }
    SEGMENT_DP1 = true;
}

void displayNothing() {
    uint16_t value = 42;
    //keep calculation to keep timings
    uint8_t digit1 = (value / 100);
    uint8_t digit2 = ((value / 10) % 10);
    uint8_t digit3 = (value % 10);
    
    //show nothing
    setDigit1Segments(0);
    setDigit2Segments(0);
    setDigit3Segments(0);
}

void displayOff() {
    setDigit1Segments(0b00111111);
    setDigit2Segments(0b01110001);
    setDigit3Segments(0b01110001);
}

void displayBat() {
    setDigit1Segments(0b01111100);
    setDigit2Segments(0b01110111);
    setDigit3Segments(0b01111000);
}

void displayDot() {
    setDigit1Segments(0b10000000);
    setDigit2Segments(0b00000000);
    setDigit3Segments(0b00000000);
}

void displaySplash() {
    setLed(0x80); setDigit1Segments(0b00110000); setDigit2Segments(0b00000000); setDigit3Segments(0b00000000); wait_10ms();
    setLed(0xC0); setDigit1Segments(0b01111001); setDigit2Segments(0b00000000); setDigit3Segments(0b00000000); wait_10ms();
    setLed(0xE0); setDigit1Segments(0b01111111); setDigit2Segments(0b00000000); setDigit3Segments(0b00000000); wait_10ms();
    setLed(0x70); setDigit1Segments(0b11001111); setDigit2Segments(0b00110000); setDigit3Segments(0b00000000); wait_10ms();
    setLed(0x38); setDigit1Segments(0b10000110); setDigit2Segments(0b00111001); setDigit3Segments(0b00000000); wait_10ms();
    setLed(0x1C); setDigit1Segments(0b00000000); setDigit2Segments(0b01111111); setDigit3Segments(0b00000000); wait_10ms();
    setLed(0x0E); setDigit1Segments(0b00000000); setDigit2Segments(0b01001111); setDigit3Segments(0b00110000); wait_10ms();
    setLed(0x07); setDigit1Segments(0b00000000); setDigit2Segments(0b00000110); setDigit3Segments(0b01111001); wait_10ms();
    setLed(0x03); setDigit1Segments(0b00000000); setDigit2Segments(0b00000000); setDigit3Segments(0b01111111); wait_10ms();
    setLed(0x01); setDigit1Segments(0b00000000); setDigit2Segments(0b00000000); setDigit3Segments(0b01001111); wait_10ms();
    setLed(0x00); setDigit1Segments(0b00000000); setDigit2Segments(0b00000000); setDigit3Segments(0b00000110); wait_10ms();
    setLed(0x00); setDigit1Segments(0b00000000); setDigit2Segments(0b00000000); setDigit3Segments(0b00000000);
}
