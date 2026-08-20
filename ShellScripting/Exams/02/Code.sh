#!/bin/bash

i=0
j=0
line=""
counter=0

if [ $# -ne 1 ]
then
    echo "Error: one argument is required"
    exit 1
fi

while read line
do
    i=0

    for words in $line
    do
        if [ $i -eq $j ]
        then
            let counter=counter+${#words}
        fi

        let i=i+1
    done

    let j=j+1
done < "$1"

echo "the number of the length of the words on the diagonal is $counter"
