#ifndef AVRTONE_H
#define AVRTONE_H

#include <stdint.h>
#include <avr-alarm/alarm.h>

/* perfect prescale factor for good frequency range and resolution
 * resolution of 1Hz and range C4 to C6.
 */
#define TONE_PRESCALE 128
#define TONE_TIMER_FREQ_HZ (F_CPU / TONE_PRESCALE)

/** time resolution of tone generation, in miliseconds. The library cannot distinguish
 * between two duration with a difference less than TONE_TIME_RESOLUTION. For example, if
 * TONE_TIME_RESOLUTION = 10, then playTone(440, 500) and playTone(440, 502) will have
 * the same duration.
 */
#define TONE_TIME_RESOLUTION 10


void initOutput(void);
void initToneTimer(void);

inline void startToneTimer(void);
inline void stopToneTimer(void);

inline void quiet(void);
void setToneFreq(uint16_t f_Hz);

void setFreqAlarmHandler(void* freq_uint16_ptr);

void playTone(uint16_t f_Hz, time_ms_t dur_ms);


#endif /* AVRTONE_H */
