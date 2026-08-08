# Bash Exercise — Copy Selected Files into a Destination Directory

## Task

Write a Bash script that receives a destination directory name followed by one or more filenames from the command line.

The script must:

1. Verify that the user supplied enough command-line arguments.
2. Create the destination directory if it does not already exist.
3. Process each filename provided after the directory name.
4. Ask the user whether each file should be copied into the destination directory.
5. Copy only the files for which the user confirms the operation.

---

## Command-Line Format

The script should be executed in the following form:

```bash
./myScript dir file1 file2 ... fileN
```

where:

- `dir` is the destination directory.
- `file1`, `file2`, ..., `fileN` are the files that may be copied into that directory.

The first command-line argument represents the directory name, while all remaining arguments represent filenames.

Example:

```bash
./myScript backup report.txt notes.txt program.c
```

In this example:

```text
$1 = backup
$2 = report.txt
$3 = notes.txt
$4 = program.c
```

---

## Argument Validation

The script must verify that at least:

- one destination directory, and
- one filename

have been provided.

If too few arguments are supplied, the script must display a usage message such as:

```text
Run: ./myScript dir file1 file2 ...
```

and terminate with an error status.

---

## Destination Directory

The first command-line argument is the destination directory.

If the directory does not exist, the script must create it before processing the files.

Example:

```text
Destination directory: backup
```

If `backup` does not exist, the script should create it.

---

## File Processing

The script must process every command-line argument after the destination directory as a filename.

For each file, the script must ask the user whether the file should be copied.

Example:

```text
report.txt in backup (y/n)?
```

If the user enters:

```text
y
```

the file should be copied into the destination directory.

If the user enters another value, the file should not be copied.

The script must then continue with the next filename.

---

## Copy Result

After attempting to copy a file, the script should indicate whether the operation succeeded or failed.

Example successful message:

```text
Copy done for backup/report.txt
```

Example failure message:

```text
Error for report.txt
```

---

## Example Execution

Suppose the following files exist in the current directory:

```text
report.txt
notes.txt
program.c
```

Run:

```bash
./myScript backup report.txt notes.txt program.c
```

A possible interaction is:

```text
Create directory backup
report.txt in backup (y/n)? y
Copy done for backup/report.txt
notes.txt in backup (y/n)? n
program.c in backup (y/n)? y
Copy done for backup/program.c
```

After execution, the destination directory should contain:

```text
backup/
├── report.txt
└── program.c
```

`notes.txt` is not copied because the user did not confirm it.

---

## Requirements

Your Bash script must:

- Use command-line positional parameters.
- Treat the first argument as the destination directory.
- Treat all remaining arguments as filenames.
- Check that at least two command-line arguments were provided.
- Display a usage message and terminate if the arguments are insufficient.
- Check whether the destination directory exists.
- Create the directory if necessary.
- Iterate through the filenames supplied on the command line.
- Skip the first parameter when processing files.
- Ask the user for confirmation before copying each file.
- Copy a file only when the user answers `y`.
- Report whether each attempted copy succeeds or fails.
- Exit normally after all filenames have been processed.
