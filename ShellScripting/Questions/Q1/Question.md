# Bash Exercise — Process Integer Triples from a File

## Objective

Write a Bash script that reads integer values from an input file in groups of three and evaluates the function

```text
f(x, y, z) = 3x² + 4y + 5z
```

for each triple.

## Task

The input file contains integers arranged as triples:

```text
x y z
```

Your script must:

- Receive the input filename as a command-line argument.
- Read all values from the file.
- Process the values three at a time as `x`, `y`, and `z`.
- Compute `f(x, y, z) = 3x² + 4y + 5z` for each triple.
- Print the result of each computation.

## Example Input

Suppose `input.txt` contains:

```text
1 1 2
2 1 3
1 3 4
```

The triples are:

```text
(1, 1, 2)
(2, 1, 3)
(1, 3, 4)
```

## Expected Output

```text
17 31 35
```

## Running the Script

The script should be executable as:

```bash
./script.sh input.txt
```

where `input.txt` is the file containing the integer triples.

## Requirements

- Use Bash.
- Obtain the filename from a command-line argument.
- Read the input values from that file.
- Process the values in groups of three.
- Produce one result for each triple.
