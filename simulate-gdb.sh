#/bin/sh

SIMULATION_VCD=sim.vcd

simulavr -f $3 -d $1 -F ${2}000000 -c vcd:traces-selected:$SIMULATION_VCD -g -B ${4}

sudo mkdir -p /tmp/avrproj
sudo mv $SIMULATION_VCD /tmp/avrproj/
sudo chmod -R 777 /tmp/avrproj
