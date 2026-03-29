#!/bin/bash
dir=$1
cd $dir
arduino-cli compile --fqbn arduino:renesas_uno:unor4wifi .
arduino-cli upload   --fqbn arduino:renesas_uno:unor4wifi   -p /dev/ttyACM0   .
cd ../