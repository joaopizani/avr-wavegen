AVR-Tone Sound Signal Generation Library
========================================
This is the AVR Tone Generation Library (libavr-tone.a). It provides functions to help setup the timers
used for wave generation, along with functions to play tones of a **defined duration and frequency**.


What's this all about
---------------------
AVR-Tone is characterized in the framework of [avr-wavegen](http://github.com/joaopizani/avr-wavegen) and a
**signal generation** library, that is, a library which main responsibility is to generate a (square) sound
signal. But there are A LOT of ways to make square-wave sounds, and avr-tone certainly takes a very specific
approach: It generates tones of a defined frequency and duration.

"Well, but ALL sounds have a defined frequency and duration!" you might argue. Well, not all, actually: we
could have (and will probably have) generation libraries that produce:

 - All sorts of noises (white noise, "brown" noise, "pink" noise, etc.).
 - Periodic "beats" and other percussive sounds. The important thing here is the **rhythm** of the beat,
   rather than their frequency or the duration of each beat by itself.
 - More fancy functions of frequency vs. time such as, for example, sounds like the siren of a police car :)


AVR-Tone as a "model" and the interface that all sound generation libs must follow
----------------------------------------------------------------------------------
AVR-Tone is just, therefore, a first and small step in the direction of a whole array of sound generation libs
that might come. The **interface that all sound generation libs must follow**, however, is simple: they must
generate the sound signal **by using TIMER2 compare match interrupts**, that is, by making *TIMER2 trigger
its compare match interrupts when rising and falling edges are to happen in the sound signal*.

A clever generation lib might even use **distinct** compare match interrupts (COMPA and COMPB) to trigger
the rise and fall of the sound wave, this way resulting in variable perceived volume by the listener
through PWM. AVR-Tone just doesn't allow this **yet** :)


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

### void playTone(uint16\_t f\_Hz, uint16\_t dur\_ms)
This function receives as parameters the frequency (in Hertz) of the tone to be generated, and the
uration of this tone. IMPORTANT: This function is asynchronous, i.e, it **doesn't block while the tone is
played**. The `playTone` function adds the requested tone to a *play queue* and returns immediately, leaving
the AVR free to do other (parallel) processing. Because of some limitations of most AVR MCU's, the following
restrictions apply when calling this function:

 * *f_Hz* better be bellow some 4000Hz. Otherwise, undefined behavior (with probably lots of aliasing)
   ensues. This is because tone generation, along with transmission and user-code timing requirements
   might just be too much for our poor AVR's to handle (too much instruction throughput) :(
 * *dur_ms* better be less then or equal to 6000 (6 seconds). I can't guarantee anything higher than that.


Important remark
----------------
The avr-tone library is heavily interrupt-driven. So you **must** have global interrupts enabled when using
avr-tone. The recommended procedure is to call `sei()` (from `avr/interrupt.h`) just before starting the
calls to `playTone`.


Installing and using in applications
------------------------------------
As with all other component libraries of [avr-wavegen](https://github.com/joaopizani/avr-wavegen), you can
compile and install avr-tone at a certain PREFIX in your filesystem by just typing

    make install PREFIX=[prefix]

To use avr-tone in an application (or other library), you must add the path of avr-tone's headers to the
compiler's include path, and link your application with the static lib file (libavt-tone.a)
found under $PREFIX/lib. In the case that you are using a Makefile from avr-wavegen as a template for the
Makefile in your application - or using the Makefile template from
[avr-utils](https://github.com/joaopizani/avr-utils) - then you can just add the following to your paths.def:
``` bash
    AVRTONE_ROOT=[path to PREFIX where you installed avr-tone]
    AVRTONE_INCLUDE=${AVRAM_ROOT}/include
    AVRTONE_LIBS=${AVRAM_ROOT}/lib/avr-tone
    AVRTONE_INCFLAGS=-I${AVRTONE_INCLUDE}
    AVRTONE_LIBFLAGS=-L${AVRTONE_LIBS} -lavr-tone
```

Finally, you should append AVRTONE\_INCFLAGS and AVRTONE\_LIBFLAGS, respectively, to the variables
EXT\_INCFLAGS and EXT\_LIBFLAGS, which should be present at the end of your paths.def. Like this:
``` bash
    EXT_INCFLAGS=${LIB1_INCFLAGS} ${LIB2_INCFLAGS} ${AVRAM_INCFLAGS} ...
    EXT_LIBFLAGS=${LIB1_LIBFLAGS} ${LIB2_LIBFLAGS} ${AVRAM_LIBFLAGS} ...
```

