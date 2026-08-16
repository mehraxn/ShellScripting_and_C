#!/bin/bash
# Exam 2020/06/16 - Exercise 4

longest_word=""
length_longest=0
# Scan the file word by word
for word in $(cat file.txt) do
        # Detect the length of $word
        length=$(echo $word|wc -c)
        #length=${#word} # Other possibility
        if [ $length -gt $length_longest ] then
                length_longest=$length
                longest_word=$word
        fi
done
echo $longest_word
