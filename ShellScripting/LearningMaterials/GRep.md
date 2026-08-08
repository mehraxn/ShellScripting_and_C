# `grep` in Bash — Complete Standalone Guide

`grep` is one of the most important text-processing commands in Linux and Bash scripting.

It is used to **search for text patterns** inside files or inside the output of other commands.

---

## 1. What Does `grep` Do?

The basic idea is:

> `grep` reads text, looks for lines that match a pattern, and prints the matching lines.

Basic syntax:

```bash
grep "pattern" file
```

Example:

```bash
grep "POSIX" main.c
```

This means:

> Search inside `main.c` for lines containing the text `POSIX`.

Suppose `main.c` contains:

```c
#include <stdio.h>

/* This program uses POSIX functions */

int main() {
    return 0;
}
```

Then:

```bash
grep "POSIX" main.c
```

prints:

```text
/* This program uses POSIX functions */
```

---

# 2. `grep` Searches Inside File Content

A very important distinction:

```bash
grep "POSIX" main.c
```

searches **inside the contents of `main.c`**.

It is not checking whether the filename contains `POSIX`.

For example:

```text
main.c
```

can match if its content contains:

```text
POSIX
```

even though the filename itself does not contain the word `POSIX`.

---

# 3. Basic Syntax

General form:

```bash
grep [OPTIONS] "PATTERN" FILE
```

For example:

```bash
grep "hello" notes.txt
```

Here:

- `grep` → command
- `"hello"` → text/pattern to search for
- `notes.txt` → file to search inside

---

# 4. Simple Example

Suppose `file.txt` contains:

```text
hello world
Linux is useful
hello Bash
Operating Systems
```

Run:

```bash
grep "hello" file.txt
```

Output:

```text
hello world
hello Bash
```

Only the matching lines are printed.

---

# 5. Case Sensitivity

By default, `grep` is **case-sensitive**.

Suppose:

```text
POSIX
Posix
posix
```

Then:

```bash
grep "POSIX" file.txt
```

matches only:

```text
POSIX
```

To ignore uppercase/lowercase differences, use:

```bash
grep -i "POSIX" file.txt
```

Now all of these match:

```text
POSIX
Posix
posix
```

---

# 6. Search in More Than One File

You can search multiple files at once.

```bash
grep "POSIX" file1.c file2.c file3.c
```

You can also use a wildcard:

```bash
grep "POSIX" *.c
```

This means:

> Search for `POSIX` inside all `.c` files in the current directory.

Suppose the current directory contains:

```text
main.c
test.c
hello.c
notes.txt
```

Then:

```bash
grep "POSIX" *.c
```

searches:

```text
main.c
test.c
hello.c
```

but not:

```text
notes.txt
```

---

# 7. `grep` with Wildcards

In:

```bash
grep "POSIX" *.c
```

the `*.c` part is a **shell wildcard**.

It means:

> all filenames ending in `.c`

The shell expands it before `grep` runs.

For example:

```bash
grep "POSIX" *.c
```

may become:

```bash
grep "POSIX" main.c test.c hello.c
```

Important:

- `*.c` is a **filename wildcard**
- `"POSIX"` is the **text pattern searched inside the files**

These are two different kinds of matching.

---

# 8. Print Line Numbers with `-n`

Use:

```bash
grep -n "POSIX" file.c
```

Suppose:

```text
line 1
line 2
POSIX example
line 4
```

Output:

```text
3:POSIX example
```

The `3` means the match was found on line 3.

---

# 9. Ignore Case with `-i`

```bash
grep -i "posix" file.c
```

This can match:

```text
POSIX
Posix
posix
PoSiX
```

---

# 10. Show Lines That Do NOT Match with `-v`

Use:

```bash
grep -v "POSIX" file.c
```

This means:

> Print every line that does **not** contain `POSIX`.

Example input:

```text
hello
POSIX system
Linux
POSIX API
```

Output:

```text
hello
Linux
```

---

# 11. Count Matching Lines with `-c`

Use:

```bash
grep -c "POSIX" file.c
```

Suppose the file contains:

```text
POSIX
hello
POSIX example
world
POSIX API
```

Output:

