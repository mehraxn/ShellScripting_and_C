# Understanding Division in C Language

This README explains how division works in the C programming language, especially when using integer types.

## Example Code

```c
int a = 7;
int b = 3;
float c = a / b;
```

### What Happens Here?

* Both `a` and `b` are declared as `int` (integers).
* The expression `a / b` performs **integer division**.
* In integer division, the result is the quotient without the remainder (fractional part is discarded).

  * `7 / 3` equals `2` in integer division.
* Then, `2` (an `int`) is stored in `c`, which is of type `float`. So `c` becomes `2.0`.

### Incorrect Result if Float is Expected

If you expected `c` to be `2.333...`, then this code won't give the correct result because of the integer division.

## Correct Way to Get Floating-Point Division

You need to convert at least one operand to `float` to force floating-point division:

### Method 1:

```c
float c = (float)a / b;
```

### Method 2:

```c
float c = a / (float)b;
```

### Method 3:

```c
float c = (float)a / (float)b;
```

All three methods will produce the correct result:

```c
c = 2.333333
```

## Summary

* Integer division truncates the decimal.
* To get a floating-point result, cast one (or both) operands to `float`.
* Be cautious of type conversions in arithmetic operations.

This is a common source of bugs for beginners in C programming!
