#include <stdio.h>
#include <stdlib.h>

int cmp_char_desc(const void *a, const void *b) {
    return (*(char*)b - *(char*)a); // reverse order
}

int main() {
    char arr[] = {'z', 'a', 'q', 'm', 'b'};
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(char), cmp_char_desc);

    for (int i = 0; i < n; i++)
        printf("%c ", arr[i]);
    printf("\n");

    return 0;
}
