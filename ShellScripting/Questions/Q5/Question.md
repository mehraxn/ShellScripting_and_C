# Bash Exercise — Generate a Horizontal Histogram

## Task

Write a Bash script that receives the name of a file from the command line, reads a sequence of integer values from that file, and displays a **horizontal histogram** using the `*` character.

Each integer in the input file represents the value of one histogram bin.

For every integer value `n`, the script must print exactly `n` asterisks on one line.

---

## Input

The filename must be provided as the first command-line argument.

Example:

```bash
./script.sh data.txt
```

In this case:

```text
$1 = data.txt
```

The input file contains a sequence of integer numbers.

Example `data.txt`:

```text
1
3
5
4
2
```

Each number represents the size of one histogram bar.

---

## Expected Output

For the example input:

```text
1
3
5
4
2
```

the script must display:

```text
*
***
*****
****
**
```

This means:

```text
1 -> *
3 -> ***
5 -> *****
4 -> ****
2 -> **
```

Each input value produces **one horizontal histogram bar**.

---

## Requirements

Your Bash script must:

- Receive the input filename from the command line.
- Access the filename through the first positional parameter, `$1`.
- Read the integer values stored in the file.
- Process each integer individually.
- Treat each integer as the length of one histogram bar.
- Print one `*` character for each unit of the corresponding integer value.
- Print each histogram bar on a separate line.
- Preserve the same order as the values in the input file.

---

## Example

### Input File

```text
1
3
5
4
2
```

### Output

```text
*
***
*****
****
**
```
