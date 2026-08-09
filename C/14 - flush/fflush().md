# `fflush()` in C — Flushing Standard I/O Buffers

## Overview

In C, standard I/O functions such as `printf()`, `fprintf()`, `fputs()`, and `fwrite()` often use a **buffer**.

A buffer is a temporary area in memory where output data can wait before it is actually written to its destination, such as:

- the terminal
- a file
- a pipe
- another output stream

The `fflush()` function forces pending output data in a stream's buffer to be written immediately.

---

## 1. Why Does C Use Buffers?

Writing directly to a file or terminal can be relatively expensive.

Instead of performing an output operation for every small piece of data, C can collect data in memory first.

Conceptually:

```text
Program
   |
   | printf("Hello");
   v
+------------------+
| Output buffer    |
| "Hello"          |
+------------------+
   |
   | later
   v
Terminal / File
```

This improves efficiency because several small writes can be combined into a larger write.

---

## 2. What Does "Flush" Mean?

To **flush a buffer** means:

> Write the data currently waiting in the buffer to the associated output stream.

For example:

```c
printf("Hello");
```

The text may first be placed in the `stdout` buffer.

Then:

```c
fflush(stdout);
```

forces the pending output to be written immediately.

Conceptually:

```text
Before fflush():

printf("Hello")
      |
      v
+-------------+
| "Hello"     |
| stdout      |
| buffer      |
+-------------+


After fflush(stdout):

+-------------+
| empty       |
| stdout      |
| buffer      |
+-------------+
      |
      v
Terminal displays:

Hello
```

---

## 3. Header File

`fflush()` is declared in:

```c
#include <stdio.h>
```

---

## 4. Function Prototype

```c
int fflush(FILE *stream);
```

The argument is a pointer to a `FILE` stream.

Common examples are:

```c
fflush(stdout);
fflush(stderr);
```

You can also flush an output file opened with `fopen()`:

```c
FILE *fp = fopen("output.txt", "w");

fprintf(fp, "Hello");
fflush(fp);
```

---

## 5. `fflush(stdout)`

`stdout` is the standard output stream.

For example:

```c
#include <stdio.h>

int main(void)
{
    printf("Hello");
    fflush(stdout);

    return 0;
}
```

The important line is:

```c
fflush(stdout);
```

It means:

> Write any output currently waiting in the `stdout` buffer now.

---

## 6. Example Without `fflush()`

Consider:

```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Waiting...");

    sleep(5);

    printf("Done\n");

    return 0;
}
```

Depending on how `stdout` is buffered, `Waiting...` may remain in the buffer for some time.

Conceptually:

```text
printf("Waiting...")
        |
        v
stdout buffer
        |
        | may still be waiting
        v
sleep(5)
```

The program has executed `printf()`, but the text is not necessarily guaranteed to have been written to the terminal at that exact moment.

---

## 7. Example With `fflush()`

```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Waiting...");
    fflush(stdout);

    sleep(5);

    printf("Done\n");

    return 0;
}
```

Execution:

```text
printf("Waiting...")
        |
        v
stdout buffer

fflush(stdout)
        |
        v
"Waiting..." is written immediately

sleep(5)
        |
        v
program waits

printf("Done\n")
```

So `fflush()` is useful when you need output to become visible before the program continues.

---

## 8. A Common Example: Printing a Prompt

Suppose a program asks the user for input:

```c
#include <stdio.h>

int main(void)
{
    int number;

    printf("Enter a number: ");
    fflush(stdout);

    scanf("%d", &number);

    printf("You entered: %d\n", number);

    return 0;
}
```

Why use:

```c
fflush(stdout);
```

after the prompt?

Because the prompt does not end with `\n`.

Depending on buffering, it may still be waiting in the output buffer.

By flushing `stdout`, we make sure the user sees:

```text
Enter a number:
```

before the program waits for input.

---

## 9. Flushing a File

`fflush()` is not only for the terminal.

It can also be used with files:

```c
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("data.txt", "w");

    if (fp == NULL)
    {
        return 1;
    }

    fprintf(fp, "Operating Systems\n");

    fflush(fp);

    fclose(fp);

    return 0;
}
```

Here:

```c
fflush(fp);
```

requests that buffered output for `fp` be passed to the underlying file system.

---

## 10. Return Value

`fflush()` returns an integer.

```c
int result = fflush(stdout);
```

On success:

```text
0
```

is returned.

On failure:

```text
EOF
```

is returned.

Example:

```c
if (fflush(stdout) == EOF)
{
    perror("fflush");
}
```

---

## 11. `fflush(NULL)`

C also allows:

```c
fflush(NULL);
```

This means:

> Flush all open output streams.

Example:

```c
#include <stdio.h>

int main(void)
{
    printf("Hello\n");

    FILE *fp = fopen("data.txt", "w");

    if (fp != NULL)
    {
        fprintf(fp, "Some data\n");
    }

    fflush(NULL);

    if (fp != NULL)
    {
        fclose(fp);
    }

    return 0;
}
```

---

## 12. `fflush()` Does Not Disable Buffering

This is an important distinction.

```c
fflush(stdout);
```

does **not** mean:

> Disable the `stdout` buffer permanently.

It means:

