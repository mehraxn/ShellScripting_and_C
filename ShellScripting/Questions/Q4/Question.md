# Bash Exercise — Display a File Line by Line and Word by Word

## Task

Write a Bash script that receives the name of a file from the command line and displays the content of that file in **two different ways**:

1. **Line by line**, with a line number printed before each line.
2. **Word by word**, with a word number printed before each word.

The filename must be provided to the script as a **command-line argument** and accessed through a positional parameter.

---

## Input

The script must receive the filename as its first command-line argument.

Example:

```bash
./script.sh data.txt
```

In this case:

```text
$1 = data.txt
```

Assume `data.txt` contains:

```text
hello world
Operating Systems
Bash is fun
```

---

## Part 1 — Display the File Line by Line

Read the file **one complete line at a time**.

For every line:

- Start numbering from `1`.
- Print the line number.
- Print the complete line after the number.
- Increase the line counter after each iteration.

For the example input, the output of this part should be:

```text
1: hello world
2: Operating Systems
3: Bash is fun
```

A line containing several words must still be treated as **one line**.

---

## Part 2 — Display the File Word by Word

After finishing the line-by-line processing, process the same file again **one whitespace-separated word at a time**.

For every word:

- Restart the counter from `1`.
- Print the word number.
- Print the current word after the number.
- Increase the counter after each word.

For the example input, the output of this part should be:

```text
1: hello
2: world
3: Operating
4: Systems
5: Bash
6: is
7: fun
```

---

## Requirements

Your script must:

- Use Bash.
- Receive the filename from the command line.
- Access the filename using the first positional parameter, `$1`.
- Read the file once **line by line**.
- Number each line starting from `1`.
- Read the same file again **word by word**.
- Number each word starting from `1`.
- Reset the counter before beginning the word-by-word section.
- Display both numbered results on standard output.

---

## Expected Behavior

Given:

```text
hello world
Operating Systems
Bash is fun
```

the script should first produce:

```text
1: hello world
2: Operating Systems
3: Bash is fun
```

and then produce:

```text
1: hello
2: world
3: Operating
4: Systems
5: Bash
6: is
7: fun
```

The two parts are independent:

```text
First part  -> one iteration per line
Second part -> one iteration per word
```
