#!/bin/bash

for N in {1..5}
do
	for M in {1..5}
	do 
		ruby client-0.rb $((($N % 6)+ 1)) &
	done

done
wait
