Example test programs
=====================

Each of the subdirectories inside this one contain a small example application, supposed to test a
**combination** of libraries from different layers of abstraction.

For each subdirectory, you can find a Makefile inside of it. All makefiles are based on the exact same
template and work similarly:

* **To compile the application:** Type "make". To clean all generated files type "make clean"

* **To program your AVR device with the executable image:** Simply type `make writeflash` at the command-line.
You might want to take a look at the Makefile to change options such as the model of your programmer and
the baud rate at which to do the programming. The Makefiles are pretty well-documented and you'll easily find
these options.

* **To simulate the program and generate waveform output:** Type
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

