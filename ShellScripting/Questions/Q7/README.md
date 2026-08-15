# Background File Copy Progress Monitor

A Bash script that copies a file to a destination directory in the **background** while periodically estimating and displaying the progress of the copy operation.

The script demonstrates how Bash can combine process management, command-line arguments, file-system inspection, pipelines, arithmetic, and loops to monitor an operation while it is running.

---

## Table of Contents

* [Overview](#overview)
* [What the Script Does](#what-the-script-does)
* [Script](#script)
* [Running the Script](#running-the-script)
* [Command-Line Arguments](#command-line-arguments)
* [How Progress Is Calculated](#how-progress-is-calculated)
* [Complete Execution Flow](#complete-execution-flow)
* [Line-by-Line Explanation](#line-by-line-explanation)
* [Important Variables](#important-variables)
* [Important Commands](#important-commands)
* [Important Bash Syntax](#important-bash-syntax)
* [Example Execution](#example-execution)
* [Understanding `df`](#understanding-df)
* [Understanding the Pipeline](#understanding-the-pipeline)
* [Why the Copy Runs in the Background](#why-the-copy-runs-in-the-background)
* [Limitations of the Progress Calculation](#limitations-of-the-progress-calculation)
* [Summary](#summary)

---

# Overview

Normally, running:

```bash
cp source_file destination_directory
```

causes the shell to wait until the copy operation finishes.

This script instead starts the copy in the **background**:

```bash
cp "$source" "$destination" &
```

The script can therefore continue executing while `cp` is still running.

During the copy, the script checks how much disk space is being used on the file system containing the destination.

By comparing:

```text
used space before the copy
```

with:

```text
used space during the copy
```

the script estimates how much data has already been transferred.

It then converts this amount into a percentage.

---

# What the Script Does

The program expects two command-line arguments:

```bash
./copy_progress.sh SOURCE_FILE DESTINATION_DIRECTORY
```

For example:

```bash
./copy_progress.sh /data/source.iso /data/backup
```

The script performs the following operations:

1. Verifies that exactly two arguments were supplied.
2. Verifies that the source exists and is a regular file.
3. Verifies that the destination exists and is a directory.
4. Stores the two arguments in descriptive variables.
5. Determines the size of the source file.
6. Converts the source size to approximately 1 KB blocks.
7. Measures the amount of disk space already used on the destination file system.
8. Starts the file copy in the background.
9. Repeatedly measures the destination file-system usage.
10. Estimates how much data has been transferred.
11. Calculates a progress percentage.
12. Prints the progress.
13. Waits one second.
14. Repeats until the estimated transferred amount reaches the source-file size.

---

# Script

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

# Running the Script

First, make the script executable:

```bash
chmod +x copy_progress.sh
```

Then execute it:

```bash
./copy_progress.sh SOURCE_FILE DESTINATION_DIRECTORY
```

Example:

```bash
./copy_progress.sh /data/source.iso /data/backup
```

Possible output:

```text
Progress: 10%
Progress: 24%
Progress: 39%
Progress: 53%
Progress: 71%
Progress: 86%
Progress: 100%
```

The exact values depend on factors such as:

* file size
* disk speed
* file-system behavior
* system load
* how much data is written during each one-second interval

---

# Command-Line Arguments

Consider:

```bash
./copy_progress.sh /data/source.iso /data/backup
```

Bash assigns:

```text
$0 = ./copy_progress.sh
$1 = /data/source.iso
$2 = /data/backup
```

The special variable:

```bash
$#
```

contains the number of command-line arguments.

In this example:

```text
$# = 2
```

The variables therefore have these meanings:

| Variable | Meaning                         |
| -------- | ------------------------------- |
| `$0`     | Name used to execute the script |
| `$1`     | Source-file path                |
| `$2`     | Destination-directory path      |
| `$#`     | Number of supplied arguments    |

---

# How Progress Is Calculated

The script does not ask `cp` directly how many bytes it has copied.

Instead, it estimates progress from the increase in used disk space.

Suppose the destination file system initially uses:

```text
5,000,000 KB
```

The script stores:

```text
startUsed = 5,000,000
```

Later, while the copy is running, suppose the file system uses:

```text
5,025,000 KB
```

Then:

```text
currentUsed = 5,025,000
```

The transferred amount is estimated as:

```text
transferred = currentUsed - startUsed
```

Therefore:

```text
transferred = 5,025,000 - 5,000,000
            = 25,000 KB
```

If the source file has a size of:

```text
100,000 KB
```

the percentage becomes:

```text
percentage = transferred × 100 / size
```

Therefore:

```text
percentage = 25,000 × 100 / 100,000
           = 25
```

The displayed progress is:

```text
Progress: 25%
```

The general formula is:

```text
                  currentUsed - startUsed
Progress (%) = ----------------------------- × 100
                         size
```

---

# Complete Execution Flow

```text
START
  |
  v
Check number of parameters
  |
  +---- Incorrect ----> Print usage
  |                         |
  |                         v
  |                      exit 1
  |
 Correct
  |
  v
Check whether $1 is a regular file
  |
  +---- No -----------> Print error
  |                         |
  |                         v
  |                      exit 1
  |
 Yes
  |
  v
Check whether $2 is a directory
  |
  +---- No -----------> Print error
  |                         |
  |                         v
  |                      exit 1
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
Convert source size to 1 KB blocks
  |
  v
Measure destination file-system used space
  |
  v
Store it in startUsed
  |
  v
Start cp in background
  |
  v
transferred=0
percentage=0
  |
  v
+------------------------------------+
| Is transferred smaller than size?  |
+------------------------------------+
         |
        Yes
         |
         v
Measure current used space
         |
         v
currentUsed
         |
         v
transferred =
currentUsed - startUsed
         |
         v
percentage =
transferred × 100 / size
         |
         v
Print percentage
         |
         v
sleep 1
         |
         +-------------> Repeat
         |
        No
         |
         v
        END
```

---

# Line-by-Line Explanation

## 1. Select the Bash Interpreter

```bash
#!/bin/bash
```

This line is called the **shebang**.

It tells the operating system that the script should be interpreted using:

```text
/bin/bash
```

Without it, the operating system may not know which interpreter should execute the file.

---

# 2. Check the Number of Arguments

```bash
if [ $# -ne 2 ]; then
```

This begins an `if` statement.

The condition is:

```bash
[ $# -ne 2 ]
```

### `$#`

`$#` stores the number of arguments passed to the script.

Example:

```bash
./copy_progress.sh file.iso /backup
```

contains two arguments:

```text
$1 = file.iso
$2 = /backup
```

Therefore:

```text
$# = 2
```

### `-ne`

`-ne` means:

```text
numerically not equal
```

Therefore:

```bash
[ $# -ne 2 ]
```

means:

> Is the number of arguments different from 2?

If the answer is yes, the commands inside the `if` block are executed.

---

# 3. Print the Usage Message

```bash
echo "Usage $0 <source> <destination>"
```

`echo` prints text on standard output.

`$0` contains the name used to execute the script.

For example:

```text
$0 = ./copy_progress.sh
```

The output becomes:

```text
Usage ./copy_progress.sh <source> <destination>
```

This tells the user how the program should be executed.

---

# 4. Terminate After Invalid Arguments

```bash
exit 1
```

`exit` immediately terminates the script.

By convention:

```text
exit 0
```

means successful completion.

A non-zero exit status such as:

```text
exit 1
```

indicates an error.

---

# 5. Close the `if`

```bash
fi
```

Bash uses:

```bash
if
...
fi
```

to define an `if` block.

So the complete section:

```bash
if [ $# -ne 2 ]; then
    echo "Usage $0 <source> <destination>"
    exit 1
fi
```

means:

> If exactly two arguments were not supplied, print an error message and stop.

---

# 6. Validate the Source File

```bash
if [ ! -f $1 ]; then
```

This verifies that the first argument refers to a regular file.

### `-f`

The test:

```bash
-f path
```

is true if `path` exists and represents a regular file.

For example:

```bash
[ -f document.txt ]
```

is true if `document.txt` exists as a normal file.

### `!`

The symbol:

```bash
!
```

means logical NOT.

Therefore:

```bash
[ ! -f $1 ]
```

means:

> `$1` is not a valid regular file.

---

# 7. Source Error Message

```bash
echo "Source is not a valid file."
```

If the source is invalid, this message is printed.

Then:

```bash
exit 1
```

terminates the script.

The complete block is:

```bash
if [ ! -f $1 ]; then
    echo "Source is not a valid file."
    exit 1
fi
```

---

# 8. Validate the Destination Directory

```bash
if [ ! -d $2 ]; then
```

### `-d`

The test:

```bash
-d path
```

checks whether `path` exists and represents a directory.

Therefore:

```bash
[ ! -d $2 ]
```

means:

> `$2` does not refer to a valid directory.

If this is true:

```bash
echo "Destination is not a valid directory."
exit 1
```

prints an error and terminates the script.

---

# 9. Save the Source Argument

```bash
source=$1
```

This creates a variable named:

```text
source
```

and stores `$1` inside it.

For example:

```text
$1 = /data/source.iso
```

results in:

```text
source = /data/source.iso
```

Later, the value is accessed with:

```bash
$source
```

---

# 10. Save the Destination Argument

```bash
destination=$2
```

This stores the second command-line argument in:

```text
destination
```

For example:

```text
$2 = /data/backup
```

becomes:

```text
destination = /data/backup
```

This improves readability because:

```bash
$destination
```

is more descriptive than:

```bash
$2
```

---

# 11. Get the Source File Size

```bash
size=$(ls -l $source | cut -d " " -f 5)
```

This line contains four important concepts:

```text
ls -l
pipe |
cut
command substitution $()
```

---

## `ls -l $source`

`ls` lists file information.

The `-l` option selects the long listing format.

Example:

```bash
ls -l file.iso
```

may produce information containing:

```text
-rw-r--r-- 1 user user 10485760 Aug 15 file.iso
```

Among these fields is the file size.

---

## Pipe `|`

The pipe:

```bash
|
```

takes the standard output of the command on its left and sends it as standard input to the command on its right.

Therefore:

```bash
ls -l $source | cut ...
```

means:

```text
ls produces output
        |
        v
cut receives that output
```

---

## `cut -d " "`

`cut` extracts fields from text.

The option:

```bash
-d " "
```

defines a space as the field delimiter.

---

## `-f 5`

```bash
-f 5
```

asks `cut` to select field number 5.

The selected value is treated as the source-file size.

---

## `$()`

The syntax:

```bash
$(command)
```

is called **command substitution**.

It means:

1. execute `command`,
2. collect its output,
3. use that output as a value.

Therefore:

```bash
size=$(...)
```

stores the output inside `size`.

---

# 12. Convert the File Size

```bash
let "size=size/1024"
```

The size returned by `ls -l` is expressed in bytes.

The `df` values used later are expressed in 1K blocks.

The script therefore divides the file size by:

```text
1024
```

because:

```text
1024 bytes = 1 KiB
```

Example:

```text
10485760 bytes
```

becomes:

```text
10485760 / 1024 = 10240
```

So:

```text
size = 10240
```

in approximately 1 KB units.

---

## `let`

`let` performs integer arithmetic.

Example:

```bash
let "x=x+1"
```

means:

```text
x = x + 1
```

Therefore:

```bash
let "size=size/1024"
```

means:

```text
size = size / 1024
```

---

# 13. Measure Initial Used Disk Space

```bash
startUsed=$(df $destination | \
            tail -n 1 | \
            tr -s " " | \
            cut -d " " -f 3)
```

This pipeline obtains the amount of space currently used on the file system containing the destination directory.

The commands execute in this order:

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

# 14. `df $destination`

```bash
df $destination
```

`df` reports disk-space information for the file system containing the specified path.

Example:

```bash
df /data/backup
```

may display:

```text
Filesystem     1K-blocks    Used    Available Use% Mounted on
/dev/sda7       41141492   5881472   33174616  16% /data
```

The fields mean approximately:

| Field        | Meaning               |
| ------------ | --------------------- |
| `Filesystem` | Device or file system |
| `1K-blocks`  | Total capacity        |
| `Used`       | Occupied space        |
| `Available`  | Free space            |
| `Use%`       | Percentage occupied   |
| `Mounted on` | Mount point           |

The script needs:

```text
Used
```

because it wants to detect how much the occupied space increases during the copy.

---

# 15. `tail -n 1`

The `df` command also prints a header.

For example:

```text
Filesystem     1K-blocks Used Available Use% Mounted on
/dev/sda7      ...
```

The command:

```bash
tail -n 1
```

returns only the final line.

So:

```text
Filesystem ...
/dev/sda7 ...
```

becomes:

```text
/dev/sda7 ...
```

The header is removed.

---

# 16. `tr -s " "`

Commands such as `df` often use several spaces between columns:

```text
/dev/sda7       41141492    5881472    33174616   16%   /data
```

The command:

```bash
tr -s " "
```

uses the `-s` option to **squeeze repeated spaces**.

Several consecutive spaces become one:

```text
/dev/sda7 41141492 5881472 33174616 16% /data
```

This makes the fields easier to extract.

---

# 17. `cut -d " " -f 3`

After the spaces have been normalized, the line can be viewed as:

```text
Field 1 → /dev/sda7
Field 2 → 41141492
Field 3 → 5881472
Field 4 → 33174616
Field 5 → 16%
Field 6 → /data
```

Field 3 is:

```text
Used
```

Therefore:

```bash
cut -d " " -f 3
```

extracts the used-space value.

That value is stored in:

```text
startUsed
```

---

# 18. Meaning of `startUsed`

`startUsed` represents:

> How much disk space was already occupied on the destination file system before this copy began.

For example:

```text
startUsed = 5881472
```

This value provides the starting point for the progress calculation.

---

# 19. The Backslash `\`

The pipeline is written over several lines:

```bash
df $destination | \
tail -n 1 | \
tr -s " " | \
cut -d " " -f 3
```

The backslash:

```bash
\
```

means:

> Continue this command on the next physical line.

Therefore the same command could be written as:

```bash
df $destination | tail -n 1 | tr -s " " | cut -d " " -f 3
```

The multi-line form is simply easier to read.

---

# 20. Start the Copy

```bash
cp $source $destination &
```

`cp` copies a file.

General form:

```bash
cp SOURCE DESTINATION
```

For example:

```bash
cp /data/source.iso /data/backup
```

copies:

```text
/data/source.iso
```

into:

```text
/data/backup
```

---

# 21. Background Operator `&`

The final character:

```bash
&
```

is extremely important.

Without it:

```bash
cp $source $destination
```

the shell waits until `cp` finishes.

Only after the entire file has been copied would the script continue.

That would make monitoring impossible.

With:

```bash
cp $source $destination &
```

the copy runs in the background.

The shell immediately continues to the following commands.

Conceptually:

```text
             +------------------------+
             | cp copies the file     |
             | in the background      |
             +------------------------+
                       |
                       | simultaneously
                       |
             +------------------------+
             | script checks progress |
             +------------------------+
```

---

# 22. Initialize `transferred`

```bash
transferred=0
```

Before monitoring begins:

```text
transferred = 0
```

This variable will later store the estimated number of 1 KB blocks transferred.

---

# 23. Initialize `percentage`

```bash
percentage=0
```

Initially:

```text
percentage = 0
```

which corresponds to:

```text
0%
```

---

# 24. Begin the Monitoring Loop

```bash
while [ $transferred -lt $size ]; do
```

This starts a `while` loop.

A `while` loop repeats as long as its condition remains true.

---

## `-lt`

The operator:

```bash
-lt
```

means:

```text
numerically less than
```

Therefore:

```bash
[ $transferred -lt $size ]
```

means:

> Is the estimated transferred amount smaller than the total source-file size?

Example:

```text
transferred = 3000
size        = 10000
```

Since:

```text
3000 < 10000
```

the loop continues.

---

# 25. Measure Current Used Space

Inside the loop:

```bash
currentUsed=$(df $destination | \
              tail -n 1 | \
              tr -s " " | \
              cut -d " " -f 3)
```

This performs the same file-system measurement as before.

The difference is timing.

`startUsed` was collected **before** the copy began.

`currentUsed` is collected **while** the copy is running.

Suppose:

```text
startUsed = 5000000
```

and later:

```text
currentUsed = 5020000
```

The file system is using:

```text
20000
```

more 1 KB blocks.

---

# 26. Calculate the Transferred Amount

```bash
let "transferred=currentUsed-startUsed"
```

This performs:

```text
transferred = currentUsed - startUsed
```

Example:

```text
currentUsed = 5020000
startUsed   = 5000000
```

Therefore:

```text
transferred = 20000
```

The script interprets this increase as approximately:

```text
20000 KB
```

of copied data.

---

# 27. Calculate the Percentage

```bash
let "percentage=transferred*100/size"
```

This applies:

```text
percentage = transferred × 100 / size
```

For example:

```text
transferred = 20000
size        = 100000
```

Then:

```text
percentage = 20000 × 100 / 100000
```

which produces:

```text
20
```

Therefore the copy is estimated to be:

```text
20%
```

complete.

---

# 28. Display Progress

```bash
echo "Progress: $percentage%"
```

If:

```text
percentage = 20
```

the command prints:

```text
Progress: 20%
```

As the copy continues, the output could be:

```text
Progress: 20%
Progress: 38%
Progress: 56%
Progress: 73%
Progress: 89%
Progress: 100%
```

---

# 29. Pause for One Second

```bash
sleep 1
```

`sleep` temporarily pauses execution.

The argument:

```text
1
```

means one second.

Therefore the script does not continuously run `df` as quickly as possible.

Instead, the monitoring sequence becomes:

```text
Measure
   ↓
Calculate
   ↓
Print
   ↓
Wait 1 second
   ↓
Measure again
```

---

# 30. End the Loop

```bash
done
```

`done` marks the end of the `while` loop.

Bash loop syntax is:

```bash
while CONDITION
do
    commands
done
```

This script uses the equivalent form:

```bash
while CONDITION; do
    commands
done
```

When:

```text
transferred >= size
```

the condition becomes false and the loop terminates.

---

# Important Variables

| Variable      | Purpose                                           |
| ------------- | ------------------------------------------------- |
| `$0`          | Name of the script                                |
| `$1`          | Source-file argument                              |
| `$2`          | Destination-directory argument                    |
| `$#`          | Number of arguments                               |
| `source`      | Stores `$1`                                       |
| `destination` | Stores `$2`                                       |
| `size`        | Source-file size in approximately 1 KB units      |
| `startUsed`   | Used destination file-system space before copying |
| `currentUsed` | Used destination file-system space during copying |
| `transferred` | Estimated amount transferred                      |
| `percentage`  | Estimated progress percentage                     |

---

# Important Commands

| Command | Purpose                            |
| ------- | ---------------------------------- |
| `echo`  | Print text                         |
| `exit`  | Terminate the script               |
| `ls`    | Obtain file information            |
| `cut`   | Extract a field from text          |
| `df`    | Display file-system disk usage     |
| `tail`  | Select lines from the end of input |
| `tr`    | Transform characters               |
| `cp`    | Copy files                         |
| `let`   | Perform integer arithmetic         |
| `sleep` | Pause execution                    |

---

# Important Bash Syntax

| Syntax           | Meaning                       |      |
| ---------------- | ----------------------------- | ---- |
| `$0`             | Script name                   |      |
| `$1`             | First argument                |      |
| `$2`             | Second argument               |      |
| `$#`             | Number of arguments           |      |
| `$variable`      | Read a variable               |      |
| `$(command)`     | Command substitution          |      |
| `                | `                             | Pipe |
| `&`              | Background execution          |      |
| `\`              | Continue command on next line |      |
| `!`              | Logical NOT                   |      |
| `-f`             | Test for regular file         |      |
| `-d`             | Test for directory            |      |
| `-ne`            | Numerically not equal         |      |
| `-lt`            | Numerically less than         |      |
| `if ... fi`      | Conditional statement         |      |
| `while ... done` | Loop                          |      |

---

# Example Execution

Suppose:

```bash
./copy_progress.sh large.iso /backup
```

and:

```text
large.iso size = 100000 KB
```

Before copying, the destination file system uses:

```text
startUsed = 500000 KB
```

The background copy starts:

```bash
cp large.iso /backup &
```

After one measurement:

```text
currentUsed = 515000 KB
```

Then:

```text
transferred = 515000 - 500000
            = 15000 KB
```

Progress:

```text
percentage = 15000 × 100 / 100000
           = 15%
```

Output:

```text
Progress: 15%
```

One second later:

```text
currentUsed = 540000 KB
```

Now:

```text
transferred = 40000 KB
```

and:

```text
percentage = 40%
```

Output:

```text
Progress: 40%
```

The script continues checking until the copied amount reaches the expected source-file size.

---

# Understanding `df`

A common source of confusion is the difference between:

```text
file size
```

and:

```text
file-system disk usage
```

Consider:

```bash
df /data/backup
```

This does **not** ask:

> How large is `/data/backup`?

It asks:

> Which file system contains `/data/backup`, and how much space is used and available on that file system?

Conceptually:

```text
SSD / Hard Disk
      |
      v
File-system storage area
      |
      +---- directories
      |        |
      |        +---- /data
      |               |
      |               +---- /data/backup
      |
      +---- files
```

`df` reports information about the entire file-system storage area.

The script takes advantage of this by measuring how much the `Used` value changes during the copy.

---

# Understanding the Pipeline

The command:

```bash
df $destination | \
tail -n 1 | \
tr -s " " | \
cut -d " " -f 3
```

can be understood step by step.

Suppose:

```bash
df /data/backup
```

returns:

```text
Filesystem     1K-blocks    Used    Available Use% Mounted on
/dev/sda7       41141492   5881472   33174616  16% /data
```

### Step 1

```bash
df $destination
```

produces:

```text
Filesystem     1K-blocks    Used    Available Use% Mounted on
/dev/sda7       41141492   5881472   33174616  16% /data
```

### Step 2

```bash
tail -n 1
```

removes the header:

```text
/dev/sda7       41141492   5881472   33174616  16% /data
```

### Step 3

```bash
tr -s " "
```

changes repeated spaces into single spaces:

```text
/dev/sda7 41141492 5881472 33174616 16% /data
```

### Step 4

```bash
cut -d " " -f 3
```

extracts:

```text
5881472
```

This is the `Used` value.

### Step 5

Command substitution:

```bash
startUsed=$(...)
```

stores that value:

```text
startUsed = 5881472
```

---

# Why the Copy Runs in the Background

Consider this version:

```bash
cp "$source" "$destination"
echo "Check progress"
```

The shell runs commands sequentially.

Therefore:

```text
Start cp
   |
   v
Wait
   |
   v
cp finishes
   |
   v
Run next command
```

The script cannot monitor the copy while waiting.

Adding:

```bash
&
```

changes the behavior:

```bash
cp "$source" "$destination" &
```

Now:

```text
Start cp
   |
   +----------------------+
   |                      |
   v                      v
cp keeps running      script continues
in background         immediately
```

This makes the monitoring loop possible.

---

# Limitations of the Progress Calculation

The script estimates progress based on **total file-system usage**, not directly on the number of bytes written by `cp`.

That distinction is important.

Suppose another program writes data to the same destination file system while the copy is running.

Then:

```text
currentUsed - startUsed
```

would include:

```text
space consumed by cp
+
space consumed by the other program
```

The script could therefore report a percentage that is higher than the actual copy progress.

Similarly, file-system caching, allocation behavior, sparse files, compression, or other file-system features can affect the relationship between logical file size and occupied disk blocks.

For a simple controlled environment in which the copy is the main operation changing the destination file-system usage, the calculation demonstrates the monitoring technique clearly.

---

# Summary

The script combines several fundamental Bash concepts into one program.

It first validates:

```text
number of arguments
source file
destination directory
```

Then it determines:

```text
source-file size
destination file-system used space
```

It starts:

```bash
cp $source $destination &
```

so the copy runs in the background.

While the copy runs, the script repeatedly performs:

```text
1. Measure current file-system usage
2. Calculate transferred amount
3. Calculate percentage
4. Print percentage
5. Wait one second
```

The core calculations are:

```bash
let "transferred=currentUsed-startUsed"
```

and:

```bash
let "percentage=transferred*100/size"
```

The complete idea is therefore:

```text
Background copy
       +
Destination file-system monitoring
       +
Arithmetic
       +
Periodic loop
       =
Estimated copy-progress display
```

This makes the program a useful example of how Bash scripts can coordinate background processes while simultaneously monitoring system information.
