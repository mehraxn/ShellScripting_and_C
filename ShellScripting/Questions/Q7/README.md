# Background File Copy Progress Monitor

## Overview

This repository contains a Bash script that copies a source file into a destination directory **in the background** and periodically displays an estimate of the percentage of the copy operation that has been completed.

The script is based on the Operating Systems course exercise that combines:

- command-line arguments
- parameter validation
- regular-file and directory tests
- command substitution
- pipelines
- `ls`
- `cut`
- `df`
- `tail`
- `tr`
- background execution with `&`
- arithmetic with `let`
- `while` loops
- `sleep`

The main idea is to estimate copy progress by checking how much the **used space of the destination file system increases** while the copy is running.

---

## 1. Problem

The script receives exactly two command-line arguments:

```bash
./copy_progress.sh SOURCE_FILE DESTINATION_DIRECTORY
```

Example:

```bash
./copy_progress.sh /data/source.iso /data/backup
```

In this execution:

```text
$0 = ./copy_progress.sh
$1 = /data/source.iso
$2 = /data/backup
```

So:

- `$1` is the source file.
- `$2` is the destination directory.
- `$#` is the number of command-line arguments.

The script must:

1. Check that exactly two arguments were supplied.
2. Check that the source is a valid regular file.
3. Check that the destination is a valid directory.
4. Determine the size of the source file.
5. Determine how much space is already used on the destination file system.
6. Start the copy operation in the background.
7. Check the destination file system every one second.
8. Determine how much additional space has been used.
9. Convert that amount into a copy percentage.
10. Continue until the transferred amount reaches the source-file size.

---

## 2. Complete Script

```bash
#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage $0 <source> <destination>"
    exit 1
fi

if [ ! -f $1 ]; then
    echo "Source is not a valid file."
    exit 1
fi

if [ ! -d $2 ]; then
    echo "Destination is not a valid directory."
    exit 1
fi

source=$1
destination=$2

size=$(ls -l $source | cut -d " " -f 5)
let "size=size/1024"

startUsed=$(df $destination | \
            tail -n 1 | \
            tr -s " " | \
            cut -d " " -f 3)

cp $source $destination &

transferred=0
percentage=0

while [ $transferred -lt $size ]; do

    currentUsed=$(df $destination | \
                  tail -n 1 | \
                  tr -s " " | \
                  cut -d " " -f 3)

    let "transferred=currentUsed-startUsed"
    let "percentage=transferred*100/size"

    echo "Progress: $percentage%"

    sleep 1
done
```

---

# 3. Line-by-Line Explanation

## `#!/bin/bash`

```bash
#!/bin/bash
```

This is the **shebang**.

It tells the operating system to execute the script using the Bash interpreter located at:

```text
/bin/bash
```

---

## Check the Number of Parameters

```bash
if [ $# -ne 2 ]; then
```

This starts an `if` statement.

### `$#`

`$#` contains the number of command-line arguments passed to the script.

Example:

```bash
./copy_progress.sh file.txt /data/backup
```

has two arguments:

```text
$1 = file.txt
$2 = /data/backup
$# = 2
```

### `-ne`

`-ne` means **numerically not equal**.

Therefore:

```bash
[ $# -ne 2 ]
```

means:

> Is the number of supplied parameters different from 2?

If yes, the condition is true.

---

## Display Correct Usage

```bash
echo "Usage $0 <source> <destination>"
```

`echo` prints text to the terminal.

`$0` contains the name used to execute the script.

For example:

```text
$0 = ./copy_progress.sh
```

So the output may be:

```text
Usage ./copy_progress.sh <source> <destination>
```

---

## Terminate on Error

```bash
exit 1
```

`exit` terminates the script.

Conventionally:

- `exit 0` means successful completion.
- a non-zero value such as `exit 1` indicates an error.

---

## End the First `if`

```bash
fi
```

`fi` closes the Bash `if` statement.

So:

```bash
if [ $# -ne 2 ]; then
    echo "Usage $0 <source> <destination>"
    exit 1
fi
```

means:

> If the user did not provide exactly two arguments, print the correct usage and stop the script.

---

# 4. Check the Source File

```bash
if [ ! -f $1 ]; then
```

This checks whether the first argument is a valid regular file.

### `-f`

The test:

```bash
-f path
```

is true when the path exists and refers to a **regular file**.

### `!`

`!` means logical NOT.

Therefore:

```bash
[ ! -f $1 ]
```

means:

> `$1` is not a valid regular file.

If the test is true, the script prints:

```bash
echo "Source is not a valid file."
```

and terminates:

```bash
exit 1
```

---

# 5. Check the Destination Directory

```bash
if [ ! -d $2 ]; then
```

### `-d`

The test:

```bash
-d path
```

