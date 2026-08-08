# Bash Exercise — Swap Two Columns in a File

## Task

Write a Bash script that receives a filename from the command line and swaps the two columns of data stored in that file.

The script must overwrite the original file with the modified content.

## Input Format

The input file contains two columns of data.

Example:

```text
7 3
2 23
5 0
```

## Expected Result

After running the script, the same file should contain:

```text
3 7
23 2
0 5
```

## Requirements

- Use Bash shell scripting.
- Receive the filename as a command-line argument.
- Read the file line by line.
- Each line contains exactly two values.
- Swap the first and second values of every line.
- Write the transformed data back to the same file.
- The input and final output filenames must be the same.

## Additional Requirement

Implement the column swap **without printing the swapped values to the terminal as the final output**.

The transformed values must be redirected and stored in another file first.

In other words:

- Do not rely on displaying the swapped values on standard output as the final result.
- Store the swapped output in a temporary or secondary file.
- After processing is complete, use that file to replace the original input file.
- The final modified data must be stored in the original filename.
