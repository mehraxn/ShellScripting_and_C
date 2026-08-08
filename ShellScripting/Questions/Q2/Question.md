# Bash Exercise — Filter and Display Matching C Files

## Task

Write a Bash script that displays the **contents of all `.c` files in the current directory that contain the string `POSIX`**.

## Requirements

Your script must:

- Look only at files in the **current directory**.
- Consider only files with the **`.c` extension**.
- Check whether each `.c` file contains the string:

```text
POSIX
```

- Display the **entire content** of every `.c` file that contains that string.

## Example

Suppose the current directory contains:

```text
main.c
test.c
hello.c
notes.txt
```

and only `main.c` and `hello.c` contain the string `POSIX`.

Your script should display the contents of:

```text
main.c
hello.c
```

and ignore:

```text
test.c
notes.txt
```
