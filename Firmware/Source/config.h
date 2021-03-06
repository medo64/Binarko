#ifndef CONFIG_H
#define CONFIG_H

#define _XTAL_FREQ  1000000

void init();
void clrwdt();
void reset();

void deepSleep(void);
void doze();
void wake();

void wait_10ms();
void wait_250ms();
void wait_1000ms();

#endif
