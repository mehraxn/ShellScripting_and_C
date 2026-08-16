#!/bin/bash

final_length=0
final_line=""

while read line
do
    temp_length=${#line}

    if [ $temp_length -gt $final_length ]
    then
        final_length=$temp_length
        final_line="$line"
    fi
done < $1

echo "$final_line"
