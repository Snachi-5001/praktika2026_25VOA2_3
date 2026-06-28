#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "file_io.h"

int main() {
    int* arr = NULL;
    int n = read_from_file(&arr, "input.txt");
    if (n <= 0) {
        fprintf(stderr, "Program terminated: input.txt is empty or missing.\n");
        return 1;
    }

    printf("Selection sort\n");
    printf("Original array (%d numbers): ", n);
    printArray(arr, n);

    sortirovka(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    if (save_to_file(arr, n, "output.txt") != 0) {
        fprintf(stderr, "Error writing to output.txt\n");
        free(arr);
        return 1;
    }

    printf("Result saved to output.txt (%d numbers)\n", n);
    free(arr);
    return 0;
}