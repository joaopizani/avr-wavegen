AVR-Wavegen: The Humble AVR Sound Library Suite
===============================================

Introduction
------------
Thanks for your interest! This repo is a collection of related static libraries (pieces of software intended
to be used as .a archives) that generate and manipulate square wave sounds in AVR microcontrollers. More
specifically, our goal is to **generate** sound signals, **transmit** them in a number of ways and **use**
these signals in yet another number of ways...

For example, you can produce sounds of a given frequency and duration, and transmit them through AM radio or
output them directly with a buzzer. These sounds can be Morse code, Nokia® composer-like tunes, DTMF tones,
etc.


Component libraries
-------------------
The `avr-wavegen` library collection is conceptually organized in 3 "layers" (event though up until now we only
have components in the lower two). These layers are (from the bottom up):

1. **Transmission:** The lowest layer is responsible for transmitting the sound signal using some medium. The
   simplest way to do transmission is just using a buzzer, but you can also transmit your sound waves using
   Amplitude Modulated (AM) radio in some carrier frequency. The transmission libs available as of now are
   `avr-am` and `avr-buzzer`.

2. **Generation:** The middle layer generates the sound signal itself, that is, a square wave whose frequency
   corresponds to the perceived pitch of the sound :). As of now, the only library in this layer is
   `avr-tone`, which generates tones of a given frequency and duration. But further generation libs could be
   integrated in the future - for example to generate noise-like or percussion-like signals.

3. **Composition:** The topmost layer consists of libraries that use the sound signal generation facilities of
   layer 2 to convey information meaningful for human beings (or machines). Although we still have no libs
   implemented in this layer, we can give examples of Morse code, DTMF tones, Video-game music interpreters,
   and so on...


Compiling, installing and testing
---------------------------------
Besides the respective subdirectories for all libraries, this repository also contains a directory called
`integration-tests` containing small example applications - each of them designed to test the combined
functionality of a set of libraries.

### Compiling the libraries and test applications
The Makefiles of all libraries - as well as of all test applications - are very similar to each other. In
fact they are all based on the same Makefile template, which can be found in the root of the
[avr-utils](https://github.com/joaopizani/avr-utils) repository. Therefore, for all component libraries, the
compilation steps remain the same:

1. Enter the library directory and edit the `paths.def` with paths to the dependencies of that lib (if any).
   Obs: it should not be necessary to edit the paths.def for libs that come pre-bundled with the avr-wavegen 
2. Type `make` to compile the sources and create the .a file.
3. Then type `make install PREFIX=\<favorite-dir\>` to install the lib to your favorite directory. You can
   also directly type `make install PREFIX=\<favorite-dir\>` if you are feeling lucky...

### Programming your AVR device or performing simulation
You can compile a test application with the exact same steps 1 to 2 above. But instead of "installing" the
application, you'll probably want to send it to your development board, or to simulate it.

**To program your AVR device with the executable image:** Simply type `make writeflash` at the command-line.
You might want to take a look at the Makefile to change options such as the model of your programmer and
the baud rate at which to do the programming. The Makefiles are pretty well-documented and you'll easily find
these options.

**To simulate the program and generate waveform output:** Type
`make simulate-vcd SIM_TIME=\<t\> SIM_TRACES=\<pins-file\>` to simulate the program under simulavr and
generate tracing output to a VCD file for later analysis. You must provide the maximum simulation time in
miliseconds and a text file (`pins-file`) containing the names of the pins you want to trace (to obtain a
file with all traceable pins for a device use `simulavr -d \<device-name\> -o \<filename\>`). There are
reasonable defaults for these values, so if you'd like to trust us, you can just use `make simulate-vcd` and
you'll have a simulation of 200ms, tracing the values specified in sim/\<project-name\>-traces and storing the
waveforms in sim/\<project-name\>-waves.vcd.

**To simulate the program and debug it in AVR-GDB:** Just type `make simulate-gdb` at the command-line.
Simulavr will run the application and then AVR-GDB will be launched, will connect itself to the running
Simulavr and stop at the beginning of the `main` function. Simulavr runs in the background, therefore its
stdout and stderr are redirected to files. These files are, respectively, sim/\<project-name\>-sim-stdout.txt
and sim/\<project-name\>-sim-stderr.txt.