```text
3
```

This means 3 lines matched.

---

# 12. Print Only Matching Filenames with `-l`

Use:

```bash
grep -l "POSIX" *.c
```

This does **not** print the matching lines.

It prints only the names of files containing at least one match.

Suppose:

```text
main.c   → contains POSIX
test.c   → does not contain POSIX
hello.c  → contains POSIX
```

Then:

```bash
grep -l "POSIX" *.c
```

outputs:

```text
main.c
hello.c
```

This is especially useful when you only care about **which files match**.

---

# 13. Print Files That Do NOT Match with `-L`

Use:

```bash
grep -L "POSIX" *.c
```

If:

```text
main.c   → contains POSIX
test.c   → does not contain POSIX
hello.c  → contains POSIX
```

then the output is:

```text
test.c
```

---

# 14. Quiet Mode with `-q` or `--quiet`

Use:

```bash
grep -q "POSIX" file.c
```

or:

```bash
grep --quiet "POSIX" file.c
```

This searches for `POSIX`, but it prints **nothing**.

Why is that useful?

Because sometimes we only want to know:

> Was the text found or not?

The answer is stored in the command's **exit status**.

---

# 15. `grep` Exit Status and `$?`

After running a command, Bash stores its exit status in:

```bash
$?
```

For `grep`:

```text
0 → a match was found
1 → no match was found
2 → an error occurred
```

Example:

```bash
grep -q "POSIX" main.c
echo $?
```

If `POSIX` exists:

```text
0
```

If it does not exist:

```text
1
```

This is extremely useful in shell scripting.

Example:

```bash
grep -q "POSIX" main.c

if [ $? -eq 0 ]
then
    echo "POSIX was found"
else
    echo "POSIX was not found"
fi
```

---

# 16. A Cleaner `if grep ...` Form

Instead of writing:

```bash
grep -q "POSIX" main.c

if [ $? -eq 0 ]
then
    echo "Found"
fi
```

Bash can directly use the exit status of `grep`:

```bash
if grep -q "POSIX" main.c
then
    echo "Found"
fi
```

This is shorter and commonly used in real shell scripts.

---

# 17. Example: Search All `.c` Files and Display Matching Files

```bash
#!/bin/bash

for file in *.c
do
    grep -q "POSIX" "$file"

    if [ $? -eq 0 ]
    then
        more "$file"
    fi
done

exit 0
```

Meaning:

1. Take one `.c` file at a time.
2. Search inside it for `POSIX`.
3. If `grep` finds it, its exit status is `0`.
4. Display the whole file with `more`.

---

# 18. Same Example Using `if grep`

A cleaner version:

```bash
#!/bin/bash

for file in *.c
do
    if grep -q "POSIX" "$file"
    then
        more "$file"
    fi
done

exit 0
```

This performs the same task.

---

# 19. `grep -l` as a Shorter Solution

Suppose you want to display the contents of every `.c` file containing `POSIX`.

First:

```bash
grep -l "POSIX" *.c
```

may output:

```text
main.c
hello.c
```

Then:

```bash
more $(grep -l "POSIX" *.c)
```

becomes approximately:

```bash
more main.c hello.c
```

So `more` opens the matching files.

---

# 20. Command Substitution with `grep`

This:

```bash
$(command)
```

means:

> Run the command and substitute its output here.

Therefore:

```bash
$(grep -l "POSIX" *.c)
```

means:

> Get the filenames returned by `grep`.

Example:

```bash
more $(grep -l "POSIX" *.c)
```

If `grep` outputs:

```text
main.c
hello.c
```

then Bash effectively runs:

```bash
more main.c hello.c
```

---

# 21. Difference Between Command Substitution and Pipe

These two commands are **not the same**:

```bash
more $(grep -l "POSIX" *.c)
```

and:

```bash
grep -l "POSIX" *.c | more
```

## First version

```bash
more $(grep -l "POSIX" *.c)
```

If `grep` returns:

```text
main.c
hello.c
```

Bash runs:

```bash
more main.c hello.c
```

So `more` displays the **contents of the files**.

## Second version

```bash
grep -l "POSIX" *.c | more
```

