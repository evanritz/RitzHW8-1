#!/bin/bash
echo "Configuring GPIO pins..."
config-pin -a p9.12 out
config-pin -a p8.16 in+ 
echo "Configured GPIO pins"
echo "Compiling control_GPIO.cpp..."
g++ -Wall control_GPIO.cpp -o control_GPIO
echo "Finished"
