#include <pic.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"


bool hadInit = false;

void batteryInit() {
    ADFVR1 = 1; ADFVR0 = 0; //A/D Converter Fixed Voltage Reference Peripheral output is 2x (2.048V)
    FVREN = 1; //Fixed Voltage Reference is enabled
    while(!FVRRDY);

    ADFM = 1; //Right justified. Six Most Significant bits of ADRESH are set to '0' when the conversion result is loaded.
    ADCS2 = 0; ADCS1 = 1; ADCS0 = 1;//Frc (clock supplied from a dedicated RC oscillator)
    ADPREF1 = 1; ADPREF0 = 1; //Vref+ is connected to internal fixed voltage reference
        
    hadInit = true;
}

uint16_t getRawAdc() {
    if (hadInit == false) { batteryInit(); }

    CHS5 = 1; CHS4 = 0; CHS3 = 1; CHS2 = 0; CHS1 = 0; CHS0 = 0; //RF0    
    ADON = 1; //ADC is enabled
    _delay(10); //to discharge holding cap if there was measurement just before (at least 10us)
    
    ADCON0bits.GO = true; //Setting this bit starts an A/D conversion cycle.
    while(ADCON0bits.GOnDONE); //A/D conversion cycle in progress.
    ADON = 0;

    return ADRES;
}


uint16_t getBatteryVoltage() {
    return (getRawAdc() * (uint16_t)5);
}
