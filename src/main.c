#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "file_io.h"
#define SIZE 10
void create_default_input_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot create default input file\n");//Ошибка не удаётся создать файл по умолчанию
        return;
    }
    int default_nums[SIZE] = { 64, 25, 12, 22, 11, 90, 3, 45, 18, 7 };
    for (int i = 0; i < SIZE; i++)
        fprintf(file, "%d ", default_nums[i]);
    fprintf(file, "\n");
    fclose(file);
    printf("Default input file '%s' created with %d numbers.\n", filename, SIZE);//Создан файл s с d числами по умолчанию
}
int main() {
    int arr[SIZE];
    int read_count = read_from_file(arr, SIZE, "input.txt");
    if (read_count < SIZE) {
        if (read_count == -1) {
            create_default_input_file("input.txt");
            read_count = read_from_file(arr, SIZE, "input.txt");
            if (read_count < SIZE) {
                fprintf(stderr, "Error: still cannot read enough numbers after creating default file\n");//Ошибка после создания файла не удалось прочитать d чисел
                return 1;
            }
        }
        else {
            fprintf(stderr, "Error: file must contain %d numbers, but %d read\n", SIZE, read_count);//Ошибка в файле должно быть d чисел прочитано d
            return 1;
        }
    }
    printf("Selection sort\n");//Сортировка выбором
    printf("Original array: ");//Исходный массив
    printArray(arr, SIZE);
    sortirovka(arr, SIZE);
    printf("Sorted array: ");//Отсортированный массив
    printArray(arr, SIZE);
    if (save_to_file(arr, SIZE, "output.txt") != 0) {
        fprintf(stderr, "Error writing to output.txt\n");//Ошибка записи в output.txt
        return 1;
    }
    printf("Result saved to output.txt\n");//Результат сохранён в output.txt
    return 0;
}