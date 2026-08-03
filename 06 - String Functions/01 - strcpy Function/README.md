# strcpy Function in C - Usage Guide

## Purpose of strcpy

The `strcpy` function is a standard library function in C used to **copy strings from one location to another**. It is declared in the `<string.h>` header file.

### Function Signature
```c
char *strcpy(char *destination, const char *source);
```

### Primary Purpose
- **String Copying**: Copies the entire content of the source string (including the null terminator `\0`) to the destination string
- **Memory Transfer**: Transfers character data from one memory location to another
- **String Initialization**: Often used to initialize or assign values to string variables

## Usage with Dynamic and Static Strings

### 1. Static to Static Strings
```c
#include <stdio.h>
#include <string.h>

int main() {
    char source[] = "Hello World";     // Static source
    char dest[50];                     // Static destination
    
    strcpy(dest, source);
    printf("Copied string: %s\n", dest);
    return 0;
}
```
**Result**: ✅ **Works perfectly** - Both strings have fixed memory allocation.

### 2. Static to Dynamic Strings
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char source[] = "Hello World";                    // Static source
    char *dest = malloc(strlen(source) + 1);         // Dynamic destination
    
    if (dest != NULL) {
        strcpy(dest, source);
        printf("Copied string: %s\n", dest);
        free(dest);  // Don't forget to free memory
    }
    return 0;
}
```
**Result**: ✅ **Works perfectly** - Dynamic memory provides adequate space.

### 3. Dynamic to Static Strings
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char *source = malloc(20);          // Dynamic source
    strcpy(source, "Hello World");      // Initialize dynamic string
    char dest[50];                      // Static destination
    
    strcpy(dest, source);
    printf("Copied string: %s\n", dest);
    
    free(source);
    return 0;
}
```
**Result**: ✅ **Works if destination has enough space**.

### 4. Dynamic to Dynamic Strings
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char *source = malloc(20);                       // Dynamic source
    strcpy(source, "Hello World");
    
    char *dest = malloc(strlen(source) + 1);        // Dynamic destination
    
    if (source != NULL && dest != NULL) {
        strcpy(dest, source);
        printf("Copied string: %s\n", dest);
        
        free(source);
        free(dest);
    }
    return 0;
}
```
**Result**: ✅ **Works perfectly** - Both strings are properly allocated.

## Key Considerations and Best Practices

### ⚠️ Critical Requirements
1. **Destination Must Have Sufficient Space**: The destination must be large enough to hold the entire source string plus the null terminator
2. **Memory Allocation**: For dynamic strings, ensure proper memory allocation before using `strcpy`
3. **Null Termination**: `strcpy` automatically copies the null terminator

### 🚨 Common Pitfalls
```c
// ❌ DANGEROUS - Buffer overflow risk
char dest[5];
char source[] = "This string is too long";
strcpy(dest, source);  // Will overflow dest buffer!

// ❌ DANGEROUS - Uninitialized destination
char *dest;  // Not allocated
strcpy(dest, "Hello");  // Undefined behavior!
```

### ✅ Safe Alternatives
```c
// Use strncpy for safer copying
strncpy(dest, source, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';  // Ensure null termination

// Or use snprintf for better control
snprintf(dest, sizeof(dest), "%s", source);
```

## Summary Table

| Source Type | Destination Type | Result | Notes |
|-------------|------------------|--------|-------|
| Static      | Static           | ✅ Works | Ensure dest size ≥ source size |
| Static      | Dynamic          | ✅ Works | Allocate dest with `malloc` first |
| Dynamic     | Static           | ✅ Works | Ensure dest size ≥ source size |
| Dynamic     | Dynamic          | ✅ Works | Allocate both with `malloc` |

## Memory Management Tips

1. **Always check malloc return values** for NULL
2. **Free dynamically allocated memory** with `free()`
3. **Calculate required size** using `strlen(source) + 1`
4. **Consider using safer alternatives** like `strncpy` or `snprintf` for production code

The `strcpy` function works with any combination of static and dynamic strings as long as proper memory allocation and size considerations are maintained.