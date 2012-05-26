#ifndef AVRTONE_H
#define AVRTONE_H

#include <stdint.h>
#include <avr-alarm/alarm.h>

/* perfect prescale factor for good frequency range and resolution
 * resolution of 1Hz and range C4 to C6.
 */
#define TONE_PRESCALE 128

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
