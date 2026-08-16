#!/bin/bash

counter=0
line=""
flag=0
dimension=0

while read line
do
    counter=0

    for word in $line
    do
        counter=$((counter + 1))
    done

    echo "$counter"

done < "$1"
