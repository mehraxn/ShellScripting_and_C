# Pthreads: Passing the Same Loop Variable to Multiple Threads — Buggy Example

## Overview

This example demonstrates a common mistake when creating multiple POSIX threads (`pthreads`) in C: **passing the address of the same loop variable to every thread**.

The program creates four threads. The intention is that each thread should receive a different logical number:

```text
Thread 0 -> 0
Thread 1 -> 1
Thread 2 -> 2
Thread 3 -> 3
```

However, the program does **not** give each thread its own copy of the number. Instead, every thread receives the address of the same variable, `t`. Because the main thread keeps changing `t` while the created threads may read it at different times, the values observed by the threads are not reliable.

This is a classic example of a **race condition caused by sharing a changing variable without synchronization**.

---

## Complete Buggy Program

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

void *tF(void *par)
{
    int *tidP;
    int tid;

    tidP = (int *)par;
    tid = *tidP;

    printf("Thread read t = %d\n", tid);

    pthread_exit(NULL);
}

int main(void)
{
    pthread_t th[NUM_THREADS];
    int rc;
    int t;

    for (t = 0; t < NUM_THREADS; t++)
    {
        rc = pthread_create(&th[t], NULL, tF, (void *)&t);

        if (rc != 0)
        {
            exit(-1);
        }
    }

    pthread_exit(NULL);
}
```

---

## What the Program Is Trying to Do

The program creates `NUM_THREADS` threads. Since:

```c
#define NUM_THREADS 4
```

it creates four threads.

The loop variable `t` takes these values:

```text
0 -> 1 -> 2 -> 3
```

The intended idea is:

```text
t = 0 -> create the first thread and give it 0
t = 1 -> create the second thread and give it 1
t = 2 -> create the third thread and give it 2
t = 3 -> create the fourth thread and give it 3
```

But the program does something different: it passes `&t`, which is the **address of `t`**, rather than a separate copy of its current value.

---

# Line-by-Line Explanation

## 1. Include the standard input/output library

```c
#include <stdio.h>
```

This library provides standard input/output functions.

The program needs it because it uses:

```c
printf()
```

---

## 2. Include the standard library

```c
#include <stdlib.h>
```

This library provides several general-purpose functions.

In this program it is needed for:

```c
exit()
```

---

## 3. Include the Pthreads library

```c
#include <pthread.h>
```

This header provides the POSIX thread types and functions used by the program, including:

```c
pthread_t
pthread_create()
pthread_exit()
```

When compiling a pthread program, the pthread library must also be linked.

For example:

```bash
gcc -Wall -g -o program Main.c -lpthread
```

---

## 4. Define the number of threads

```c
#define NUM_THREADS 4
```

This creates a symbolic constant named `NUM_THREADS` with value `4`.

Therefore, the program will attempt to create four threads.

---

# The Thread Function

## 5. Define the function executed by every created thread

```c
void *tF(void *par)
```

`tF` is the function that every newly created thread will execute.

A pthread start routine has the general form:

```c
void *function_name(void *arg)
```

So the function:

- receives one `void *` argument;
- returns a `void *` value.

The parameter:

```c
par
```

will receive the fourth argument supplied to `pthread_create()`.

In this program, that argument will be:

```c
(void *)&t
```

Therefore, `par` receives the address of the variable `t`.

---

## 6. Declare an integer pointer

```c
int *tidP;
```

`tidP` is a pointer to an integer.

It will eventually point to the integer variable whose address was passed to the thread.

In this program, that variable is `t` from `main()`.

---

## 7. Declare a local integer

```c
int tid;
```

`tid` is a local variable belonging to the current thread.

Each thread has its own copy of this local variable because each thread has its own stack.

The program uses `tid` to store the value that the thread reads from `t`.

Do not confuse this variable with a real pthread identifier. The real pthread identifiers are stored in the `pthread_t th[]` array in `main()`.

---

## 8. Convert the generic pointer to an integer pointer

```c
tidP = (int *)par;
```

`par` has type:

```c
void *
```

but the program knows that it actually contains the address of an integer.

Therefore it casts `par` to:

```c
int *
```

After this instruction, conceptually:

```text
tidP -----> t
```

The important point is that every created thread receives the address of the **same `t`**.

---

## 9. Read the value stored at that address

```c
tid = *tidP;
```

`tidP` contains the address of `t`.

The `*` operator dereferences the pointer, meaning:

> Go to the memory address stored in `tidP` and read the integer currently stored there.

So this is effectively reading the **current value of `t`**.

For example, if `t` currently contains `2`, then:

```text
tid = 2
```

The key word is **currently**. The thread does not necessarily read the value that `t` had when the thread was created.

---

## 10. Print the value read by the thread

```c
printf("Thread read t = %d\n", tid);
```

This prints the value that the thread copied into `tid`.

For example:

```text
Thread read t = 2
```

Because of the bug explained later, the four threads are not guaranteed to print `0`, `1`, `2`, and `3`.

---

## 11. Terminate the created thread

```c
pthread_exit(NULL);
```

This terminates only the thread executing `tF()`.

`NULL` means that the thread does not return a useful termination value.

---

# The `main()` Function

## 12. Start the main function

```c
int main(void)
```

Execution of the program begins in `main()`.

Initially, the process has its main thread. The main thread then creates additional threads using `pthread_create()`.

---

## 13. Create an array for the real thread identifiers

```c
pthread_t th[NUM_THREADS];
```

Since `NUM_THREADS` is `4`, this creates:

```text
th[0]
th[1]
th[2]
th[3]
```

Each element stores the actual `pthread_t` identifier of one created thread.

Conceptually:

```text
th[0] -> identifier of the first thread
th[1] -> identifier of the second thread
th[2] -> identifier of the third thread
th[3] -> identifier of the fourth thread
```

---

## 14. Declare the return-code variable

```c
int rc;
```

`rc` stores the return value of `pthread_create()`.

For `pthread_create()`:

```text
0       -> success
nonzero -> error
```

---

## 15. Declare the loop variable

```c
int t;
```

`t` is the loop variable used while creating the threads.

It will take the values:

```text
0, 1, 2, 3
```

There is only **one variable `t`**.

Its value changes during the loop, but its memory address remains the same.

For example, conceptually:

```text
Address of t: 0x5000

