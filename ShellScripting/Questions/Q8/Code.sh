#!/bin/bash

counter=0
line=""


while read line
do
    counter=0

    for word in $line
    do
        counter=$((counter + 1))
    done

    echo "$counter"

done < "$1"
