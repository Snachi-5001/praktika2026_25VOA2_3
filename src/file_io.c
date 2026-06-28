#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"

int read_from_file(int** arr, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file '%s' for reading\n", filename);
        return -1;
    }

    int capacity = 10;
    int count = 0;
    *arr = (int*)malloc(capacity * sizeof(int));
    if (*arr == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation error\n");
        return -1;
    }

    int num;
    while (fscanf(file, "%d", &num) == 1) {
        if (count >= capacity) {
            capacity *= 2;
            int* new_arr = (int*)realloc(*arr, capacity * sizeof(int));
            if (new_arr == NULL) {
                free(*arr);
                fclose(file);
                fprintf(stderr, "Memory reallocation error\n");
                return -1;
            }
            *arr = new_arr;
        }
        (*arr)[count++] = num;
    }

    fclose(file);
    if (count == 0) {
        free(*arr);
        *arr = NULL;
        fprintf(stderr, "File '%s' is empty or contains no numbers\n", filename);
        return -1;
    }
    return count;
}

int save_to_file(int* arr, int n, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file '%s' for writing\n", filename);
        return -1;
    }
    for (int i = 0; i < n; i++)
        fprintf(file, "%d ", arr[i]);
    fprintf(file, "\n");
    fclose(file);
    return 0;
}