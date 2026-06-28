#include <stdio.h>
#include <time.h>
#include "sort.h"
#include "stdlib.h"
void sortirovka(int arr[], int n) {
    int i, j, minIndex, temp;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        temp = arr[minIndex];
        for (j = minIndex; j > i; j--)
            arr[j] = arr[j - 1];
        arr[i] = temp;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

double getSortTime(int arr[], int n) {
    // Создаём копию массива, чтобы не портить оригинал
    int* copy = (int*)malloc(n * sizeof(int));
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation error in getSortTime\n");
        return -1.0;
    }
    for (int i = 0; i < n; i++)
        copy[i] = arr[i];

    clock_t start = clock();
    sortirovka(copy, n);
    clock_t end = clock();

    free(copy);
    return (double)(end - start) / CLOCKS_PER_SEC;
}