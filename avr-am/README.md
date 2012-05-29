AVR-AM: Transmit signals over Amplitude-Modulated radio waves
=============================================================

This library takes as input a square-wave signal and performs amplitude modulation on it, outputting the
already-modulated carrier wave on pin 0 of PORTB. It is of great importance to have in mind that the generated
carrier is **also square** and relatively low-power.

The power of the transmission is the power of the output pin of the microcontroller itself. Furthermore,
the square carrier generated has a quite spread spectrum, which means that the low-frequency (senoidal)
component - the one that your radio "listens to" - has only a **small part** of the original carrier's power.
These two characteristics combined mean that you have to hold the antenna of your radio **very** close to the
AVR to be able to hear anything. Of course, if you're not so purist, you can always add a transistor to the
output to amplify it. Just please don't amplify it too much or else you might go to jail :P

What's this lib made of?
------------------------
Well, our whole approach to wave generation in avr-wavegen is based on timers and interrupt-driven
computations. The way by which we make a square signal modulate an underlying (higher-freq) square carrier is
to *turn the carrier on* when a *rising edge* happens in the signal, and *turn the carrier off* when a
*falling edge* happens in the signal. To take care of generating the carrier and modulating it, avr-am has
**two interrupt handlers** in src/toggle.c:

1. **TIMER0\_COMPA\_vect:** is activated with twice the desired frequency of the carrier. That because we
   assume that the duty-cycle is 50% (such flexibility is too expensive as the handler must have ideally a
   couple of instructions). Each time this ISR is called, we toggle pin 0 of PORTB (one instruction).

2. **TIMER2\_COMPA\_vect:** is called with twice the frequency of the sound signal requested by the client
   generation library. This function just enables and disables TIMER0 counting, effectively "toggling" the
   carrier. We could easily implement variable duty-cycle in the sound signal - resulting in variable sound
   volume (through PWM). I just didn't do it yet 'cause I'm lazy :)

Initializing and configuring AM playback
----------------------------------------
AVR-AM gives you the possibility to choose which carrier frequency you want to use for your humble radio
transmitter, by using the functions declared in avr-am/config.h. The code snippet below shall give you a
really good idea of how to use avr-am:

    #include <avr/interrupt.h>
    #include <avr-am/config.h>
    #include <avr-tone/avr-tone.h> // or any other sound signal generation lib
    
    initOutput(); // this is from avr-tone
    initCarrierTimer(); // this is from avr-am
    initToneTimer(); // this is from avr-tone

    setCarrierFreqKHz(650); // or any of your favorite frequencies (in KHz)
    sei(); // enable global interrupts, we need it for all timers to work

    playTone(...); // play you favorite sounds :)


Installing and using in applications
------------------------------------
As with all other component libraries of [avr-wavegen](https://github.com/joaopizani/avr-wavegen), you can
compile and install avr-am at a certain PREFIX in your filesystem by just typing

    make install PREFIX=[prefix]

To use avr-am in an application, you must link your application with the static lib file (libavr-am.a)
found under $PREFIX/lib. In the case that you are using a Makefile from avr-wavegen as a template for the
Makefile in your application - or using the Makefile template from
[avr-utils](https://github.com/joaopizani/avr-utils) - then you can just add the following to your paths.def:

    AVRAM_ROOT=[path to PREFIX where you installed avr-am]
    AVRAM_INCLUDE=${AVRAM_ROOT}/include
    AVRAM_LIBS=${AVRAM_ROOT}/lib/avr-am
    AVRAM_INCFLAGS=-I${AVRAM_INCLUDE}
    AVRAM_LIBFLAGS=-Wl,--whole-archive -L${AVRAM_LIBS} -lavr-buzzer -Wl,--no-whole-archive

Observation: the *-Wl,--whole-archive* and *-Wl,--no-whole-archive* options are needed because the library
mainly consists of interruption handlers, which wouldn't otherwise be linked in. Finally, you should
append AVRAM\_INCFLAGS and AVRAM\_LIBFLAGS, respectively, to the variables EXT\_INCFLAGS and EXT\_LIBFLAGS,
which should be present at the end of your paths.def. Like this:

    EXT_INCFLAGS=${LIB1_INCFLAGS} ${LIB2_INCFLAGS} ${AVRAM_INCFLAGS} ...
    EXT_LIBFLAGS=${LIB1_LIBFLAGS} ${LIB2_LIBFLAGS} ${AVRAM_LIBFLAGS} ...

