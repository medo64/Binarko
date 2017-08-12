#include <pic.h>
#include <stdbool.h>

#define TIMER_INIT_VALUE  12

void initTimer() {
    T016BIT = 0; //8-bit mode
    T0CS2 = 1; T0CS1 = 0; T0CS0 = 0; //LFINTOSC
    T0CKPS3 = 0; T0CKPS2 = 1; T0CKPS1 = 1; T0CKPS0 = 1; //1:128 prescaler

    TMR0L = TIMER_INIT_VALUE;

    TMR0IF = 0;
    TMR0IE = 1;

    T0EN = 1;
}

void resetTimer() {
    TMR0L = TIMER_INIT_VALUE;
    TMR0IF = 0;
}

bool hasElapsed1s(void) {
    if (TMR0IF) {
        TMR0L = TIMER_INIT_VALUE;
        TMR0IF = 0;
        return true;
    } else {
        return false;
    }
}