The pipe sends this text:

```text
main.c
hello.c
```

to `more`.

So `more` displays the **filenames themselves**, not their contents.

---

# 22. Search for a Whole Word with `-w`

Suppose a file contains:

```text
cat
catalog
concatenate
```

Run:

```bash
grep "cat" file.txt
```

It can match all three lines because all contain the characters `cat`.

If you want only the complete word `cat`, use:

```bash
grep -w "cat" file.txt
```

Output:

```text
cat
```

---

# 23. Match the Entire Line with `-x`

Suppose:

```text
hello
hello world
say hello
```

Run:

```bash
grep -x "hello" file.txt
```

Output:

```text
hello
```

Only a line that exactly matches the complete pattern is printed.

---

# 24. Print Only the Matching Part with `-o`

Suppose:

```text
user123 logged in
```

Run:

```bash
grep -o "user123" file.txt
```

Output:

```text
user123
```

`-o` means:

> Print only the matched part, not the whole line.

---

# 25. Recursive Search with `-r`

Use:

```bash
grep -r "POSIX" .
```

Meaning:

> Search for `POSIX` in files in the current directory and all subdirectories.

Here:

```text
.
```

means the current directory.

Example structure:

```text
project/
├── main.c
├── test.c
└── src/
    └── worker.c
```

Then:

```bash
grep -r "POSIX" .
```

can search all three files, including `src/worker.c`.

---

# 26. Recursive Search Only in Certain File Types

You can combine recursive search with `--include`.

```bash
grep -r --include="*.c" "POSIX" .
```

Meaning:

> Search recursively for `POSIX`, but only inside `.c` files.

You can also exclude files:

```bash
grep -r --exclude="test.c" "POSIX" .
```

---

# 27. Limit the Number of Matches with `-m`

Use:

```bash
grep -m 2 "POSIX" file.txt
```

This stops after 2 matching lines.

---

# 28. Show Context Around Matches

Sometimes you want to see lines before or after the matching line.

## After the match

```bash
grep -A 2 "POSIX" file.txt
```

Shows the matching line plus 2 lines after it.

## Before the match

```bash
grep -B 2 "POSIX" file.txt
```

Shows 2 lines before the matching line.

## Before and after

```bash
grep -C 2 "POSIX" file.txt
```

Shows 2 lines before and 2 lines after.

---

# 29. `grep` with Standard Input

`grep` does not always need a filename.

It can receive text from another command through a pipe.

Example:

```bash
ls | grep ".c"
```

Meaning:

1. `ls` prints directory entries.
2. `|` sends that output to `grep`.
3. `grep` keeps lines containing `.c`.

Suppose:

```text
main.c
notes.txt
hello.c
image.jpg
```

Output:

```text
main.c
hello.c
```

---

# 30. `grep` with `ps`

Example:

```bash
ps aux | grep "bash"
```

This searches the process list for lines containing `bash`.

---

# 31. `grep` with `cat`

You may see:

```bash
cat file.txt | grep "POSIX"
```

This works, but it is usually unnecessary.

The simpler version is:

```bash
grep "POSIX" file.txt
```

because `grep` can read the file directly.

---

# 32. Basic Regular Expressions

`grep` can search for more than fixed text.

By default, it understands **basic regular expressions**.

## Beginning of line: `^`

```bash
grep "^POSIX" file.txt
```

Matches lines that **start** with `POSIX`.

Example:

```text
POSIX system
```

matches.

But:

```text
This is POSIX
```

does not.

---

## End of line: `$`

```bash
grep "POSIX$" file.txt
```

Matches lines that **end** with `POSIX`.

Example:

```text
This system is POSIX
```

matches.

---

## Any single character: `.`

```bash
grep "c.t" file.txt
```

can match:

```text
cat
cut
cot
```

because `.` means any single character in a regular expression.

Important:

> This `.` is a regular-expression symbol, not a shell wildcard.

---

## Character set: `[ ]`

```bash
grep "gr[ae]y" file.txt
```

matches:

```text
gray
grey
```

---

# 33. Extended Regular Expressions with `-E`

Use:

```bash
grep -E "cat|dog" file.txt
```

This matches lines containing either:

