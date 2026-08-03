# README — Passing Dynamic 2D Arrays in C (Jagged)

## The Rule (up front)

When you pass a **dynamically allocated 2D array whose rows may have different lengths** in C, pass it like this:

```c
void func(int **a, int rows, int *colSizes);
```

* `a` is an array of row pointers (`int**`).
* `rows` is the number of rows.
* `colSizes[i]` is the number of columns in row `i`.

This is the most general dynamic representation because C functions don’t know array lengths unless you pass them explicitly.

---

## Why this shape is necessary

* In C, arrays **decay to pointers** when passed to functions. The callee cannot infer sizes.
* A dynamic 2D structure built as `int**` is **jagged**: each row is a separate allocation and may have a different length.
* Therefore, to iterate safely, you must provide:

  * how many rows there are (`rows`), and
  * how many columns each specific row has (`colSizes[i]`).

Memory sketch:

```
a (int**)
  ├─> a[0] ──> [ x x x ]        // colSizes[0] = 3
  ├─> a[1] ──> [ y y ]          // colSizes[1] = 2
  ├─> a[2] ──> [ z z z z ]      // colSizes[2] = 4
  └─> ...

colSizes (int*) = [3, 2, 4, ...]
rows = number of row pointers stored in a
```

---

## Example 1 — Printing a jagged matrix

A small, complete program that allocates, fills, prints, and frees a jagged 2D array using `rows` + `colSizes`.

```c
#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **a, int rows, int *colSizes) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < colSizes[i]; ++j) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int rows = 3;
    int *colSizes = malloc(rows * sizeof(int));
    colSizes[0] = 3; colSizes[1] = 2; colSizes[2] = 4;

    int **a = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        a[i] = malloc(colSizes[i] * sizeof(int));
        for (int j = 0; j < colSizes[i]; ++j) a[i][j] = (i+1) * 10 + j; // sample data
    }

    print_matrix(a, rows, colSizes);

    for (int i = 0; i < rows; ++i) free(a[i]);
    free(a);
    free(colSizes);
    return 0;
}
```

---

## Example 2 — Row-wise aggregation (sum of maximums)

Use the same signature to implement logic that **depends on per-row lengths**.

```c
#include <limits.h>

int sum_of_row_max(int **a, int rows, int *colSizes) {
    int total = 0;
    for (int i = 0; i < rows; ++i) {
        int mx = INT_MIN;
        for (int j = 0; j < colSizes[i]; ++j) if (a[i][j] > mx) mx = a[i][j];
        total += mx;
    }
    return total;
}
```

---

## Example 3 — Appending an element to a specific row

Jagged layout lets each row grow independently. You update the target row and **adjust `colSizes[i]`**.

```c
#include <stdlib.h>

int append_to_row(int **a, int rows, int *colSizes, int i, int value) {
    if (i < 0 || i >= rows) return 0; // out of range
    int newLen = colSizes[i] + 1;
    int *p = realloc(a[i], newLen * sizeof(int));
    if (!p) return 0;
    a[i] = p;
    a[i][newLen - 1] = value;
    colSizes[i] = newLen;
    return 1;
}
```

---

## Example 4 — Building from input row lengths

A typical pattern when row sizes come from input.

```c
#include <stdio.h>
#include <stdlib.h>

void read_and_print(void) {
    int rows; scanf("%d", &rows);
    int *colSizes = malloc(rows * sizeof(int));
    for (int i = 0; i < rows; ++i) scanf("%d", &colSizes[i]);

    int **a = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        a[i] = malloc(colSizes[i] * sizeof(int));
        for (int j = 0; j < colSizes[i]; ++j) scanf("%d", &a[i][j]);
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < colSizes[i]; ++j) printf("%d%c", a[i][j], j+1==colSizes[i]? '\n' : ' ');
    }

    for (int i = 0; i < rows; ++i) free(a[i]);
    free(a);
    free(colSizes);
}
```

---

## Common pitfalls (and how to avoid them)

* **Assuming rectangular shape:** With `int**`, rows can be different lengths. Always bound `j` by `colSizes[i]`.
* **Using `sizeof` to get lengths:** `sizeof(a[i])` gives the size of a pointer, **not** the row length. Only `colSizes[i]` is authoritative.
* **Forgetting to free rows:** Free **each row** first, then the array of pointers, then the `colSizes` array.
* **Out-of-bounds writes after `realloc`:** Always check the return of `realloc` and update the pointer before writing.
* **Mixing layouts:** Don’t index a flat contiguous block (`int*`) as if it were jagged (`int**`), or vice versa.

---

## FAQ

**Q: What if every row has the same number of columns?**
You can still use the `rows` + `colSizes` pattern (set all `colSizes[i]` to the same value). It remains general and self-describing. If you know at design time that all rows are equal length, other representations exist, but this README focuses on the general dynamic case where per-row lengths may vary.

**Q: Why not store lengths inside each row allocation?**
C’s standard `malloc`/`realloc` don’t provide portable, safe per-block length queries. Keeping sizes in a parallel `colSizes` array is explicit and portable.

---

## Takeaways

* For dynamic 2D data with potentially varying row lengths, pass **`(int **a, int rows, int *colSizes)`**.
* This exposes exactly the information the callee needs to iterate safely and manipulate rows independently.
* The pattern scales cleanly to reading input, transforming rows, and performing row-wise computations.
