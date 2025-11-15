#!/bin/bash

./gameoflife 30 30 50 0.2 1 > current.out

diff validation_set.out current.out > /dev/null

if [ $? -eq 0 ]; then
    echo "OK"
else
    echo "MISMATCH"
    diff validation_set.out current.out | head -n 20
fi

