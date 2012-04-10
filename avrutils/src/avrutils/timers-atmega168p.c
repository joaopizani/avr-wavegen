#include <stdint.h>
#include <avrutils/timers-atmega168p.h>


uint8_t getTimerPrescaleBits(uint16_t prescale) {
    switch(prescale) {
        case 0:    return 0;
        case 1:    return 1;
        case 8:    return 2;
        case 32:   return 3;
        case 64:   return 4;
        case 128:  return 5;
        case 256:  return 6;
        case 1024: return 7;
        default:   return 0;
    }
}

