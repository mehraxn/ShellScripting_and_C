# 🔀 Bash Decisions and Loops

A standalone, beginner-friendly guide to **decision making and `for` loops in Bash**.

This README explains:

- `if` statements
- `if / else`
- `elif`
- conditions with `[ ... ]`
- string comparisons
- `for` loop syntax
- iterating over literal values
- iterating over values stored in a variable
- command substitution with `$(...)`
- working with filenames
- a complete image-renaming script
- the output and behavior of every example

All code examples are explained step by step.

---

## 📚 Table of Contents

- [The Basic Idea](#-the-basic-idea)
- [The `if` Statement](#-the-if-statement)
- [Example: Testing a Shell Name](#-example-testing-a-shell-name)
- [The `if / else` Statement](#-the-if--else-statement)
- [Example: `if / else`](#-example-if--else)
- [The `elif` Statement](#-the-elif-statement)
- [Understanding `[ condition ]`](#-understanding--condition-)
- [The `for` Loop](#-the-for-loop)
- [Example: Looping Over Colors](#-example-looping-over-colors)
- [Looping Over Values Stored in a Variable](#-looping-over-values-stored-in-a-variable)
- [Command Substitution in Loops](#-command-substitution-in-loops)
- [Complete Example: Renaming JPG Files](#-complete-example-renaming-jpg-files)
- [A Safer Version of the Rename Script](#-a-safer-version-of-the-rename-script)
- [Common Mistakes](#-common-mistakes)
- [Quick Reference](#-quick-reference)

---

# 🧠 The Basic Idea

Bash scripts normally run commands from top to bottom.

For example:

```bash
echo "Step 1"
echo "Step 2"
echo "Step 3"
```

Output:

```text
Step 1
Step 2
Step 3
```

But often we want the script to make a **decision**:

> Run these commands only if a condition is true.

Or we want to **repeat** commands:

> Run these commands once for every item in a list.

Bash provides structures such as:

```text
if
else
elif
for
```

for these purposes.

---

# ✅ The `if` Statement

The basic form is:

```bash
if [ condition ]
then
    command1
    command2
    commandN
fi
```

You can also write the first two lines on one line:

```bash
if [ condition ]; then
    command1
    command2
fi
```

Both forms mean the same thing.

---

## How it works

Bash evaluates:

```bash
[ condition ]
```

If the condition is **true**, it executes the commands between:

```text
then
```

and:

```text
fi
```

If the condition is **false**, those commands are skipped.

The flow is:

```text
            ┌───────────────┐
            │   condition   │
            └───────┬───────┘
                    │
             ┌──────┴──────┐
             │             │
           true          false
             │             │
             ▼             │
        run commands       │
             │             │
             └──────┬──────┘
                    ▼
               continue
```

---

## Why is it called `fi`?

The block starts with:

```bash
if
```

and ends with:

```bash
fi
```

`fi` is simply:

```text
if
```

written backwards.

It tells Bash:

> The `if` block ends here.

---

# 🐚 Example: Testing a Shell Name

Consider this script:

```bash
#!/bin/bash

MY_SHELL="bash"

if [ "$MY_SHELL" = "bash" ]
then
    echo "You seem to like the bash shell."
fi
```

Output:

```text
You seem to like the bash shell.
```

Now examine it **line by line**.

---

## Line 1

```bash
#!/bin/bash
```

This is the **shebang**.

It tells the operating system to execute this script using the Bash interpreter.

---

## Line 2

```bash
MY_SHELL="bash"
```

This creates a variable named:

```text
MY_SHELL
```

and stores:

```text
bash
```

inside it.

So conceptually:

```text
MY_SHELL → bash
```

---

## Line 3

```bash
if [ "$MY_SHELL" = "bash" ]
```

This is the condition.

First, Bash expands:

```bash
"$MY_SHELL"
```

to:

```text
"bash"
```

Therefore the test becomes conceptually:

```bash
[ "bash" = "bash" ]
```

The operator:

```bash
=
```

compares two **strings**.

Because both strings are the same, the condition is true.

---

## Line 4

```bash
then
```

This means:

> If the condition above was true, execute the following commands.

---

## Line 5

```bash
echo "You seem to like the bash shell."
```

Because the condition was true, this command is executed.

It prints:

```text
You seem to like the bash shell.
```

---

## Line 6

```bash
fi
```

This ends the `if` statement.

---

## What if the condition is false?

Suppose we change:

```bash
MY_SHELL="bash"
```

to:

```bash
MY_SHELL="csh"
```

Then the condition becomes:

```bash
[ "csh" = "bash" ]
```

This is false.

Therefore:

```bash
echo "You seem to like the bash shell."
```

is skipped.

The script produces no output from that `if` block.

---

# ↔️ The `if / else` Statement

Sometimes we want one action when the condition is true and another action when it is false.

The syntax is:

```bash
if [ condition ]
then
    command_if_true
else
    command_if_false
fi
```

The logic is:

```text
               condition
              /         \
           true         false
            /             \
           ▼               ▼
   commands after      commands after
       then                else
            \             /
             \           /
                continue
```

Exactly **one branch** is selected.

---

# 🧪 Example: `if / else`

Consider:

```bash
#!/bin/bash

MY_SHELL="csh"

if [ "$MY_SHELL" = "bash" ]
then
    echo "You seem to like the bash shell."
else
    echo "You don't seem to like the bash shell."
fi
```

Output:

```text
You don't seem to like the bash shell.
```

Let's explain every line.

---

## Shebang

```bash
#!/bin/bash
```

Run the script with Bash.

---

## Variable assignment

```bash
MY_SHELL="csh"
```

The variable now contains:

```text
csh
```

---

## Condition

```bash
if [ "$MY_SHELL" = "bash" ]
```

Bash substitutes the variable:

```text
$MY_SHELL → csh
```

So the test is:

```bash
[ "csh" = "bash" ]
```

This condition is **false**.

---

## `then` branch

```bash
then
    echo "You seem to like the bash shell."
```

This branch runs only when the condition is true.

Since the condition is false, this command is skipped.

---

## `else` branch

```bash
else
    echo "You don't seem to like the bash shell."
```

Because the condition was false, Bash executes the `else` branch.

Output:

```text
You don't seem to like the bash shell.
```

---

## End of block

```bash
fi
```

The decision structure ends.

---

# 🪜 The `elif` Statement

If there are more than two possibilities, Bash provides:

```bash
elif
```

which means:

> else if

Example:

```bash
#!/bin/bash

MY_SHELL="zsh"

if [ "$MY_SHELL" = "bash" ]; then
    echo "You are using Bash."
elif [ "$MY_SHELL" = "zsh" ]; then
    echo "You are using Zsh."
else
    echo "You are using another shell."
fi
```

Output:

```text
You are using Zsh.
```

The order is:

```text
if     → test the first condition
elif   → if the first was false, test another condition
else   → if all previous conditions were false
fi     → finish the block
```

---

# 🔍 Understanding `[ condition ]`

In code such as:

```bash
if [ "$MY_SHELL" = "bash" ]
```

the part:

```bash
[ "$MY_SHELL" = "bash" ]
```

is a **test**.

The spaces are important.

✅ Correct:

```bash
[ "$MY_SHELL" = "bash" ]
```

❌ Incorrect:

```bash
["$MY_SHELL"="bash"]
```

A useful way to read the correct form is:

```text
[    "$MY_SHELL"    =    "bash"    ]
     left value   compare  right value
```

---

## Common string tests

```bash
[ "$A" = "$B" ]      # true if strings are equal
[ "$A" != "$B" ]     # true if strings are different
[ -z "$A" ]          # true if A is empty
[ -n "$A" ]          # true if A is not empty
```

Example:

```bash
NAME="Milad"

if [ -n "$NAME" ]; then
    echo "The name is not empty."
fi
```

---

## Common integer tests

```bash
[ "$A" -eq "$B" ]    # equal
[ "$A" -ne "$B" ]    # not equal
[ "$A" -lt "$B" ]    # less than
[ "$A" -le "$B" ]    # less than or equal
[ "$A" -gt "$B" ]    # greater than
[ "$A" -ge "$B" ]    # greater than or equal
```

Example:

```bash
AGE=20

if [ "$AGE" -ge 18 ]; then
    echo "Age is at least 18."
fi
```

---

# 🔁 The `for` Loop

A `for` loop repeats a group of commands once for each item in a list.

The general syntax is:

```bash
for VARIABLE_NAME in ITEM1 ITEM2 ITEM3
do
    command1
    command2
    commandN
done
```

You may also see:

```bash
for VARIABLE_NAME in ITEM1 ITEM2 ITEM3; do
    command1
    command2
done
```

Both are valid.

---

## How the loop works

Suppose we write:

```bash
for COLOR in red green blue
do
    echo "$COLOR"
done
```

Bash performs three iterations.

### Iteration 1

```text
COLOR=red
```

then execute the body.

### Iteration 2

```text
COLOR=green
```

then execute the body.

### Iteration 3

```text
COLOR=blue
```

then execute the body.

After the final item, the loop ends at:

```bash
done
```

---

# 🎨 Example: Looping Over Colors

Script:

```bash
#!/bin/bash

for COLOR in red green blue
do
    echo "COLOR: $COLOR"
done
```

Output:

```text
COLOR: red
COLOR: green
COLOR: blue
```

Now examine every line.

---

## Line 1

```bash
#!/bin/bash
```

Use Bash to execute the script.

---

## Line 2

```bash
for COLOR in red green blue
```

This creates a loop variable named:

```text
COLOR
```

The list contains:

```text
red
green
blue
```

Bash assigns each item to `COLOR`, one at a time.

---

## First iteration

Bash effectively has:

```bash
COLOR="red"
```

Then the loop body runs:

```bash
echo "COLOR: $COLOR"
```

Output:

```text
COLOR: red
```

---

## Second iteration

Now:

```bash
COLOR="green"
```

The same command runs:

```bash
echo "COLOR: $COLOR"
```

Output:

```text
COLOR: green
```

---

## Third iteration

Now:

```bash
COLOR="blue"
```

Output:

```text
COLOR: blue
```

---

## `done`

```bash
done
```

marks the end of the `for` loop.

So:

```text
for ... do
    ...
done
```

plays a similar structural role to:

```text
if ... then
    ...
fi
```

---

# 📦 Looping Over Values Stored in a Variable

Instead of writing the items directly after `in`, they can first be stored in a variable.

Example:

```bash
#!/bin/bash

COLORS="red green blue"

for COLOR in $COLORS
do
    echo "COLOR: $COLOR"
done
```

Output:

```text
COLOR: red
COLOR: green
COLOR: blue
```

Let's explain exactly why.

---

## Create the list

```bash
COLORS="red green blue"
```

`COLORS` contains the string:

```text
red green blue
```

---

## Expand the list

```bash
for COLOR in $COLORS
```

Here `$COLORS` is intentionally unquoted.

Its expansion is split into words:

```text
red
green
blue
```

Therefore the loop receives three separate items.

The iterations become:

```text
COLOR=red
COLOR=green
COLOR=blue
```

---

## Important difference

Compare:

```bash
for COLOR in $COLORS
```

with:

```bash
for COLOR in "$COLORS"
```

If:

```bash
COLORS="red green blue"
```

then:

```bash
for COLOR in $COLORS
```

normally gives **three iterations**:

```text
red
green
blue
```

But:

```bash
for COLOR in "$COLORS"
```

gives **one iteration** whose value is:

```text
red green blue
```

That difference comes from Bash word splitting.

> [!NOTE]
> For real programs where list items may themselves contain spaces, Bash arrays are safer than storing a list in one plain string.

Example array:

```bash
COLORS=("red" "green" "light blue")

for COLOR in "${COLORS[@]}"; do
    echo "COLOR: $COLOR"
done
```

Output:

```text
COLOR: red
COLOR: green
COLOR: light blue
```

---

# 🖥️ Command Substitution in Loops

Bash can run a command and store its output in a variable using:

```bash
VARIABLE=$(command)
```

This is called **command substitution**.

Examples:

```bash
SERVER_NAME=$(hostname)
```

```bash
TODAY=$(date +%F)
```

```bash
FILES=$(ls)
```

The command inside:

```bash
$(...)
```

runs first.

Its output becomes the variable's value.

---

## Example

```bash
DATE=$(date +%F)
```

Suppose:

```bash
date +%F
```

prints:

```text
2026-08-07
```

Then `DATE` receives:

```text
2026-08-07
```

So afterward:

```bash
echo "$DATE"
```

prints:

```text
2026-08-07
```

---

# 🖼️ Complete Example: Renaming JPG Files

The course example renames every `.jpg` file by adding the current date to the beginning of its filename.

Original files might be:

```text
bear.jpg
man.jpg
pig.jpg
rename-pics.sh
```

The script is:

```bash
#!/bin/bash

PICTURES=$(ls *.jpg)
DATE=$(date +%F)

for PICTURE in $PICTURES
do
    echo "Renaming ${PICTURE} to ${DATE}-${PICTURE}"
    mv "${PICTURE}" "${DATE}-${PICTURE}"
done
```

Now let's explain **every line completely**.

---

## Line 1 — Choose Bash

```bash
#!/bin/bash
```

The shebang tells Linux:

> Execute this script with Bash.

---

## Line 2 — Collect JPG filenames

```bash
PICTURES=$(ls *.jpg)
```

There are two important parts here.

### Part A — `*.jpg`

```bash
*.jpg
```

is a wildcard pattern.

It means:

> Match filenames in the current directory that end with `.jpg`.

If the directory contains:

```text
bear.jpg
man.jpg
pig.jpg
notes.txt
```

then:

```bash
*.jpg
```

matches:

```text
bear.jpg
man.jpg
pig.jpg
```

but not:

```text
notes.txt
```

---

### Part B — `ls *.jpg`

```bash
ls *.jpg
```

asks `ls` to display the matching JPG filenames.

Possible output:

```text
bear.jpg
man.jpg
pig.jpg
```

---

### Part C — `$(...)`

```bash
$(ls *.jpg)
```

runs:

```bash
ls *.jpg
```

and captures its output.

---

### Part D — assignment

```bash
PICTURES=$(ls *.jpg)
```

stores that output in the variable `PICTURES`.

Conceptually:

```text
PICTURES → bear.jpg man.jpg pig.jpg
```

---

## Line 3 — Get the date

```bash
DATE=$(date +%F)
```

Again, this uses command substitution.

The command:

```bash
date +%F
```

prints the current date in ISO format:

```text
YYYY-MM-DD
```

For example:

```text
2015-03-06
```

Therefore:

```bash
DATE=$(date +%F)
```

stores:

```text
2015-03-06
```

inside `DATE`.

Conceptually:

```text
DATE → 2015-03-06
```

---

## Line 4 — Start the loop

```bash
for PICTURE in $PICTURES
```

Suppose:

```text
PICTURES = bear.jpg man.jpg pig.jpg
```

Bash loops over each word.

So the iterations are:

```text
PICTURE=bear.jpg
PICTURE=man.jpg
PICTURE=pig.jpg
```

The loop body runs once for every picture.

---

## Line 5 — Begin the loop body

```bash
do
```

Everything after `do` and before `done` belongs to the loop.

---

## Line 6 — Display the planned rename

```bash
echo "Renaming ${PICTURE} to ${DATE}-${PICTURE}"
```

Suppose we are in the first iteration:

```text
PICTURE=bear.jpg
DATE=2015-03-06
```

Then Bash expands:

```bash
${PICTURE}
```

to:

```text
bear.jpg
```

and:

```bash
${DATE}
```

to:

```text
2015-03-06
```

So the command becomes conceptually:

```bash
echo "Renaming bear.jpg to 2015-03-06-bear.jpg"
```

Output:

```text
Renaming bear.jpg to 2015-03-06-bear.jpg
```

---

## Why `${PICTURE}` instead of `$PICTURE`?

Both can work when the variable is clearly separated:

```bash
$PICTURE
```

But braces make the variable boundary explicit:

```bash
${PICTURE}
```

This is particularly useful when text is immediately attached to the variable.

For example:

```bash
${DATE}-${PICTURE}
```

clearly means:

```text
value of DATE
+
-
+
value of PICTURE
```

---

## Line 7 — Rename the file

```bash
mv "${PICTURE}" "${DATE}-${PICTURE}"
```

The `mv` command moves or renames files.

Its general form is:

```bash
mv SOURCE DESTINATION
```

Here:

```bash
"${PICTURE}"
```

is the old filename.

And:

```bash
"${DATE}-${PICTURE}"
```

is the new filename.

For the first iteration, the command becomes:

```bash
mv "bear.jpg" "2015-03-06-bear.jpg"
```

So:

```text
bear.jpg
```

is renamed to:

```text
2015-03-06-bear.jpg
```

For the second iteration:

```bash
mv "man.jpg" "2015-03-06-man.jpg"
```

For the third:

```bash
mv "pig.jpg" "2015-03-06-pig.jpg"
```

---

## Line 8 — End the loop

```bash
done
```

After reaching `done`, Bash checks whether another item remains in the list.

If yes, the next item is assigned to `PICTURE`.

If no items remain, the loop finishes.

---

# 📤 Expected Output of the Rename Example

Before running the script:

```bash
$ ls
```

Output:

```text
bear.jpg  man.jpg  pig.jpg  rename-pics.sh
```

Run:

```bash
$ ./rename-pics.sh
```

Possible output:

```text
Renaming bear.jpg to 2015-03-06-bear.jpg
Renaming man.jpg to 2015-03-06-man.jpg
Renaming pig.jpg to 2015-03-06-pig.jpg
```

Then:

```bash
$ ls
```

Output:

```text
2015-03-06-bear.jpg
2015-03-06-man.jpg
2015-03-06-pig.jpg
rename-pics.sh
```

So the transformation is:

```text
bear.jpg  →  2015-03-06-bear.jpg
man.jpg   →  2015-03-06-man.jpg
pig.jpg   →  2015-03-06-pig.jpg
```

---

# 🛡️ A Safer Version of the Rename Script

The course example:

```bash
PICTURES=$(ls *.jpg)

for PICTURE in $PICTURES
```

is useful for learning command substitution and loops, but it is **not the safest way to process filenames**.

Why?

Because filenames may contain spaces.

For example:

```text
my holiday.jpg
```

Using:

```bash
PICTURES=$(ls *.jpg)
```

and then:

```bash
for PICTURE in $PICTURES
```

may split the filename into:

```text
my
holiday.jpg
```

which is incorrect.

A better Bash version is:

```bash
#!/bin/bash

DATE=$(date +%F)

for PICTURE in *.jpg
do
    [ -e "$PICTURE" ] || continue

    echo "Renaming ${PICTURE} to ${DATE}-${PICTURE}"
    mv -- "$PICTURE" "${DATE}-${PICTURE}"
done
```

This version does **not** parse the output of `ls`.

---

## Line-by-line explanation of the safer version

### Shebang

```bash
#!/bin/bash
```

Run with Bash.

---

### Store the date

```bash
DATE=$(date +%F)
```

Store the current date in:

```text
YYYY-MM-DD
```

format.

---

### Let Bash expand the wildcard directly

```bash
for PICTURE in *.jpg
```

Bash itself expands:

```bash
*.jpg
```

into matching filenames.

This preserves filenames containing spaces as individual filename items.

---

### Begin loop

```bash
do
```

Start the repeated commands.

---

### Handle the case where no JPG files exist

```bash
[ -e "$PICTURE" ] || continue
```

This is a compact conditional expression.

The first part:

```bash
[ -e "$PICTURE" ]
```

asks whether the path exists.

The operator:

```bash
||
```

means:

> OR — execute the command on the right if the command on the left failed.

So:

```bash
continue
```

is executed when no real matching file exists.

`continue` means:

> Skip the rest of this loop iteration and move to the next one.

---

### Print the rename operation

```bash
echo "Renaming ${PICTURE} to ${DATE}-${PICTURE}"
```

Tell the user what is about to happen.

---

### Rename safely

```bash
mv -- "$PICTURE" "${DATE}-${PICTURE}"
```

Here:

```bash
"$PICTURE"
```

is quoted so filenames containing spaces stay one argument.

The:

```bash
--
```

tells `mv`:

> Stop interpreting anything after this point as command-line options.

That protects against filenames beginning with `-`.

---

### End loop

```bash
done
```

Finish the current iteration and continue until all JPG files have been processed.

---

# ⭐ Recommended Real-World Version

For actual Bash scripts, prefer:

```bash
#!/bin/bash

DATE=$(date +%F)

for PICTURE in *.jpg; do
    [ -e "$PICTURE" ] || continue

    NEW_NAME="${DATE}-${PICTURE}"

    echo "Renaming '$PICTURE' to '$NEW_NAME'"
    mv -- "$PICTURE" "$NEW_NAME"
done
```

This version introduces:

```bash
NEW_NAME="${DATE}-${PICTURE}"
```

which makes the code easier to read.

For example:

```text
DATE=2026-08-07
PICTURE=bear.jpg
```

produces:

```text
NEW_NAME=2026-08-07-bear.jpg
```

Then:

```bash
mv -- "$PICTURE" "$NEW_NAME"
```

clearly means:

> Rename the old filename to the new filename.

---

# ⚠️ Common Mistakes

## 1. Forgetting `then`

❌ Wrong:

```bash
if [ "$NAME" = "Milad" ]
    echo "Hello"
fi
```

✅ Correct:

```bash
if [ "$NAME" = "Milad" ]
then
    echo "Hello"
fi
```

or:

```bash
if [ "$NAME" = "Milad" ]; then
    echo "Hello"
fi
```

---

## 2. Forgetting `fi`

An `if` block must end with:

```bash
fi
```

Example:

```bash
if [ "$A" = "$B" ]; then
    echo "Equal"
fi
```

---

## 3. Forgetting spaces around `[ ... ]`

❌ Wrong:

```bash
if ["$A" = "$B"]; then
```

✅ Correct:

```bash
if [ "$A" = "$B" ]; then
```

---

## 4. Using the wrong comparison operator

For strings:

```bash
[ "$A" = "$B" ]
```

For integers:

```bash
[ "$A" -eq "$B" ]
```

Do not confuse them.

---

## 5. Forgetting `do`

❌ Wrong:

```bash
for COLOR in red green blue
    echo "$COLOR"
done
```

✅ Correct:

```bash
for COLOR in red green blue
do
    echo "$COLOR"
done
```

or:

```bash
for COLOR in red green blue; do
    echo "$COLOR"
done
```

---

## 6. Forgetting `done`

Every `for` loop must eventually end with:

```bash
done
```

---

## 7. Quoting a whole string list when you expect several loop items

Given:

```bash
COLORS="red green blue"
```

This:

```bash
for COLOR in "$COLORS"
```

produces only **one iteration**.

If you intentionally use a space-separated string list:

```bash
for COLOR in $COLORS
```

produces three words.

For robust scripts, arrays are usually better:

```bash
COLORS=("red" "green" "blue")

for COLOR in "${COLORS[@]}"; do
    echo "$COLOR"
done
```

---

## 8. Parsing `ls` in real scripts

This educational pattern:

```bash
FILES=$(ls *.jpg)
```

is easy to understand, but it can fail with unusual filenames.

Prefer direct globbing:

```bash
for FILE in *.jpg
```

for filesystem loops.

---

# 📌 Quick Reference

## Basic `if`

```bash
if [ condition ]; then
    commands
fi
```

---

## `if / else`

```bash
if [ condition ]; then
    commands_if_true
else
    commands_if_false
fi
```

---

## `if / elif / else`

```bash
if [ condition1 ]; then
    commands1
elif [ condition2 ]; then
    commands2
else
    commands3
fi
```

---

## Basic `for`

```bash
for ITEM in item1 item2 item3; do
    commands
done
```

---

## Loop over values

```bash
for COLOR in red green blue; do
    echo "$COLOR"
done
```

---

## Loop over an array

```bash
COLORS=("red" "green" "blue")

for COLOR in "${COLORS[@]}"; do
    echo "$COLOR"
done
```

---

## Command substitution

```bash
VARIABLE=$(command)
```

Example:

```bash
DATE=$(date +%F)
```

---

## String equality

```bash
[ "$A" = "$B" ]
```

---

## String inequality

```bash
[ "$A" != "$B" ]
```

---

## Numeric comparison

```bash
[ "$A" -eq "$B" ]   # equal
[ "$A" -ne "$B" ]   # not equal
[ "$A" -lt "$B" ]   # less than
[ "$A" -le "$B" ]   # less than or equal
[ "$A" -gt "$B" ]   # greater than
[ "$A" -ge "$B" ]   # greater than or equal
```

---

# 🧠 One-Minute Summary

The basic decision structure is:

```bash
if [ condition ]; then
    commands
fi
```

Add another path with:

```bash
else
```

Use:

```bash
elif
```

when more conditions are needed.

A `for` loop repeats commands:

```bash
for ITEM in A B C; do
    echo "$ITEM"
done
```

which executes once for:

```text
A
B
C
```

Command substitution:

```bash
DATE=$(date +%F)
```

runs a command and stores its output.

And the practical JPG example:

```bash
for PICTURE in *.jpg; do
    mv -- "$PICTURE" "${DATE}-${PICTURE}"
done
```

renames every matching image by adding a date prefix.

---

> **Key idea:** `if` chooses **whether** commands run, while `for` chooses **how many times** commands run.
