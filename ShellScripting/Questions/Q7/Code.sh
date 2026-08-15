#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage $0 <source> <destination>"
    exit 1
fi

if [ ! -f $1 ]; then
    echo "Source is not a valid file."
    exit 1
fi

if [ ! -d $2 ]; then
    echo "Destination is not a valid directory."
    exit 1
fi

source=$1
destination=$2

size=$(ls -l $source | cut -d " " -f 5)
let "size=size/1024"

startUsed=$(df $destination | \
            tail -n 1 | \
            tr -s " " | \
            cut -d " " -f 3)

cp $source $destination &

transferred=0
percentage=0

while [ $transferred -lt $size ]; do

    currentUsed=$(df $destination | \
                  tail -n 1 | \
                  tr -s " " | \
                  cut -d " " -f 3)

    let "transferred=currentUsed-startUsed"
    let "percentage=transferred*100/size"

    echo "Progress: $percentage%"

    sleep 1
done
