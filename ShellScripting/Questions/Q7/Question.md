# Bash Exercise — Monitor the Progress of a Background File Copy

## Task

Write a Bash script that receives:

1. The path of a **source file**
2. A **destination path**

The script must copy the source file to the destination **in the background** and periodically display the percentage of the copy operation that has been completed.

---

## Command-Line Format

The script should be executed in the following form:

```bash
./script.sh SOURCE_FILE DESTINATION_PATH
```

Example:

```bash
./script.sh /data/source.iso /data/backup
```

In this example:

```text
$1 = /data/source.iso
$2 = /data/backup
```

---

## Requirements

Your script must:

- Check that the required command-line parameters have been provided correctly.
- Use the first argument as the source file.
- Use the second argument as the destination path.
- Start the copy operation in the **background**.
- Copy the source file into the destination path.
- Monitor the space occupied on the destination file system.
- Check the destination space at regular intervals of **1 second**.
- Display the percentage of progress of the copy operation on the screen.
- Continue monitoring until the copy operation is complete.

---

## Disk-Space Information

The `df` command can be used to display disk-space information for the file system containing a given path.

Example:

```bash
df /data/backup
```

Possible output:

```text
Filesystem     1K-blocks    Used    Available Use% Mounted on
/dev/sda7       41141492   5881472   33174616  16% /data
```

The relevant fields are:

```text
1K-blocks  -> total file-system space
Used       -> currently used space
Available  -> currently available space
```

The fields are separated by spaces.

For this exercise, assume that no other separator is used and that spaces do not appear inside the individual fields.

---

## Monitoring Interval

The script should pause for one second between two consecutive checks.

The following command may be used:

```bash
sleep 1
```

This suspends the script for approximately one second before the next progress check.

---

## Expected Behavior

A possible execution could look like:

```bash
./script.sh /data/source.iso /data/backup
```

While the file is being copied in the background, the script should periodically display progress information, for example:

```text
Copy progress: 12%
Copy progress: 27%
Copy progress: 43%
Copy progress: 68%
Copy progress: 91%
Copy progress: 100%
```

The exact percentages depend on the file size and the speed of the copy operation.

---

## Goal

The final script must combine:

- command-line parameter checking,
- background execution,
- file copying,
- disk-space analysis with `df`,
- periodic monitoring with `sleep`,
- and progress-percentage computation.
