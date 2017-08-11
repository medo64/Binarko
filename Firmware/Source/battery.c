#include <pic.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"


#define CHANNEL_ANF0  0b101000
#define CHANNEL_FVR   0b111110
#define USE_VREF  true
#define USE_VDD   false

#define BATTERY_MILLIVOLTS_MIN  3000
#define BATTERY_MILLIVOLTS_MAX  4500


bool hadInit = false;

void adcInit() {
    ADFVR1 = 1; ADFVR0 = 0; //A/D Converter Fixed Voltage Reference Peripheral output is 2x (2.048V)
    FVREN = 1; //Fixed Voltage Reference is enabled
    while(!FVRRDY);

    ADFM = 1; //Right justified. Six Most Significant bits of ADRESH are set to '0' when the conversion result is loaded.
    ADCS2 = 0; ADCS1 = 1; ADCS0 = 1;//Frc (clock supplied from a dedicated RC oscillator)
        
    hadInit = true;
}

uint16_t getRawAdc(uint8_t channel, bool useVref) {
    if (hadInit == false) { adcInit(); }

    if (useVref) {
        ADPREF1 = 1; ADPREF0 = 1; //Vref+ is connected to internal fixed voltage reference
    } else {
        ADPREF1 = 0; ADPREF0 = 0; //Vref+ is connected to Vdd
    }
    
    ADCON0 = (channel << 2);
    ADON = 1; //ADC is enabled
    _delay(10); //to discharge holding cap if there was measurement just before (at least 10us)
    
    ADCON0bits.GO = true; //Setting this bit starts an A/D conversion cycle.
    while(ADCON0bits.GOnDONE); //A/D conversion cycle in progress.
    ADON = 0;

    return ADRES;
}


uint16_t getBatteryVoltage() {
    return (getRawAdc(CHANNEL_ANF0, USE_VREF) * 5);
}

uint16_t getSupplyVoltage() {
    uint32_t millivolts = (65536 / getRawAdc(CHANNEL_FVR, USE_VDD) * 2048 / 64);
    return (uint16_t)millivolts; //https://edeca.net/pages/measuring-pic-vdd-with-no-external-components-using-the-fvr/
}

uint8_t getSupplyVoltageAsPercent() {
    uint16_t millivolts = getSupplyVoltage();
    if (millivolts < BATTERY_MILLIVOLTS_MIN) {
        return 0;
    } else if (millivolts > BATTERY_MILLIVOLTS_MAX) {
        return 100;
    } else {
        uint16_t percentU = ((millivolts - BATTERY_MILLIVOLTS_MIN) >> 4) * 25;
        uint16_t percentD = ((BATTERY_MILLIVOLTS_MAX - BATTERY_MILLIVOLTS_MIN) >> 4) / 4;
        return (uint8_t)(percentU / percentD);
    }
}
