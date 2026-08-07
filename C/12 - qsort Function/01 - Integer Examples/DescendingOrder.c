#include <stdio.h>
#include <stdlib.h>

int cmp_int_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a); // reverse order
}

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(int), cmp_int_desc);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