```text
cat
```

or:

```text
dog
```

Example input:

```text
I have a cat
I have a dog
I have a bird
```

Output:

```text
I have a cat
I have a dog
```

---

# 34. Fixed String Search with `-F`

Sometimes you do not want `grep` to interpret special regular-expression characters.

Use:

```bash
grep -F "a.b" file.txt
```

This searches for the literal characters:

```text
a.b
```

instead of interpreting `.` as a regular-expression wildcard.

---

# 35. Why Quotes Are Important

Prefer:

```bash
grep "hello world" file.txt
```

instead of:

```bash
grep hello world file.txt
```

Without quotes, Bash may interpret the words as separate arguments.

Quotes keep the pattern together.

This is especially important when the pattern contains:

- spaces
- `*`
- `$`
- `[ ]`
- other special shell characters

---

# 36. `grep` vs `find`

These commands solve different problems.

## `grep`

```bash
grep "POSIX" file.c
```

Searches **inside file contents**.

## `find`

```bash
find . -name "*.c"
```

Searches for **file and directory names**.

So:

```text
grep → search text inside files
find → search for files/directories
```

---

# 37. `grep` vs `ls`

## `ls`

```bash
ls *.c
```

Lists `.c` filenames in the current directory.

## `grep`

```bash
grep "POSIX" *.c
```

Searches inside those `.c` files for the text `POSIX`.

So:

```text
ls   → list names
grep → search contents
```

---

# 38. Common Useful Options

| Option | Meaning |
|---|---|
| `-i` | Ignore uppercase/lowercase |
| `-n` | Show line numbers |
| `-v` | Show non-matching lines |
| `-c` | Count matching lines |
| `-l` | Print names of matching files |
| `-L` | Print names of non-matching files |
| `-q` | Quiet mode; print nothing |
| `-w` | Match whole words |
| `-x` | Match whole lines |
| `-o` | Print only matched text |
| `-r` | Search recursively |
| `-E` | Use extended regular expressions |
| `-F` | Treat pattern as fixed text |
| `-m N` | Stop after `N` matches |
| `-A N` | Show `N` lines after match |
| `-B N` | Show `N` lines before match |
| `-C N` | Show `N` lines before and after |

---

# 39. Practical Examples

## Find `error` in a log file

```bash
grep "error" app.log
```

## Ignore case

```bash
grep -i "error" app.log
```

## Include line numbers

```bash
grep -n "error" app.log
```

## Count error lines

```bash
grep -c "error" app.log
```

## Search all `.txt` files

```bash
grep "hello" *.txt
```

## Show only filenames containing `TODO`

```bash
grep -l "TODO" *.c
```

## Search recursively

```bash
grep -r "TODO" .
```

## Search recursively only in `.c` files

```bash
grep -r --include="*.c" "TODO" .
```

## Check silently whether a file contains text

```bash
grep -q "POSIX" main.c
```

## Use the result in an `if`

```bash
if grep -q "POSIX" main.c
then
    echo "POSIX found"
else
    echo "POSIX not found"
fi
```

---

# 40. Complete Bash Example

```bash
#!/bin/bash

for file in *.c
do
    if grep -q "POSIX" "$file"
    then
        echo "POSIX found in $file"
        more "$file"
    fi
done

exit 0
```

This script:

1. Finds `.c` files in the current directory.
2. Takes one filename at a time.
3. Searches inside each file for `POSIX`.
4. If a match exists, displays the filename and file contents.

---

# 41. Key Points to Remember

```text
grep "text" file
```

means:

> Search for `text` inside `file`.

```bash
grep "POSIX" *.c
```

means:

> Search for `POSIX` inside all `.c` files in the current directory.

```bash
grep -q "POSIX" file.c
```

means:

> Check whether `POSIX` exists, but print nothing.

```bash
echo $?
```

after `grep` tells you whether a match was found:

```text
0 → found
1 → not found
```

```bash
grep -l "POSIX" *.c
```

means:

> Print only the names of `.c` files containing `POSIX`.

And the most important conceptual distinction is:

```text
ls   → list file/directory names
find → search for file/directory names
grep → search inside text/content
```
