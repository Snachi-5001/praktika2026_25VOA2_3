#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"

int read_from_file(int* arr, int n, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file '%s' for reading\n", filename);
        return -1;
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &arr[i]) == 1)
            count++;
        else
            break;
    }
    fclose(file);
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