is true when the path exists and is a directory.

Therefore:

```bash
[ ! -d $2 ]
```

means:

> `$2` is not a valid directory.

If so, the script prints:

```bash
echo "Destination is not a valid directory."
```

and exits with:

```bash
exit 1
```

---

# 6. Store the Arguments in Variables

```bash
source=$1
destination=$2
```

These assignments give meaningful names to the two arguments.

If:

```text
$1 = /data/source.iso
$2 = /data/backup
```

then:

```text
source = /data/source.iso
destination = /data/backup
```

The script can now use:

```bash
$source
$destination
```

instead of directly using `$1` and `$2`.

---

# 7. Determine the Source File Size

```bash
size=$(ls -l $source | cut -d " " -f 5)
```

This line combines:

- `ls -l`
- a pipe `|`
- `cut`
- command substitution `$()`

---

## `ls -l $source`

`ls` lists file information.

The `-l` option selects the **long listing format**.

A conceptual output is:

```text
-rw-r--r-- 1 user user 10485760 Aug 15 source.iso
```

The course solution uses the fifth field as the file size.

---

## Pipe `|`

The pipe:

```bash
|
```

passes the output of the command on its left to the command on its right.

Therefore:

```bash
ls -l $source | cut ...
```

means:

1. Run `ls -l $source`.
2. Send its output to `cut`.

---

## `cut -d " " -f 5`

`cut` extracts selected fields.

### `-d " "`

This says that a space is the field delimiter.

### `-f 5`

This says to extract field number 5.

The result is stored in `size`.

---

## Command Substitution `$()`

The syntax:

```bash
$(command)
```

means:

1. execute the command,
2. capture its output,
3. substitute that output at this location.

So:

```bash
size=$(...)
```

stores the output in the variable `size`.

---

# 8. Convert Bytes to 1K Blocks

```bash
let "size=size/1024"
```

The size obtained from `ls -l` is in bytes.

The later `df` values are expressed in 1K blocks, so the script divides by 1024:

```text
1024 bytes = 1 KiB
```

Example:

```text
10485760 / 1024 = 10240
```

So the source size becomes approximately:

```text
10240 1K blocks
```

### `let`

`let` performs integer arithmetic in Bash.

Example:

```bash
let "x=x+1"
```

increments `x`.

Here:

```bash
let "size=size/1024"
```

performs:

```text
size = size / 1024
```

---

# 9. Record Initial Used Space

```bash
startUsed=$(df $destination | \
            tail -n 1 | \
            tr -s " " | \
            cut -d " " -f 3)
```

This obtains how much disk space is already used on the file system containing the destination.

The pipeline is:

```text
df
 |
 v
tail
 |
 v
tr
 |
 v
cut
```

---

## `df $destination`

`df` shows disk-space information for the **file system containing the specified path**.

Example:

```bash
df /data/backup
```

Possible output:

```text
Filesystem     1K-blocks    Used    Available Use% Mounted on
/dev/sda7       41141492   5881472   33174616  16% /data
```

Important fields:

```text
1K-blocks = total file-system space
Used      = occupied file-system space
Available = free file-system space
```

The script uses the `Used` field.

Important: `df /data/backup` does **not** give the size of `/data/backup` itself. It gives information about the whole file system containing that directory.

---

## `tail -n 1`

`df` prints a header and a data line.

`tail -n 1` keeps only the final line.

Input:

```text
Filesystem     1K-blocks    Used    Available Use% Mounted on
/dev/sda7       41141492   5881472   33174616  16% /data
```

Output:

```text
/dev/sda7       41141492   5881472   33174616  16% /data
```

---

## Backslash `\`

The backslash at the end of a line:

```bash
\
```

means that the command continues on the following line.

Therefore:

```bash
df $destination | \
tail -n 1 | \
tr -s " " | \
cut -d " " -f 3
```

is equivalent to:

```bash
df $destination | tail -n 1 | tr -s " " | cut -d " " -f 3
```

---

## `tr -s " "`

`df` may use several spaces to align columns.

Example:

```text
/dev/sda7      41141492     5881472     33174616    16% /data
```

The command:

```bash
tr -s " "
```

"squeezes" repeated spaces into one space.

The result becomes:

```text
/dev/sda7 41141492 5881472 33174616 16% /data
```

This makes field extraction easier.

---

## `cut -d " " -f 3`

After spaces are normalized, the fields are:

```text
Field 1 = /dev/sda7
Field 2 = 41141492
Field 3 = 5881472
Field 4 = 33174616
Field 5 = 16%
Field 6 = /data
```

Field 3 is the `Used` value.

Therefore:

```bash
cut -d " " -f 3
```

extracts the used file-system space.

That value is stored in:

```text
startUsed
```

So `startUsed` means:

