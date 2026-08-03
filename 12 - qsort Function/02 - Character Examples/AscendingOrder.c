#include <stdio.h>
#include <stdlib.h>

int cmp_char_asc(const void *a, const void *b) {
    return (*(char*)a - *(char*)b); // normal order
}

int main() {
    char arr[] = "salam";
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(char), cmp_char_asc);

    for (int i = 0; i < n; i++)
        printf("%c ", arr[i]);
    printf("\n");

    return 0;
}
