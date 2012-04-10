#!/bin/sh

INPUT_FILE=$1
OUTPUT_FILE=`dirname $INPUT_FILE`/`basename $INPUT_FILE .out`.hex

avr-objcopy -O ihex  $INPUT_FILE  $OUTPUT_FILE

sudo mkdir -p /tmp/avrproj
sudo mv $OUTPUT_FILE /tmp/avrproj/
sudo chmod -R 777 /tmp/avrproj
