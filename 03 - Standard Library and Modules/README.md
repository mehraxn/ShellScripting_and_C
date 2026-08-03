# Difference Between Module and Standard Library in C

This document explains the difference between a **module** and the **standard library** in the C programming language, with examples and clear distinctions.

---

## 🔹 What is a Standard Library in C?

The **C Standard Library** is a collection of **predefined header files and functions** that provide common functionality like:

* Input/Output
* Memory management
* String manipulation
* Math operations

### 📦 Examples of Standard Library Headers

| Header       | Purpose                                              |
| ------------ | ---------------------------------------------------- |
| `<stdio.h>`  | Input and output (e.g., `printf`, `scanf`)           |
| `<stdlib.h>` | General utilities (e.g., `malloc`, `free`, `atoi`)   |
| `<string.h>` | String handling (e.g., `strcpy`, `strlen`, `strdup`) |
| `<math.h>`   | Mathematical functions (e.g., `sin`, `sqrt`)         |

### ✅ Example Using Standard Library:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char name[] = "Alice";
    printf("Length: %zu\n", strlen(name));
    return 0;
}
```

---

## 🔹 What is a Module in C?

In C, a **module** typically refers to a **collection of functions and definitions** grouped in **separate `.c` and `.h` files** for organization and reusability.

> C does not have formal "modules" like Python or modern C++ (C++20 Modules), but developers build modular systems manually using files.

### 🗂️ Components of a Module

* **Header file (`.h`)**: Declarations (function prototypes, macros, etc.)
* **Implementation file (`.c`)**: Definitions (actual function code)

### ✅ Example: Creating a Math Utilities Module

#### `math_utils.h`

```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int add(int a, int b);
int square(int x);

#endif
```

#### `math_utils.c`

```c
#include "math_utils.h"

int add(int a, int b) {
    return a + b;
}

int square(int x) {
    return x * x;
}
```

#### `main.c`

```c
#include <stdio.h>
#include "math_utils.h"

int main() {
    printf("Sum: %d\n", add(3, 4));
    printf("Square: %d\n", square(5));
    return 0;
}
```

Compile with:

```bash
gcc main.c math_utils.c -o app
```

---

## 🔍 Key Differences Between Module and Standard Library

| Feature            | Standard Library                      | User Module                          |
| ------------------ | ------------------------------------- | ------------------------------------ |
| Provided By        | C language + compiler                 | User/developer                       |
| Form               | Header files only (e.g., `<stdio.h>`) | Header + Source files (`.h` + `.c`)  |
| Built-in Functions | Yes (e.g., `printf`, `malloc`)        | No — must define them yourself       |
| Compilation        | Included automatically                | Must be compiled and linked manually |
| Portability        | Highly portable and consistent        | Depends on developer implementation  |

---

## 📌 Summary

* **Standard Library**: Built-in functionality you can use immediately with `#include <...>`.
* **Module**: A user-defined way to organize code in reusable `.c` and `.h` files.

Both are essential to building clean, reusable, and maintainable C programs.

Let me know if you’d like a project scaffold showing both in action!
