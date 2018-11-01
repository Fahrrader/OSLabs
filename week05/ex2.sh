#!/bin/bash
while true
do
	while ! ln input.txt input.lock 2>/dev/null 
	do
	    sleep 1
	done
	value = $(tail -1 input.txt)
	result = $(expr $value + 1)
	echo $result >> input.txt
	rm -f input.lock
done