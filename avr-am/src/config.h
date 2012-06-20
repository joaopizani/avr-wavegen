#ifndef AVRAM_CONFIG_H
#define AVRAM_CONFIG_H

#include <avr/io.h>
#include <stdint.h>

#define CARRIER_PRESCALE 1
#define SYSTEM_FREQ_KHZ (F_CPU / 1000)
#define CARRIER_TIMER_FREQ_KHZ (SYSTEM_FREQ_KHZ / CARRIER_PRESCALE)



void initCarrierTimer(void);

void setCarrierFreqKHz(uint16_t f_KHz);

inline void startCarrierTimer(void);
inline void stopCarrierTimer(void);


#endif /* AVRAM_CONFIG_H */
