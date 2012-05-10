#ifndef AVRTONE_H
#define AVRTONE_H

#include <stdint.h>

#define TONE_PRESCALE 1024
#define TONE_TIMER_FREQ_HZ (F_CPU / TONE_PRESCALE)


void initOutput(void);
void initToneTimer(void);

inline void startToneTimer(void);
inline void stopToneTimer(void);

void setToneFreq(uint16_t f_Hz);
void playTone(uint16_t f_Hz, uint16_t dur_ms);


#endif /* AVRTONE_H */
