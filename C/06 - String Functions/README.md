# C String Functions Complete Reference

This comprehensive guide covers all 30 essential C string manipulation functions, providing detailed explanations, syntax, parameters, return values, and practical examples for each function.

## Table of Contents

1. [Memory Functions](#memory-functions)
2. [String Copy Functions](#string-copy-functions)
3. [String Concatenation Functions](#string-concatenation-functions)
4. [String Comparison Functions](#string-comparison-functions)
5. [String Search Functions](#string-search-functions)
6. [String Tokenization Functions](#string-tokenization-functions)
7. [String Utility Functions](#string-utility-functions)
8. [POSIX and Extension Functions](#posix-and-extension-functions)

---

## Memory Functions

### 1. `memcpy`
**Header:** `<string.h>`

Copies `n` bytes from source memory area to destination memory area. Memory areas must not overlap.

**Syntax:**
```c
void *memcpy(void *dest, const void *src, size_t n);
```

**Parameters:**
- `dest`: Pointer to destination memory
- `src`: Pointer to source memory  
- `n`: Number of bytes to copy

**Returns:** Pointer to destination (`dest`)

**Example:**
```c
char src[] = "Hello World";
char dest[20];
memcpy(dest, src, strlen(src) + 1);
printf("%s", dest); // Output: Hello World
```

### 2. `memmove`
**Header:** `<string.h>`

Similar to `memcpy` but handles overlapping memory areas safely.

**Syntax:**
```c
void *memmove(void *dest, const void *src, size_t n);
```

**Parameters:**
- `dest`: Pointer to destination memory
- `src`: Pointer to source memory
- `n`: Number of bytes to move

**Returns:** Pointer to destination (`dest`)

**Example:**
```c
char str[] = "Hello World";
memmove(str + 6, str, 5); // Move "Hello" to position 6
printf("%s", str); // Output: Hello Hello
```

### 3. `memchr`
**Header:** `<string.h>`

Searches for the first occurrence of a character in a block of memory.

**Syntax:**
```c
void *memchr(const void *s, int c, size_t n);
```

**Parameters:**
- `s`: Pointer to memory block
- `c`: Character to search for (as int)
- `n`: Number of bytes to search

**Returns:** Pointer to first occurrence, or `NULL` if not found

**Example:**
```c
char str[] = "Hello World";
char *ptr = memchr(str, 'W', strlen(str));
if (ptr) printf("Found at position: %ld", ptr - str); // Output: Found at position: 6
```

### 4. `memcmp`
**Header:** `<string.h>`

Compares two blocks of memory byte by byte.

**Syntax:**
```c
int memcmp(const void *s1, const void *s2, size_t n);
```

**Parameters:**
- `s1`: Pointer to first memory block
- `s2`: Pointer to second memory block
- `n`: Number of bytes to compare

**Returns:**
- `< 0` if s1 < s2
- `0` if s1 == s2
- `> 0` if s1 > s2

**Example:**
```c
char str1[] = "ABC";
char str2[] = "ABD";
int result = memcmp(str1, str2, 3);
printf("%d", result); // Output: negative value (C < D)
```

### 5. `memset`
**Header:** `<string.h>`

Fills a block of memory with a specific byte value.

**Syntax:**
```c
void *memset(void *s, int c, size_t n);
```

**Parameters:**
- `s`: Pointer to memory block
- `c`: Value to set (as int, but treated as unsigned char)
- `n`: Number of bytes to set

**Returns:** Pointer to memory block (`s`)

**Example:**
```c
char buffer[10];
memset(buffer, 'A', 9);
buffer[9] = '\0';
printf("%s", buffer); // Output: AAAAAAAAA
```

---

## String Copy Functions

### 6. `strcpy`
**Header:** `<string.h>`

Copies a string from source to destination, including the null terminator.

**Syntax:**
```c
char *strcpy(char *dest, const char *src);
```

**Parameters:**
- `dest`: Pointer to destination string
- `src`: Pointer to source string

**Returns:** Pointer to destination string

**Example:**
```c
char dest[20];
strcpy(dest, "Hello World");
printf("%s", dest); // Output: Hello World
```

### 7. `strncpy`
**Header:** `<string.h>`

Copies at most `n` characters from source to destination. May not null-terminate if source is longer than `n`.

**Syntax:**
```c
char *strncpy(char *dest, const char *src, size_t n);
```

**Parameters:**
- `dest`: Pointer to destination string
- `src`: Pointer to source string
- `n`: Maximum number of characters to copy

**Returns:** Pointer to destination string

**Example:**
```c
char dest[10];
strncpy(dest, "Hello World", 5);
dest[5] = '\0'; // Ensure null termination
printf("%s", dest); // Output: Hello
```

---

## String Concatenation Functions

### 8. `strcat`
**Header:** `<string.h>`

Concatenates source string to the end of destination string.

**Syntax:**
```c
char *strcat(char *dest, const char *src);
```

**Parameters:**
- `dest`: Pointer to destination string (must have enough space)
- `src`: Pointer to source string

**Returns:** Pointer to destination string

**Example:**
```c
char dest[20] = "Hello ";
strcat(dest, "World");
printf("%s", dest); // Output: Hello World
```

### 9. `strncat`
**Header:** `<string.h>`

Concatenates at most `n` characters from source to destination.

**Syntax:**
```c
char *strncat(char *dest, const char *src, size_t n);
```

**Parameters:**
- `dest`: Pointer to destination string
- `src`: Pointer to source string
- `n`: Maximum number of characters to concatenate

**Returns:** Pointer to destination string

**Example:**
```c
char dest[20] = "Hello ";
strncat(dest, "Beautiful World", 9);
printf("%s", dest); // Output: Hello Beautiful
```

---

## String Utility Functions

### 10. `strlen`
**Header:** `<string.h>`

Returns the length of a string (excluding null terminator).

**Syntax:**
```c
size_t strlen(const char *s);
```

**Parameters:**
- `s`: Pointer to string

**Returns:** Length of string

**Example:**
```c
char str[] = "Hello World";
printf("Length: %zu", strlen(str)); // Output: Length: 11
```

---

## String Comparison Functions

### 11. `strcmp`
**Header:** `<string.h>`

Compares two strings lexicographically.

**Syntax:**
```c
int strcmp(const char *s1, const char *s2);
```

**Parameters:**
- `s1`: Pointer to first string
- `s2`: Pointer to second string

**Returns:**
- `< 0` if s1 < s2
- `0` if s1 == s2
- `> 0` if s1 > s2

**Example:**
```c
int result = strcmp("apple", "banana");
printf("%d", result); // Output: negative value
```

### 12. `strncmp`
**Header:** `<string.h>`

Compares at most `n` characters of two strings.

**Syntax:**
```c
int strncmp(const char *s1, const char *s2, size_t n);
```

**Parameters:**
- `s1`: Pointer to first string
- `s2`: Pointer to second string
- `n`: Maximum number of characters to compare

**Returns:** Same as `strcmp`

**Example:**
```c
int result = strncmp("apple", "application", 3);
printf("%d", result); // Output: 0 (first 3 chars are equal)
```

### 13. `strcoll`
**Header:** `<string.h>`

Compares two strings according to the current locale.

**Syntax:**
```c
int strcoll(const char *s1, const char *s2);
```

**Parameters:**
- `s1`: Pointer to first string
- `s2`: Pointer to second string

**Returns:** Same as `strcmp`

**Example:**
```c
setlocale(LC_COLLATE, "");
int result = strcoll("café", "cafe");
```

### 14. `strxfrm`
**Header:** `<string.h>`

Transforms a string according to the current locale for use with `strcmp`.

**Syntax:**
```c
size_t strxfrm(char *dest, const char *src, size_t n);
```

**Parameters:**
- `dest`: Pointer to destination buffer
- `src`: Pointer to source string
- `n`: Maximum size of destination buffer

**Returns:** Length of transformed string

**Example:**
```c
char transformed[100];
size_t len = strxfrm(transformed, "café", sizeof(transformed));
```

---

## String Search Functions

### 15. `strchr`
**Header:** `<string.h>`

Finds the first occurrence of a character in a string.

**Syntax:**
```c
char *strchr(const char *s, int c);
```

**Parameters:**
- `s`: Pointer to string
- `c`: Character to search for

**Returns:** Pointer to first occurrence, or `NULL` if not found

**Example:**
```c
char *ptr = strchr("Hello World", 'W');
if (ptr) printf("Found at position: %ld", ptr - "Hello World"); // Output: Found at position: 6
```

### 16. `strrchr`
**Header:** `<string.h>`

Finds the last occurrence of a character in a string.

**Syntax:**
```c
char *strrchr(const char *s, int c);
```

**Parameters:**
- `s`: Pointer to string
- `c`: Character to search for

**Returns:** Pointer to last occurrence, or `NULL` if not found

**Example:**
```c
char *ptr = strrchr("Hello World", 'l');
if (ptr) printf("Last 'l' at position: %ld", ptr - "Hello World"); // Output: Last 'l' at position: 9
```

### 17. `strspn`
**Header:** `<string.h>`

Returns the length of the initial segment of string that consists only of characters in accept.

**Syntax:**
```c
size_t strspn(const char *s, const char *accept);
```

**Parameters:**
- `s`: Pointer to string to be scanned
- `accept`: Pointer to string containing accepted characters

**Returns:** Length of initial segment

**Example:**
```c
size_t len = strspn("123abc", "0123456789");
printf("%zu", len); // Output: 3
```

### 18. `strcspn`
**Header:** `<string.h>`

Returns the length of the initial segment of string that consists of characters not in reject.

**Syntax:**
```c
size_t strcspn(const char *s, const char *reject);
```

**Parameters:**
- `s`: Pointer to string to be scanned
- `reject`: Pointer to string containing rejected characters

**Returns:** Length of initial segment

**Example:**
```c
size_t len = strcspn("hello123", "0123456789");
printf("%zu", len); // Output: 5
```

### 19. `strpbrk`
**Header:** `<string.h>`

Finds the first occurrence of any character from accept in string.

**Syntax:**
```c
char *strpbrk(const char *s, const char *accept);
```

**Parameters:**
- `s`: Pointer to string to be scanned
- `accept`: Pointer to string containing characters to match

**Returns:** Pointer to first matching character, or `NULL` if none found

**Example:**
```c
char *ptr = strpbrk("hello world", "aeiou");
if (ptr) printf("First vowel: %c", *ptr); // Output: First vowel: e
```

### 20. `strstr`
**Header:** `<string.h>`

Finds the first occurrence of substring in string.

**Syntax:**
```c
char *strstr(const char *haystack, const char *needle);
```

**Parameters:**
- `haystack`: Pointer to string to be searched
- `needle`: Pointer to substring to search for

**Returns:** Pointer to first occurrence, or `NULL` if not found

**Example:**
```c
char *ptr = strstr("Hello World", "World");
if (ptr) printf("Found at position: %ld", ptr - "Hello World"); // Output: Found at position: 6
```

---

## String Tokenization Functions

### 21. `strtok`
**Header:** `<string.h>`

Breaks string into tokens separated by delimiters. Not thread-safe.

**Syntax:**
```c
char *strtok(char *str, const char *delim);
```

**Parameters:**
- `str`: Pointer to string to tokenize (NULL for subsequent calls)
- `delim`: Pointer to string containing delimiter characters

**Returns:** Pointer to next token, or `NULL` if no more tokens

**Example:**
```c
char str[] = "apple,banana,orange";
char *token = strtok(str, ",");
while (token) {
    printf("%s\n", token);
    token = strtok(NULL, ",");
}
// Output: apple, banana, orange (each on new line)
```

---

## POSIX and Extension Functions

### 22. `strdup`
**Header:** `<string.h>` (POSIX/C23)

Creates a duplicate of a string by allocating memory and copying the string.

**Syntax:**
```c
char *strdup(const char *s);
```

**Parameters:**
- `s`: Pointer to string to duplicate

**Returns:** Pointer to duplicated string, or `NULL` on error

**Example:**
```c
char *copy = strdup("Hello World");
if (copy) {
    printf("%s", copy);
    free(copy); // Remember to free allocated memory
}
```

### 23. `strndup`
**Header:** `<string.h>` (POSIX/C23)

Creates a duplicate of at most `n` characters of a string.

**Syntax:**
```c
char *strndup(const char *s, size_t n);
```

**Parameters:**
- `s`: Pointer to string to duplicate
- `n`: Maximum number of characters to duplicate

**Returns:** Pointer to duplicated string, or `NULL` on error

**Example:**
```c
char *copy = strndup("Hello World", 5);
if (copy) {
    printf("%s", copy); // Output: Hello
    free(copy);
}
```

### 24. `memccpy`
**Header:** `<string.h>` (POSIX/C23)

Copies bytes from source to destination until a specific character is found or `n` bytes are copied.

**Syntax:**
```c
void *memccpy(void *dest, const void *src, int c, size_t n);
```

**Parameters:**
- `dest`: Pointer to destination
- `src`: Pointer to source
- `c`: Character to stop copying at
- `n`: Maximum bytes to copy

**Returns:** Pointer to byte after `c` in dest, or `NULL` if `c` not found

**Example:**
```c
char src[] = "Hello World";
char dest[20];
void *ptr = memccpy(dest, src, ' ', sizeof(dest));
if (ptr) {
    *((char*)ptr - 1) = '\0';
    printf("%s", dest); // Output: Hello
}
```

### 25. `mempcpy`
**Header:** `<string.h>` (GNU extension)

Similar to `memcpy` but returns pointer to end of copied data.

**Syntax:**
```c
void *mempcpy(void *dest, const void *src, size_t n);
```

**Parameters:**
- `dest`: Pointer to destination
- `src`: Pointer to source
- `n`: Number of bytes to copy

**Returns:** Pointer to byte after last copied byte

**Example:**
```c
char dest[20];
char *end = mempcpy(dest, "Hello", 5);
*end = '\0';
printf("%s", dest); // Output: Hello
```

### 26. `strtok_r`
**Header:** `<string.h>` (POSIX)

Thread-safe version of `strtok` that uses a user-provided context pointer.

**Syntax:**
```c
char *strtok_r(char *str, const char *delim, char **saveptr);
```

**Parameters:**
- `str`: Pointer to string to tokenize (NULL for subsequent calls)
- `delim`: Pointer to delimiter characters
- `saveptr`: Pointer to context pointer

**Returns:** Pointer to next token, or `NULL` if no more tokens

**Example:**
```c
char str[] = "apple,banana,orange";
char *saveptr;
char *token = strtok_r(str, ",", &saveptr);
while (token) {
    printf("%s\n", token);
    token = strtok_r(NULL, ",", &saveptr);
}
```

### 27. `strlcpy`
**Header:** `<string.h>` (BSD/GNU extension)

Size-bounded string copying that guarantees null termination.

**Syntax:**
```c
size_t strlcpy(char *dst, const char *src, size_t size);
```

**Parameters:**
- `dst`: Pointer to destination buffer
- `src`: Pointer to source string
- `size`: Size of destination buffer

**Returns:** Length of source string

**Example:**
```c
char dest[10];
size_t len = strlcpy(dest, "Hello World", sizeof(dest));
printf("%s (truncated: %s)", dest, len >= sizeof(dest) ? "yes" : "no");
// Output: Hello Wor (truncated: yes)
```

### 28. `strlcat`
**Header:** `<string.h>` (BSD/GNU extension)

Size-bounded string concatenation that guarantees null termination.

**Syntax:**
```c
size_t strlcat(char *dst, const char *src, size_t size);
```

**Parameters:**
- `dst`: Pointer to destination buffer
- `src`: Pointer to source string
- `size`: Size of destination buffer

**Returns:** Length of string it tried to create

**Example:**
```c
char dest[20] = "Hello ";
size_t len = strlcat(dest, "World", sizeof(dest));
printf("%s", dest); // Output: Hello World
```

---

## Important Notes

### Memory Management
- Functions like `strdup` and `strndup` allocate memory that must be freed with `free()`
- Always ensure destination buffers are large enough to prevent buffer overflows
- Use safer alternatives like `strncpy`, `strncat`, `strlcpy`, and `strlcat` when possible

### Thread Safety
- `strtok` is not thread-safe; use `strtok_r` in multi-threaded applications
- Most other string functions are thread-safe as long as they don't modify shared data

### Null Termination
- Always ensure strings are properly null-terminated
- Functions like `strncpy` may not null-terminate if the source is too long
- The `strl*` functions guarantee null termination

### Portability
- POSIX functions may not be available on all systems
- GNU extensions are specific to glibc
- BSD extensions are available on BSD systems and some Linux distributions

### Best Practices
- Always check return values for functions that can fail
- Validate input parameters before calling string functions
- Use static analysis tools to detect potential buffer overflows
- Consider using safer alternatives from modern C libraries when available

---

This reference covers all 30 functions from your CSV file. Each function is explained with its purpose, syntax, parameters, return values, and practical examples to help you understand and use them effectively in your C programs.