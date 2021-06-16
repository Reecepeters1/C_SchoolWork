#!/usr/bin/bash

date
VAR1=0
while [ $VAR1 -lt 10000 ]
do
    ./genfuzz > tmp
    ./tricheck < tmp
    X=$?  # exit code from myapp
    if [ $X != 0 ]
    then
        echo "bad result"
    fi
    VAR1=`expr $VAR1 + 1`
done
date
