# Bash Exercise Solution — Numeric vs String Comparison

This repository contains two Bash solutions for the same exercise.

Both versions:

- Read integer values from an input file.
- Process the values in groups of three.
- Compute:

```text
f(x, y, z) = 3x² + 4y + 5z
```

- Print the final result for each triple.

The only difference between the two versions is how `counter` is compared:

- **Version 1** uses numeric comparison with `-eq`.
- **Version 2** uses string comparison with `=`.

---

## Version 1 — Numeric Comparison with `-eq`

```bash
#!/bin/bash

counter=1

for numbers in $(cat "$1")
do
    if [ "$counter" -eq 1 ]
    then
        let result=numbers*numbers*3

    elif [ "$counter" -eq 2 ]
    then
        let result=result+4*numbers

    elif [ "$counter" -eq 3 ]
    then
        let result=result+5*numbers

        echo "the final result is $result"

        result=0
        counter=0
    fi

    let counter=counter+1
done

exit 0
```

---

## Version 2 — String Comparison with `=`

```bash
#!/bin/bash

counter=1

for numbers in $(cat "$1")
do
    if [ "$counter" = "1" ]
    then
        let result=numbers*numbers*3

    elif [ "$counter" = "2" ]
    then
        let result=result+4*numbers

    elif [ "$counter" = "3" ]
    then
        let result=result+5*numbers

        echo "the final result is $result"

        result=0
        counter=0
    fi

    let counter=counter+1
done

exit 0
```

---

## Difference Between the Two Versions

### Numeric comparison

```bash
[ "$counter" -eq 1 ]
```

Use `-eq` when comparing numbers.

### String comparison

```bash
[ "$counter" = "1" ]
```

Use `=` when comparing strings.

Since `counter` is being used as a number in this script, the numeric comparison with `-eq` is the more appropriate choice.

---

## Example Usage

Make the script executable:

```bash
chmod +x script.sh
```

Run it with an input file:

```bash
./script.sh input.txt
```

Example `input.txt`:

```text
1 1 2
2 1 3
1 3 4
```

Example output:

```text
the final result is 17
the final result is 31
the final result is 35
```