> used destination file-system space before the copy starts.

---

# 10. Start the Copy in the Background

```bash
cp $source $destination &
```

`cp` copies a source file to a destination.

General form:

```bash
cp SOURCE DESTINATION
```

Example:

```bash
cp /data/source.iso /data/backup
```

The important part is:

```bash
&
```

`&` starts the command as a **background job**.

Without `&`, the script would wait for `cp` to finish before continuing.

That would make progress monitoring useless.

With:

```bash
cp $source $destination &
```

the behavior is conceptually:

```text
              +--> cp keeps copying
              |
script -------+
              |
              +--> script continues monitoring
```

---

# 11. Initialize Monitoring Variables

```bash
transferred=0
percentage=0
```

At the beginning:

```text
transferred = 0
percentage  = 0
```

`transferred` represents the estimated amount copied.

`percentage` represents the estimated copy percentage.

---

# 12. Start the `while` Loop

```bash
while [ $transferred -lt $size ]; do
```

The loop continues as long as:

```text
transferred < size
```

### `-lt`

`-lt` means **numerically less than**.

So:

```bash
[ $transferred -lt $size ]
```

means:

> Has the transferred amount not yet reached the full source-file size?

If yes, keep monitoring.

---

# 13. Measure Current Used Space

```bash
currentUsed=$(df $destination | \
              tail -n 1 | \
              tr -s " " | \
              cut -d " " -f 3)
```

This repeats the same `df` pipeline.

The difference is:

- `startUsed` was measured before copying.
- `currentUsed` is measured while copying.

Example:

```text
startUsed   = 5000000
currentUsed = 5004000
```

The destination file system is now using 4000 more 1K blocks.

---

# 14. Calculate the Transferred Amount

```bash
let "transferred=currentUsed-startUsed"
```

This calculates:

```text
transferred = currentUsed - startUsed
```

Example:

```text
currentUsed = 5004000
startUsed   = 5000000
```

Then:

```text
transferred = 4000
```

The script treats this increase in used file-system space as the amount copied.

---

# 15. Calculate the Percentage

```bash
let "percentage=transferred*100/size"
```

The formula is:

```text
percentage = transferred × 100 / size
```

Example:

```text
size        = 10000
transferred = 4000
```

Then:

```text
percentage = 4000 × 100 / 10000
           = 40
```

So progress is:

```text
40%
```

---

# 16. Display the Percentage

```bash
echo "Progress: $percentage%"
```

If:

```text
percentage = 40
```

the terminal displays:

```text
Progress: 40%
```

Possible output during a copy:

```text
Progress: 12%
Progress: 27%
Progress: 43%
Progress: 68%
Progress: 91%
Progress: 100%
```

---

# 17. Wait One Second

```bash
sleep 1
```

`sleep` pauses the script.

`sleep 1` means:

> Wait approximately one second.

Then the next loop iteration begins.

The monitoring cycle is:

```text
Check current used space
        ↓
Calculate transferred amount
        ↓
Calculate percentage
        ↓
Display percentage
        ↓
sleep 1
        ↓
Repeat
```

---

# 18. End the Loop

```bash
done
```

`done` closes the `while` loop.

The loop terminates when:

```text
transferred >= size
```

---

# 19. Complete Program Flow

```text
START
  |
  v
Check $# == 2
  |
  +---- No ---> print usage ---> exit 1
  |
 Yes
  |
  v
Check $1 is a regular file
  |
  +---- No ---> print error ---> exit 1
  |
 Yes
  |
  v
Check $2 is a directory
  |
  +---- No ---> print error ---> exit 1
  |
 Yes
  |
  v
source=$1
destination=$2
  |
  v
Determine source-file size
  |
  v
Convert bytes to 1K blocks
  |
  v
Run df on destination
  |
  v
Store initial Used value in startUsed
  |
  v
cp source destination &
  |
  v
Copy runs in background
  |
  v
transferred=0
percentage=0
  |
  v
+----------------------------------+
| transferred < size ?             |
+----------------------------------+
        |
       Yes
        |
        v
Run df on destination again
        |
        v
Get current Used value
        |
        v
transferred =
currentUsed - startUsed
        |
        v
percentage =
transferred * 100 / size
        |
        v
Print percentage
        |
        v
sleep 1
        |
        +-----------> repeat
        |
       No
        |
        v
       END
```

---

# 20. Important Variables

| Variable | Meaning |
|---|---|
| `$0` | Script name |
| `$1` | Source-file path |
| `$2` | Destination-directory path |
| `$#` | Number of command-line arguments |
| `source` | Copy of `$1` |
| `destination` | Copy of `$2` |
| `size` | Source-file size converted to 1K blocks |
| `startUsed` | Used destination file-system space before copying |
| `currentUsed` | Used destination file-system space during copying |
| `transferred` | Difference between `currentUsed` and `startUsed` |
| `percentage` | Estimated completion percentage |