> Flush the data that is currently waiting in the buffer.

After that, the stream can continue buffering future output.

For example:

```c
printf("A");
fflush(stdout);

printf("B");
```

After flushing `A`, the later output `B` can again enter the `stdout` buffer.

---

## 13. `fflush()` vs `setbuf()`

These two functions are related to buffering, but they do different things.

### `fflush()`

```c
fflush(stdout);
```

means:

> Keep using buffering, but write the currently buffered output now.

Conceptually:

```text
buffer enabled
      |
      v
data waits in buffer
      |
      | fflush()
      v
data is written
```

### `setbuf()`

For example:

```c
setbuf(stdout, NULL);
```

means:

> Make `stdout` unbuffered.

Now future output is not stored in the normal standard-I/O buffer first.

Conceptually:

```text
setbuf(stdout, NULL)

printf()
   |
   v
output directly
```

So:

| Function | Meaning |
|---|---|
| `fflush(stdout)` | Flush pending output now |
| `setbuf(stdout, NULL)` | Disable buffering for `stdout` |

---

## 14. `stdout` Buffering

A common simplification is to say that standard output is buffered.

More precisely, the behavior depends on where `stdout` is connected.

Typical behavior is:

- terminal → often **line buffered**
- file/redirection → often **fully buffered**

For example:

```c
printf("Hello\n");
```

on a terminal often causes output to appear because the newline can trigger a flush for a line-buffered stream.

But:

```c
printf("Hello");
```

has no newline, so the text may remain buffered.

This is why explicitly calling:

```c
fflush(stdout);
```

is useful when immediate visibility matters.

---

## 15. `stderr`

`stderr` is the standard error stream.

Example:

```c
fprintf(stderr, "An error occurred\n");
```

It is intended for diagnostic and error messages and is normally configured so that error output is not delayed like ordinary buffered output.

That is useful because error messages should generally be visible immediately.

---

## 16. Important Warning: Do Not Use `fflush(stdin)`

A common mistake is:

```c
fflush(stdin);
```

In standard C, `fflush()` is defined for output streams, and for update streams when the most recent operation was output.

Using:

```c
fflush(stdin);
```

to "clear the keyboard buffer" is **not portable standard C**.

Do not rely on it.

---

## 17. Why `fflush()` Matters With Multiple Processes

In operating systems programming, buffering can become especially important when using functions such as:

```c
fork();
```

A process may have data waiting inside its standard-I/O buffers.

If the process is duplicated with `fork()`, the child receives a copy of the process memory, including the state of standard-I/O buffers.

That can sometimes lead to duplicated output if the buffer is later flushed by more than one process.

Example idea:

```c
printf("Hello");

fork();
```

If `"Hello"` is still buffered when `fork()` executes, both parent and child may inherit a copy of that buffered data.

Therefore, when appropriate, a program can flush output before `fork()`:

```c
printf("Hello");
fflush(stdout);

fork();
```

This ensures that the pending output has already been written before the process is duplicated.

---

## 18. Complete Example

```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Program starting...");
    fflush(stdout);

    sleep(2);

    printf("done\n");

    return 0;
}
```

### Step-by-step

```text
1. printf("Program starting...")
       |
       v
   text enters stdout

2. fflush(stdout)
       |
       v
   pending stdout data is written

3. sleep(2)
       |
       v
   program waits for 2 seconds

4. printf("done\n")
       |
       v
   final message is printed
```

Expected visible behavior:

```text
Program starting...
```

Then, after approximately two seconds:

```text
done
```

---

## 19. Simple Analogy

Think of a buffer as a bucket.

You keep putting water into the bucket:

```text
Program output
      |
      v
   [ BUCKET ]
```

Normally, you may wait until the bucket is full before emptying it.

Calling:

```c
fflush(stdout);
```

is like saying:

> "Empty the bucket right now, even if it is not full."

So:

```text
Before fflush:

[ Hello.... ]


After fflush:

[          ]  ----->  Terminal/File
```

---

## 20. Summary

The main idea is:

```text
Program output
      |
      v
    Buffer
      |
      | fflush()
      v
Actual output destination
```

Remember:

```c
fflush(stdout);
```

means:

> Write the pending buffered data of `stdout` now.

Key points:

- `fflush()` is declared in `<stdio.h>`.
- Its prototype is:

  ```c
  int fflush(FILE *stream);
  ```

- `fflush(stdout)` flushes pending standard output.
- `fflush(fp)` flushes pending output associated with file stream `fp`.
- `fflush(NULL)` flushes all open output streams.
- Success returns `0`.
- Failure returns `EOF`.
- `fflush()` does not permanently disable buffering.
- `setbuf(stdout, NULL)` disables buffering; it is different from `fflush(stdout)`.
- `fflush(stdin)` should not be used as a portable way to clear input.
- Flushing is especially important when output must appear immediately or before operations such as `fork()`.

---

## Quick Reference

```c
#include <stdio.h>

fflush(stdout);   // Flush standard output
fflush(stderr);   // Flush standard error stream
fflush(fp);       // Flush a particular output file stream
fflush(NULL);     // Flush all open output streams
```

The simplest definition to remember is:

> **`fflush()` forces pending buffered output to be written to its destination immediately.**
