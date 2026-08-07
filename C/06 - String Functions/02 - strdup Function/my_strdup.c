#include <stdlib.h>

char *my_strdup(const char *s) {
    if (s == NULL) return NULL;

    int length = 0;
    while (s[length] != '\0') {
        length++;
    }

    char *copy = (char *)malloc(length + 1);
    if (copy == NULL) return NULL;

    for (int i = 0; i <= length; i++) {
        copy[i] = s[i];
    }

    return copy;
}

/*
    The my_strdup function manually duplicates a null-terminated C string.
    It first calculates the string's length without using any standard string functions,
    then allocates enough memory to hold the original string including the null terminator.
    After allocation, it copies each character one by one.

    This function mimics the behavior of the POSIX strdup function, but without relying
    on functions like strlen or strcpy. It's useful for environments where standard string
    utilities are restricted or unavailable.

    In terms of performance:
    - Time complexity is O(n), where n is the length of the input string.
    - Space complexity is also O(n) due to dynamic memory allocation.
    - It's efficient for small to medium strings, but the function should always be paired
      with proper memory management (i.e., free the result after use) to avoid memory leaks.
*/
