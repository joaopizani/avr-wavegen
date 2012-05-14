#ifndef AVRTONE_H
#define AVRTONE_H

#include <stdint.h>
#include <alarm.h>

#define TONE_PRESCALE 1024
#define TONE_TIMER_FREQ_HZ (F_CPU / TONE_PRESCALE)


void initOutput(void);
void initToneTimer(void);

inline void startToneTimer(void);
inline void stopToneTimer(void);

inline void quiet(void);
void setToneFreq(uint16_t f_Hz);

void setFreqAlarmHandler(void* freq_uint16_ptr);

void playTone(uint16_t f_Hz, time_ms_t dur_ms);


#endif /* AVRTONE_H */