first iteration:  0x5000 contains 0
second iteration: 0x5000 contains 1
third iteration:  0x5000 contains 2
fourth iteration: 0x5000 contains 3
```

---

## 16. Loop four times

```c
for (t = 0; t < NUM_THREADS; t++)
```

The loop executes for:

```text
t = 0
t = 1
t = 2
t = 3
```

At each iteration, the main thread creates one new thread.

---

## 17. Create a new thread

```c
rc = pthread_create(&th[t], NULL, tF, (void *)&t);
```

This is the most important line in the entire program.

The four arguments are:

```c
pthread_create(
    &th[t],
    NULL,
    tF,
    (void *)&t
);
```

### First argument

```c
&th[t]
```

This tells `pthread_create()` where to store the identifier of the newly created thread.

For example, when:

```text
t = 0
```

the new thread identifier is stored in:

```c
th[0]
```

---

### Second argument

```c
NULL
```

This means that the thread is created with default attributes.

---

### Third argument

```c
tF
```

This tells the new thread which function to execute.

The new thread starts executing:

```c
tF()
```

---

### Fourth argument

```c
(void *)&t
```

This is the argument passed to `tF()`.

`&t` means:

> the memory address of `t`.

The cast:

```c
(void *)
```

converts that address to the generic pointer type required by `pthread_create()`.

Therefore:

```c
(void *)&t
```

means:

> Pass the address of the loop variable `t` to the new thread.

This is where the bug originates.

---

## 18. Check whether thread creation failed

```c
if (rc != 0)
```

If `pthread_create()` returned a nonzero value, the thread could not be created successfully.

---

## 19. Terminate the process on a creation error

```c
exit(-1);
```

`exit()` terminates the entire process.

Therefore, if thread creation fails, all threads belonging to this process terminate as well.

---

## 20. Terminate only the main thread

```c
pthread_exit(NULL);
```

After the loop has created the threads, the main thread terminates itself using `pthread_exit()`.

This is important because `pthread_exit(NULL)` terminates the **calling thread**, not the entire process.

Therefore, created threads that have not finished yet are allowed to continue running.

---

# The Bug

The buggy instruction is:

```c
pthread_create(&th[t], NULL, tF, (void *)&t);
```

More specifically, the problem is:

```c
&t
```

Every thread receives the address of the **same variable `t`**.

The program does **not** create a separate copy of `t` for each thread.

Conceptually:

```text
                    one variable
                        t
                        ^
                        |
           +------------+------------+
           |            |            |
        Thread 0     Thread 1     Thread 2
                                      |
                                   Thread 3
