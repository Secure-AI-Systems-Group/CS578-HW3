#!/bin/bash

PWD=(`pwd`)
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD

# run flush+reload monitoring
./attack traces &

# delay before the victim starts 
sleep 1

# run the victim code
./multiply
