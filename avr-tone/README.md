AVR Tone Generation Library
===========================
This is the AVR Tone Generation Library (libavr-tone.a). It provides functions to help setup the timers
used for wave generation, along with functions to play sounds of a defined duration and frequency.

Public API
----------
These are the functions that the user of avr-tone should know about:

### void initOutput(void)
This function sets up the output pins for the sound signal. It should be called first thing in the
application, before any calls to `playTone`.

### void initToneTimer(void)
Initializes the timer used for sound signal generation. This is **different** from the initialization of the
transmission backend, and must be done only **after** it. For example, when using `avr-am` as a backend, you
must first call `initCarrierTimer` and **only then** `initToneTimer`.

### void playTone(uint16_t f_Hz, uint16_t dur_ms)
This function receives as parameters the frequency (in Hertz) of the sound wave to be generated, and the
duration of this sound. IMPORTANT: This function is asynchronous, i.e, it **doesn't block while the tone is
played**. The `playTone` function adds the requested tone to the play queue and returns immediately, leaving
the AVR free to do other (parallel) processing. Because of some limitations of most AVR MCU's, the following
restrictions apply when calling this function:

* *f_Hz* better be bellow some 5000Hz. Otherwise, undefined behavior (with probably lots of aliasing) ensues.
* *dur_ms* better be less then or equal to 6000 (6 seconds). I cannot guarantee anything higher than that...

Important remark
----------------
The avr-tone library is heavily interrupt-driven. So you **must** have global interrupts enabled when using
avr-tone. The recommended procedure is to call `sei` just before starting the calls to `playTone`.
