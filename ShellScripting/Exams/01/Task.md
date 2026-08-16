# Exam — 2020/06/16

Given a file named `file.txt` containing some words (i.e., sequences of alphabetic characters separated by spaces, even on multiple lines) with content similar to the following:

```text
one two three
four five six
seven
```

Implement a Bash script that prints the word with the longest length.

Given the previous example, the script must print in output the word `three` or the word `seven`, because both have 5 characters.

## Challenge 1

If two or more words have the same maximum length, print the word that comes first in **reverse alphabetical order**.

For example, in the previous input, both `three` and `seven` have 5 characters. Since `three` comes before `seven` in reverse alphabetical order, the script should print:

```text
three
```

## Challenge 2

Read the file **line by line** and print the line with the longest length.

For example, given the following content:

```text
one two
three four five
six seven
```

the script should print:

```text
three four five
```

## Challenge 3

Read the file **line by line** and print every line that contains the word `five`.

For example, given the following content:

```text
one two
three four five
six seven
five eight nine
```

the script should print:

```text
three four five
five eight nine
```