---

# 21. Important Commands

| Command | Purpose |
|---|---|
| `echo` | Print messages |
| `exit` | Terminate the script |
| `ls -l` | Get detailed file information |
| `cut` | Extract fields |
| `df` | Get file-system disk-space information |
| `tail -n 1` | Keep only the last line |
| `tr -s " "` | Squeeze repeated spaces |
| `cp` | Copy the source file |
| `let` | Perform integer arithmetic |
| `sleep` | Pause between progress checks |

---

# 22. Important Bash Syntax

| Syntax | Meaning |
|---|---|
| `$#` | Number of arguments |
| `$0` | Script name |
| `$1`, `$2` | First and second arguments |
| `-ne` | Numerically not equal |
| `-lt` | Numerically less than |
| `-f` | Test for a regular file |
| `-d` | Test for a directory |
| `!` | Logical NOT |
| `$(...)` | Command substitution |
| `|` | Pipe |
| `&` | Run command in background |
| `\` | Continue command on next line |
| `if ... fi` | Conditional statement |
| `while ... done` | Loop |

---

# 23. Progress Formula

The script uses:

```text
transferred = currentUsed - startUsed
```

and:

```text
percentage = transferred × 100 / size
```

Therefore:

```text
                  currentUsed - startUsed
Progress (%) = ----------------------------- × 100
                         size
```

---

# 24. Why `df` Is Important

`df` reports disk-space information for the **file system containing a path**.

It does not report the size of that particular file or directory.

Conceptually:

```text
Physical disk / partition
        |
        v
    File system
        |
        +---- /data
               |
               +---- backup
```

If `/data/backup` belongs to a file system that uses:

```text
5,000,000 KB
```

before the copy and:

```text
5,020,000 KB
```

during the copy, the script observes an increase of:

```text
20,000 KB
```

and treats that increase as transferred data.

---

# 25. Why Field 3 Is Used

After normalization, a `df` line can look like:

```text
/dev/sda7 41141492 5881472 33174616 16% /data
```

Fields:

```text
Field 1 → /dev/sda7
Field 2 → 41141492     total 1K blocks
Field 3 → 5881472      used space
Field 4 → 33174616     available space
Field 5 → 16%          percentage used
Field 6 → /data        mount point
```

The script uses:

```bash
cut -d " " -f 3
```

because field 3 is the **Used** value.

---

# 26. Why Background Execution Is Necessary

Without `&`:

```bash
cp $source $destination
```

the program would behave like:

```text
Start copy
   ↓
Wait until copy finishes
   ↓
Start monitoring
```

This cannot show useful progress.

With:

```bash
cp $source $destination &
```

the copy and monitoring overlap:

```text
            +--> cp continues copying
            |
script -----+
            |
            +--> script monitors disk usage
```

---

# 27. Example Execution

Run:

```bash
./copy_progress.sh /data/source.iso /data/backup
```

Suppose:

```text
size = 100000 KB
```

and before copying:

```text
startUsed = 500000 KB
```

Later:

```text
currentUsed = 520000 KB
```

Then:

```text
transferred = 520000 - 500000
            = 20000 KB
```

Progress:

```text
percentage = 20000 × 100 / 100000
           = 20%
```

Output:

```text
Progress: 20%
```

One second later, suppose:

```text
currentUsed = 550000 KB
```

Then:

```text
transferred = 50000 KB
percentage  = 50%
```

Output:

```text
Progress: 50%
```

The program continues until the transferred amount reaches the source-file size.

---

# 28. Course-Slide Syntax Correction

The original course slide shows assignments in the form:

```bash
startUsed = $(...)
```

and:

```bash
currentUsed = $(...)
```

In Bash, variable assignments must not contain spaces around `=`.

Therefore the executable version uses:

```bash
startUsed=$(...)
```

and:

```bash
currentUsed=$(...)
```

This changes only the syntax error; the algorithm is the same.

---

# 29. Summary

The script has six main phases:

```text
1. Validate parameters
2. Determine source-file size
3. Record destination file-system used space
4. Start cp in the background
5. Measure used space every second
6. Calculate and display progress
```

The central commands are:

```bash
cp $source $destination &
```

which starts the copy in the background,

```bash
currentUsed=$(df $destination | tail -n 1 | tr -s " " | cut -d " " -f 3)
```

which obtains the current used space of the destination file system,

```bash
let "transferred=currentUsed-startUsed"
```

which estimates how much data has been copied,

and:

```bash
let "percentage=transferred*100/size"
```

which converts the transferred amount into a percentage.

Finally:

```bash
sleep 1
```

waits one second before the next progress check.
