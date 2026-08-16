#!/bin/bash

final_length=0
final_word=""

for words in $(cat $1)
do
    temp_length=${#words}

    if [ $temp_length -gt $final_length ]
    then
        final_length=$temp_length
        final_word=$words
    fi
done

echo "$final_word"
