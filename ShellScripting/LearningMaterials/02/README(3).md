# 🧪 Bash Test Operators

A practical, standalone reference for **file, string, and arithmetic tests in Bash**.

Bash test operators are commonly used inside:

```bash
if
while
until
```

conditions to ask questions such as:

- Does this file exist?
- Is this path a directory?
- Is this string empty?
- Are these two strings equal?
- Is one number greater than another?

---

## 📚 Table of Contents

- [How Bash Tests Work](#-how-bash-tests-work)
- [Test Syntax](#-test-syntax)
- [File Operators](#-file-operators)
- [String Operators](#-string-operators)
- [Arithmetic Operators](#-arithmetic-operators)
- [String vs Numeric Comparisons](#-string-vs-numeric-comparisons)
- [Combining Conditions](#-combining-conditions)
- [Common Mistakes](#-common-mistakes)
- [Complete Examples](#-complete-examples)
- [Quick Reference](#-quick-reference)

---

# 🔎 How Bash Tests Work

A test checks whether a condition is **true** or **false**.

For example:

```bash
if [ -f "notes.txt" ]; then
    echo "notes.txt is a regular file."
fi
```

The condition is:

```bash
[ -f "notes.txt" ]
```

It asks:

> Does `notes.txt` exist and is it a regular file?

If the answer is true, Bash executes the commands after `then`.

---

# 🧱 Test Syntax

The traditional Bash test syntax is:

```bash
[ condition ]
```

For example:

```bash
[ -f "$FILE" ]
```

Bash also supports:

```bash
test condition
```

So these two are equivalent:

```bash
[ -f "$FILE" ]
```

```bash
test -f "$FILE"
```

In Bash scripts, you will also commonly see the more powerful form:

```bash
[[ condition ]]
```

Example:

```bash
[[ -f "$FILE" ]]
```

For Bash-specific scripts, `[[ ... ]]` is often easier and safer to use.

> [!IMPORTANT]
> Spaces around `[` and `]` are required.

✅ Correct:

```bash
[ -f "$FILE" ]
```

❌ Incorrect:

```bash
[-f "$FILE"]
```

---

# 📁 File Operators

File operators test properties of files and directories.

Assume:

```bash
FILE="notes.txt"
```

---

## `-d FILE` — Is it a directory?

```bash
[ -d "$FILE" ]
```

Returns true if `FILE` exists and is a **directory**.

Example:

```bash
DIRECTORY="/home"

if [ -d "$DIRECTORY" ]; then
    echo "$DIRECTORY is a directory."
fi
```

Possible output:

```text
/home is a directory.
```

---

## `-e FILE` — Does it exist?

```bash
[ -e "$FILE" ]
```

Returns true if the path **exists**.

It may be:

- a regular file
- a directory
- another filesystem object

Example:

```bash
if [ -e "notes.txt" ]; then
    echo "notes.txt exists."
fi
```

---

## `-f FILE` — Is it a regular file?

```bash
[ -f "$FILE" ]
```

Returns true if the path exists and is a **regular file**.

Example:

```bash
if [ -f "report.txt" ]; then
    echo "report.txt is a regular file."
fi
```

### `-e` vs `-f`

```text
-e  → Does the path exist?
-f  → Does it exist AND is it a regular file?
```

For example, if `Documents` is a directory:

```bash
[ -e "Documents" ]
```

is true, but:

```bash
[ -f "Documents" ]
```

is false.

---

## `-r FILE` — Is it readable?

```bash
[ -r "$FILE" ]
```

Returns true if the current process has permission to **read** the file.

Example:

```bash
if [ -r "config.txt" ]; then
    echo "I can read config.txt."
fi
```

---

## `-s FILE` — Does it exist and contain data?

```bash
[ -s "$FILE" ]
```

Returns true if the file exists and its size is **greater than zero**.

Example:

```bash
if [ -s "output.txt" ]; then
    echo "output.txt is not empty."
fi
```

If the file exists but contains zero bytes, the test is false.

---

## `-w FILE` — Is it writable?

```bash
[ -w "$FILE" ]
```

Returns true if the current process has permission to **write** to the file.

Example:

```bash
if [ -w "data.txt" ]; then
    echo "I can modify data.txt."
fi
```

---

## `-x FILE` — Is it executable?

```bash
[ -x "$FILE" ]
```

Returns true if the current process has permission to **execute** the file.

Example:

```bash
if [ -x "script.sh" ]; then
    echo "script.sh is executable."
fi
```

If a shell script is not executable, you can normally add execute permission with:

```bash
chmod +x script.sh
```

---

## 📌 File Operator Summary

| Operator | True when... |
|---|---|
| `-d FILE` | `FILE` exists and is a directory |
| `-e FILE` | `FILE` exists |
| `-f FILE` | `FILE` exists and is a regular file |
| `-r FILE` | `FILE` is readable |
| `-s FILE` | `FILE` exists and has a size greater than zero |
| `-w FILE` | `FILE` is writable |
| `-x FILE` | `FILE` is executable |

---

# 🔤 String Operators

String tests compare or inspect text values.

Assume:

```bash
NAME="Milad"
```

---

## `-z STRING` — Is the string empty?

```bash
[ -z "$NAME" ]
```

Returns true if the string has **zero length**.

Example:

```bash
NAME=""

if [ -z "$NAME" ]; then
    echo "NAME is empty."
fi
```

Output:

```text
NAME is empty.
```

### Memory trick

```text
-z → zero length
```

---

## `-n STRING` — Is the string not empty?

```bash
[ -n "$NAME" ]
```

Returns true if the string has a length **greater than zero**.

Example:

```bash
NAME="Milad"

if [ -n "$NAME" ]; then
    echo "NAME is not empty."
fi
```

Output:

```text
NAME is not empty.
```

### Memory trick

```text
-n → non-empty
```

---

## `STRING1 = STRING2` — Are the strings equal?

```bash
[ "$STRING1" = "$STRING2" ]
```

Returns true if both strings are equal.

Example:

```bash
A="Linux"
B="Linux"

if [ "$A" = "$B" ]; then
    echo "The strings are equal."
fi
```

Output:

```text
The strings are equal.
```

---

## `STRING1 != STRING2` — Are the strings different?

```bash
[ "$STRING1" != "$STRING2" ]
```

Returns true if the strings are **not equal**.

Example:

```bash
A="Linux"
B="Windows"

if [ "$A" != "$B" ]; then
    echo "The strings are different."
fi
```

Output:

```text
The strings are different.
```

---

## 📌 String Operator Summary

| Operator | True when... |
|---|---|
| `-z STRING` | The string is empty |
| `-n STRING` | The string is not empty |
| `STRING1 = STRING2` | The strings are equal |
| `STRING1 != STRING2` | The strings are different |

---

# 🔢 Arithmetic Operators

When comparing **integers**, Bash traditionally uses special operators rather than mathematical symbols such as `<` and `>` inside `[ ... ]`.

Assume:

```bash
A=10
B=5
```

---

## `-eq` — Equal

```bash
[ "$A" -eq "$B" ]
```

True if:

```text
A = B
```

Example:

```bash
A=10
B=10

if [ "$A" -eq "$B" ]; then
    echo "A and B are equal."
fi
```

---

## `-ne` — Not equal

```bash
[ "$A" -ne "$B" ]
```

True if:

```text
A ≠ B
```

Example:

```bash
A=10
B=5

if [ "$A" -ne "$B" ]; then
    echo "A and B are different."
fi
```

---

## `-lt` — Less than

```bash
[ "$A" -lt "$B" ]
```

True if:

```text
A < B
```

Example:

```bash
A=3
B=8

if [ "$A" -lt "$B" ]; then
    echo "A is less than B."
fi
```

---

## `-le` — Less than or equal

```bash
[ "$A" -le "$B" ]
```

True if:

```text
A ≤ B
```

---

## `-gt` — Greater than

```bash
[ "$A" -gt "$B" ]
```

True if:

```text
A > B
```

Example:

```bash
A=10
B=5

if [ "$A" -gt "$B" ]; then
    echo "A is greater than B."
fi
```

---

## `-ge` — Greater than or equal

```bash
[ "$A" -ge "$B" ]
```

True if:

```text
A ≥ B
```

---

## 📌 Arithmetic Operator Summary

| Operator | Meaning |
|---|---|
| `arg1 -eq arg2` | `arg1` equals `arg2` |
| `arg1 -ne arg2` | `arg1` does not equal `arg2` |
| `arg1 -lt arg2` | `arg1` is less than `arg2` |
| `arg1 -le arg2` | `arg1` is less than or equal to `arg2` |
| `arg1 -gt arg2` | `arg1` is greater than `arg2` |
| `arg1 -ge arg2` | `arg1` is greater than or equal to `arg2` |

### Easy memory trick

```text
eq → equal
ne → not equal
lt → less than
le → less than or equal
gt → greater than
ge → greater than or equal
```

---

# ⚖️ String vs Numeric Comparisons

This distinction is extremely important.

## Strings

Use:

```bash
=
!=
```

Example:

```bash
[ "$A" = "$B" ]
```

---

## Integers

Use:

```bash
-eq
-ne
-lt
-le
-gt
-ge
```

Example:

```bash
[ "$A" -eq "$B" ]
```

---

## ❌ Do not confuse them

This:

```bash
[ "$A" = "$B" ]
```

asks whether the **text** is equal.

This:

```bash
[ "$A" -eq "$B" ]
```

asks whether the **integer values** are equal.

For example:

```bash
A="05"
B="5"
```

String comparison:

```bash
[ "$A" = "$B" ]
```

is false because:

```text
"05" ≠ "5"
```

Numeric comparison:

```bash
[ "$A" -eq "$B" ]
```

is true because numerically:

```text
5 = 5
```

---

# ➕ Combining Conditions

In Bash, conditions are often combined.

With `[[ ... ]]`, you can use:

```bash
&&
```

for logical AND, and:

```bash
||
```

for logical OR.

---

## AND

Both conditions must be true:

```bash
if [[ -f "$FILE" && -r "$FILE" ]]; then
    echo "The file exists, is regular, and is readable."
fi
```

---

## OR

At least one condition must be true:

```bash
if [[ -z "$NAME" || "$NAME" = "unknown" ]]; then
    echo "No useful name was provided."
fi
```

---

## NOT

Use `!` to reverse a condition:

```bash
if [[ ! -e "$FILE" ]]; then
    echo "The file does not exist."
fi
```

---

# ⚠️ Common Mistakes

## 1. Forgetting spaces inside `[ ... ]`

❌ Wrong:

```bash
if [-f "$FILE"]; then
```

✅ Correct:

```bash
if [ -f "$FILE" ]; then
```

The spaces are part of the required syntax.

---

## 2. Forgetting to quote variables

Prefer:

```bash
[ -z "$NAME" ]
```

rather than:

```bash
[ -z $NAME ]
```

Quoting is especially important with the traditional `[ ... ]` syntax because variable values may contain spaces or special characters.

A good general habit is:

```bash
"$VARIABLE"
```

---

## 3. Using string operators for arithmetic

❌ Wrong idea:

```bash
[ "$AGE" = 20 ]
```

This compares text.

For numeric equality, use:

```bash
[ "$AGE" -eq 20 ]
```

---

## 4. Using numeric operators for strings

❌ Wrong:

```bash
[ "$NAME" -eq "Milad" ]
```

`-eq` expects integer values.

Use:

```bash
[ "$NAME" = "Milad" ]
```

---

## 5. Confusing `-e` and `-f`

```bash
-e
```

means:

> Does this path exist?

```bash
-f
```

means:

> Does it exist and is it a regular file?

A directory can pass `-e` but fail `-f`.

---

## 6. Confusing `-z` and `-n`

```text
-z → empty
-n → not empty
```

Example:

```bash
NAME=""
```

Then:

```bash
[ -z "$NAME" ]
```

is true.

But:

```bash
[ -n "$NAME" ]
```

is false.

---

# 🚀 Complete Examples

## Example 1 — Check whether a file exists

```bash
#!/bin/bash

FILE="notes.txt"

if [ -e "$FILE" ]; then
    echo "$FILE exists."
else
    echo "$FILE does not exist."
fi
```

---

## Example 2 — Check whether a path is a directory

```bash
#!/bin/bash

PATH_TO_CHECK="/tmp"

if [ -d "$PATH_TO_CHECK" ]; then
    echo "$PATH_TO_CHECK is a directory."
else
    echo "$PATH_TO_CHECK is not a directory."
fi
```

---

## Example 3 — Check whether a file is usable

```bash
#!/bin/bash

FILE="script.sh"

if [[ -f "$FILE" && -r "$FILE" && -x "$FILE" ]]; then
    echo "$FILE is a readable and executable regular file."
else
    echo "$FILE does not satisfy all requirements."
fi
```

---

## Example 4 — Check whether user input is empty

```bash
#!/bin/bash

read -r -p "Enter your name: " NAME

if [ -z "$NAME" ]; then
    echo "You did not enter a name."
else
    echo "Hello, $NAME!"
fi
```

---

## Example 5 — Compare two strings

```bash
#!/bin/bash

USERNAME="admin"

if [ "$USERNAME" = "admin" ]; then
    echo "Administrator account."
else
    echo "Normal account."
fi
```

---

## Example 6 — Compare two numbers

```bash
#!/bin/bash

AGE=20

if [ "$AGE" -ge 18 ]; then
    echo "Age is at least 18."
else
    echo "Age is below 18."
fi
```

---

## Example 7 — Multiple numeric conditions

```bash
#!/bin/bash

SCORE=85

if [ "$SCORE" -ge 90 ]; then
    echo "Excellent"
elif [ "$SCORE" -ge 70 ]; then
    echo "Passed"
else
    echo "Needs improvement"
fi
```

Output:

```text
Passed
```

---

# 🆚 `[ ... ]` vs `[[ ... ]]`

Both are commonly used for tests.

## Traditional test

```bash
[ "$NAME" = "Milad" ]
```

This works in many POSIX-compatible shells.

---

## Bash conditional expression

```bash
[[ "$NAME" = "Milad" ]]
```

`[[ ... ]]` is a Bash feature and supports cleaner expressions such as:

```bash
[[ -f "$FILE" && -r "$FILE" ]]
```

For a Bash script starting with:

```bash
#!/bin/bash
```

using `[[ ... ]]` is often convenient.

For maximum POSIX shell portability, use:

```bash
[ ... ]
```

---

# 🔢 Bonus: Arithmetic Context `(( ... ))`

Bash also provides a dedicated arithmetic condition syntax:

```bash
(( expression ))
```

Inside `(( ... ))`, normal mathematical comparison symbols can be used.

Example:

```bash
AGE=20

if (( AGE >= 18 )); then
    echo "Adult"
fi
```

This is equivalent in purpose to:

```bash
if [ "$AGE" -ge 18 ]; then
    echo "Adult"
fi
```

For arithmetic-heavy Bash code, `(( ... ))` can be easier to read.

---

# 📌 Quick Reference

## File tests

```bash
-d FILE   # directory
-e FILE   # exists
-f FILE   # regular file
-r FILE   # readable
-s FILE   # exists and not empty
-w FILE   # writable
-x FILE   # executable
```

---

## String tests

```bash
-z STRING              # string is empty
-n STRING              # string is not empty
STRING1 = STRING2       # strings are equal
STRING1 != STRING2      # strings are not equal
```

---

## Integer tests

```bash
arg1 -eq arg2   # equal
arg1 -ne arg2   # not equal
arg1 -lt arg2   # less than
arg1 -le arg2   # less than or equal
arg1 -gt arg2   # greater than
arg1 -ge arg2   # greater than or equal
```

---

# 🧠 One-Minute Summary

| Category | Test | Meaning |
|---|---|---|
| File | `-d FILE` | Is a directory |
| File | `-e FILE` | Exists |
| File | `-f FILE` | Is a regular file |
| File | `-r FILE` | Is readable |
| File | `-s FILE` | Exists and is not empty |
| File | `-w FILE` | Is writable |
| File | `-x FILE` | Is executable |
| String | `-z STRING` | Empty string |
| String | `-n STRING` | Non-empty string |
| String | `A = B` | Strings equal |
| String | `A != B` | Strings different |
| Number | `A -eq B` | Equal |
| Number | `A -ne B` | Not equal |
| Number | `A -lt B` | Less than |
| Number | `A -le B` | Less than or equal |
| Number | `A -gt B` | Greater than |
| Number | `A -ge B` | Greater than or equal |

---

> **Key idea:** File operators inspect filesystem objects, string operators compare text, and arithmetic operators compare integer values. Always choose the operator that matches the type of data you are testing.
