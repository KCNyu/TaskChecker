#!/bin/bash

cd ../
./recomplie.sh

cd sample
for ((i = 1; i <= 9; i++)); do
	taskchecker -t D$i
	taskchecker -t D$i -l ch
done
