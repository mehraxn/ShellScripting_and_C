# Exam — 2021/06/18

## Exercise

Write a Bash script able to compute the **sum of the lengths of the words appearing on the diagonal of a square matrix** that contains only strings.

The square matrix is stored in a text file specified as a **command-line argument** to the script.

The script must also check that the argument has been correctly passed.

## Example

Given the following matrix:

```text
word11 word12 word13 word14
word21 word22 word23 word24
word31 word32 word33 word34
word41 word42 word43 word44
```

The words on the main diagonal are:

```text
word11
word22
word33
word44
```

Each word has 6 characters, so the expected result is:

```text
24
```
