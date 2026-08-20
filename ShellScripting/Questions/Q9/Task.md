# Bash Exercise: Compare Matching Text Files Across Directories

## Objective

Write a Bash script that compares matching text files stored in two directories and generates three types of output files in a third directory.

## Requirements

The script must receive exactly **4 command-line arguments**:

```bash
./script.sh dir1 dir2 dir3 n
```

where:

- `dir1` is the first input directory.
- `dir2` is the second input directory.
- `dir3` is the output directory.
- `n` is an integer representing a minimum number of lines.

## Tasks

The script must:

1. Verify that exactly four arguments are provided.
2. Verify that `dir1` and `dir2` are valid directories.
3. Create `dir3` if it does not already exist.
4. Find files that:
   - exist in both `dir1` and `dir2`,
   - have the same filename,
   - have the `.txt` extension,
   - contain more than `n` lines in both directories.
5. For every valid pair of matching files, create three output files inside `dir3`.

## Output Files

Suppose the matching file is:

```text
example.txt
```

The script must create:

```text
example.eq
example.dif
example.cat
```

### `.eq`

Contains the lines that are present in both matching text files.

### `.dif`

Contains the lines that are different between the two matching text files.

### `.cat`

Contains the concatenation of the complete contents of both matching text files.

## Example

Assume:

```text
dir1/
├── a.txt
├── b.txt
└── test.c

dir2/
├── a.txt
├── b.txt
└── x.txt
```

and the script is executed as:

```bash
./script.sh dir1 dir2 dir3 5
```

Only files that satisfy all of the following conditions are processed:

- same filename in both directories,
- `.txt` extension,
- more than 5 lines in both copies.

If `a.txt` satisfies these conditions, the script should create:

```text
dir3/
├── a.eq
├── a.dif
└── a.cat
```

## Summary

For every sufficiently long `.txt` file that exists with the same name in both input directories:

- save common lines in `.eq`,
- save different lines in `.dif`,
- save the concatenated contents in `.cat`.
