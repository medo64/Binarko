#include <pic.h>
#include "config.h"


#pragma config FEXTOSC  = OFF
#pragma config RSTOSC   = HFINT1
#pragma config CLKOUTEN = OFF
#pragma config CSWEN    = OFF
#pragma config FCMEN    = OFF

#pragma config MCLRE    = OFF
#pragma config PWRTE    = ON
#pragma config LPBOREN  = OFF
#pragma config BOREN    = ON
#pragma config BORV     = LO
#pragma config ZCD      = OFF
#pragma config PPS1WAY  = OFF
#pragma config STVREN   = ON

#pragma config WDTCPS   = WDTCPS_11
#pragma config WDTE     = NSLEEP
#pragma config WDTCWS   = WDTCWS_7
#pragma config WDTCCS   = LFINTOSC

#pragma config BBSIZE   = BB512
#pragma config BBEN     = OFF
#pragma config SAFEN    = OFF
#pragma config WRTAPP   = OFF
#pragma config WRTB     = OFF
#pragma config WRTC     = OFF
#pragma config WRTSAF   = OFF
#pragma config LVP      = OFF

#pragma config CP       = OFF


void init() {
    GIE = 0; //disable interrupts

    LATA   = 0b00000000;
    LATB   = 0b00000000;
    LATC   = 0b00000000;
    LATD   = 0b00000000;
    LATE   = 0b00000000;
    LATF   = 0b00000000;

    TRISA  = 0b11000000;
    TRISB  = 0b10000000;
    TRISC  = 0b11000011;
    TRISD  = 0b11110000;
    TRISE  = 0b11111000;
    TRISF  = 0b00000001;

    WPUA   = 0b11111111;
    WPUB   = 0b11111111;
    WPUC   = 0b11111111;
    WPUD   = 0b11111111;
    WPUE   = 0b11111111;
    WPUF   = 0b11111110;

    ANSELA = 0b00000000;
    ANSELB = 0b00000000;
    ANSELC = 0b00000000;
    ANSELD = 0b00000000;
    ANSELE = 0b00000000;
    ANSELF = 0b00000001;
}

void clrwdt() {
    asm("CLRWDT");
}

void reset() {
    asm("RESET");
}

void deepSleep() {
    IDLEN = 0;
    VREGPM = 1;
    asm("SLEEP");
    asm("NOP");
}

void doze() {
    DOZE0 = 1; DOZE1 = 1; DOZE0 = 1;
    DOZEN = 1;
}

void wake() {
    DOZEN = 0;
}


void wait_10ms() {
    __delay_ms(10);
}

void wait_250ms() {
    __delay_ms(250);
}

void wait_1000ms() {
    __delay_ms(1000);
}
