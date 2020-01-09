#!/bin/bash

for N in {1..5}
do
	for M in {1..5}
	do 
		ruby client.rb $M &
	done

done
wait
