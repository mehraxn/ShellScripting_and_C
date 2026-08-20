#!/bin/bash

if [ $# -ne 4 ]
then
    echo "Usage: $0 dir1 dir2 dir3 n"
    exit 1
fi

if [ ! -d "$1" ] || [ ! -d "$2" ]
then
    echo "The first two arguments do not fulfill the conditions!"
    exit 1
fi

if [ ! -d "$3" ]
then
    mkdir "$3"
fi

file_A=$(ls "$1")
file_B=$(ls "$2")

tracker=()
i=0

for var1 in $file_A
do
    if [[ "$var1" != *.txt ]]
    then
        continue
    fi

    for var2 in $file_B
    do
        if [ "$var1" = "$var2" ]
        then
            tracker[$i]="$var1"
            ((i++))
        fi
    done
done

for file in "${tracker[@]}"
do
    name="${file%.txt}"

    n1=$(wc -l < "$1/$file")
    n2=$(wc -l < "$2/$file")

    if [ "$n1" -gt "$4" ] && [ "$n2" -gt "$4" ]
    then
        while read line
        do
            grep -q -e "^$line$" "$2/$file"

            if [ $? -eq 0 ]
            then
                echo "$line" >> "$3/${name}.eq"
            else
                echo "$line" >> "$3/${name}.dif"
            fi
        done < "$1/$file"

        while read line
        do
            grep -q -e "^$line$" "$3/${name}.eq"

            if [ $? -eq 1 ]
            then
                echo "$line" >> "$3/${name}.dif"
            fi
        done < "$2/$file"

        cat "$1/$file" "$2/$file" > "$3/${name}.cat"
    fi
done