```

All four threads eventually execute:

```c
tid = *tidP;
```

which means that all of them read the value stored in that same variable.

At the same time, the main thread is changing `t` because of the loop:

```text
0 -> 1 -> 2 -> 3 -> 4
```

---

# Why Is That a Problem?

Creating a thread does **not** mean that the new thread immediately executes its function before the main thread continues.

After `pthread_create()`, both threads may be ready to run:

```text
Main thread
Created thread
```

The operating system scheduler decides when each one executes.

Consider this possible sequence.

### Step 1

The main thread has:

```text
t = 0
```

and creates the first thread:

```c
pthread_create(..., &t);
```

The first thread receives the address of `t`.

We would like that first thread to read:

```text
0
```

---

### Step 2

However, the first thread may not execute immediately.

The main thread continues the loop and changes:

```text
t = 1
```

---

### Step 3

Only now does the first created thread execute:

```c
tid = *tidP;
```

Since `tidP` points to `t`, and `t` now contains `1`, the first thread reads:

```text
1
```

instead of the intended:

```text
0
```

---

# A Possible Execution Timeline

Suppose the operating system schedules execution like this:

```text
Main: t = 0
Main: create Thread 0 with &t

Main: t = 1
Main: create Thread 1 with &t

Thread 0 runs
Thread 0 reads t = 1

Main: t = 2
Main: create Thread 2 with &t

Thread 1 runs
Thread 1 reads t = 2

Main: t = 3
Main: create Thread 3 with &t

Main finishes the loop
Now t becomes 4

Thread 2 runs
Thread 2 reads t = 4

Thread 3 runs
Thread 3 reads t = 4
```

One possible output could therefore be:

```text
Thread read t = 1
Thread read t = 2
Thread read t = 4
Thread read t = 4
```

This is only an example. The exact output is not guaranteed.

---

# What We Wanted vs. What Can Happen

The intended result is:

```text
Thread 0 -> 0
Thread 1 -> 1
Thread 2 -> 2
Thread 3 -> 3
```

But all threads actually share access to:

```text
t
```

and `t` is continuously changing.

Therefore, outcomes such as these are possible:

```text
1 2 4 4
```

or:

```text
2 2 3 4
```

or other orders and repeated values.

The exact behavior depends on thread scheduling.

---

# Why This Is a Race Condition

A race condition occurs when the behavior of a concurrent program depends on the timing/order in which threads access shared data.

In this program:

```text
Main thread       -> writes/modifies t
Created threads   -> read t
```

These operations happen concurrently, with no synchronization protecting access to `t`.

Therefore the value seen by a thread depends on **when that thread happens to execute**.

That is why the result is unreliable.

---

# Important Memory Picture

The incorrect mental model is:

```text
Thread 0 -> its own t = 0
Thread 1 -> its own t = 1
Thread 2 -> its own t = 2
Thread 3 -> its own t = 3
```

That is **not** what the program creates.

The real situation is:

```text
               +----------------+
               |       t        |
               | current value  |
               +----------------+
                  ^   ^   ^   ^
                  |   |   |   |
                 T0  T1  T2  T3
```

Every thread has its own local variables such as `tidP` and `tid`, but each thread's `tidP` points to the same shared `t`.

---

# `tid` Is Not the Real Thread Identifier

Inside the thread function we have:

```c
int tid;
```

Despite its name, this is **not** the real POSIX thread identifier.

The real thread identifiers are stored in:

```c
pthread_t th[NUM_THREADS];
```

So:

```text
th[0], th[1], th[2], th[3]
```

contain the real `pthread_t` values.

The local variable:

```c
int tid;
```

is simply being used as a logical numeric label copied from `t`.

---

# Why the Thread Function Uses `void *`

The function is declared as:

```c
void *tF(void *par)
```

A function used directly as the start routine of `pthread_create()` follows this general form:

```c
void *function_name(void *arg)
```

The argument is a `void *` so that a generic pointer can be passed to the thread.

In this example:

```c
(void *)&t
```

is passed from `main()`, and the thread converts it back with:

```c
tidP = (int *)par;
```

A `void *` can therefore be used to pass addresses of different kinds of data, provided that the thread knows what type it should cast the pointer back to.

---

# Key Takeaway

The code is buggy because:

```c
(void *)&t
```

passes the **same address** to every thread, while the main thread keeps modifying the value stored at that address.

The central idea to remember is:

> Passing the address of a variable does not freeze or copy its current value. It gives the thread access to that same memory location.

Therefore:

```text
All threads -> same address -> same changing variable t
```

instead of:

```text
Thread 0 -> independent 0
Thread 1 -> independent 1
Thread 2 -> independent 2
Thread 3 -> independent 3
```

A correct implementation must ensure that every thread receives stable data intended specifically for that thread, rather than all threads reading the same changing loop variable.

---

## Compile and Run

Compile with:

```bash
gcc -Wall -g -o program Main.c -lpthread
```

Run with:

```bash
./program
```

Do not expect one fixed output: because the program contains a race condition, the values and ordering printed by the threads can vary between executions.
