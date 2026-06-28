#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "file_io.h"

void printMenu() {
    printf("\n========== SORTING PROGRAM ==========\n");
    printf("1. Enter numbers manually\n");
    printf("2. Generate random numbers\n");
    printf("3. Read from file (input.txt)\n");
    printf("4. Sort and measure time\n");
    printf("5. Exit\n");
    printf("=====================================\n");
    printf("Choose an option: ");
}

int main() {
    int* arr = NULL;
    int n = 0;
    int choice;
    int hasData = 0;  // флаг, что массив загружен

    srand((unsigned int)time(NULL));

    while (1) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        // Очистка буфера после ввода числа
        while (getchar() != '\n');

        switch (choice) {
        case 1: {  // Ручной ввод
            if (arr != NULL) {
                free(arr);
                arr = NULL;
            }
            printf("How many numbers? ");
            int count;
            if (scanf("%d", &count) != 1 || count <= 0) {
                printf("Invalid count. Please enter a positive number.\n");
                while (getchar() != '\n');
                break;
            }
            while (getchar() != '\n');

            arr = (int*)malloc(count * sizeof(int));
            if (arr == NULL) {
                printf("Memory allocation error!\n");
                break;
            }

            printf("Enter %d numbers separated by space or newline:\n", count);
            for (int i = 0; i < count; i++) {
                if (scanf("%d", &arr[i]) != 1) {
                    printf("Invalid input! Please enter integers only.\n");
                    free(arr);
                    arr = NULL;
                    while (getchar() != '\n');
                    break;
                }
            }
            while (getchar() != '\n');
            n = count;
            hasData = 1;
            printf("Array loaded successfully!\n");
            printf("Array: ");
            printArray(arr, n);
            break;
        }

        case 2: {  // Генерация случайных чисел
            if (arr != NULL) {
                free(arr);
                arr = NULL;
            }
            printf("How many random numbers to generate? ");
            int count;
            if (scanf("%d", &count) != 1 || count <= 0) {
                printf("Invalid count. Please enter a positive number.\n");
                while (getchar() != '\n');
                break;
            }
            while (getchar() != '\n');

            printf("Enter min value: ");
            int min, max;
            if (scanf("%d", &min) != 1) {
                printf("Invalid input!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Enter max value: ");
            if (scanf("%d", &max) != 1 || max < min) {
                printf("Invalid input or max < min!\n");
                while (getchar() != '\n');
                break;
            }
            while (getchar() != '\n');

            arr = (int*)malloc(count * sizeof(int));
            if (arr == NULL) {
                printf("Memory allocation error!\n");
                break;
            }

            for (int i = 0; i < count; i++) {
                arr[i] = min + rand() % (max - min + 1);
            }
            n = count;
            hasData = 1;
            printf("Generated %d random numbers in range [%d, %d]\n", count, min, max);
            printf("Array: ");
            printArray(arr, n);
            break;
        }

        case 3: {  // Чтение из файла
            if (arr != NULL) {
                free(arr);
                arr = NULL;
            }
            n = read_from_file(&arr, "input.txt");
            if (n > 0) {
                hasData = 1;
                printf("Successfully read %d numbers from input.txt\n", n);
                printf("Array: ");
                printArray(arr, n);
            }
            else {
                hasData = 0;
                printf("Failed to read from file. Please create input.txt with numbers.\n");
            }
            break;
        }

        case 4: {  // Сортировка + замер времени
            if (!hasData || arr == NULL || n <= 0) {
                printf("No data! Please load or generate numbers first (options 1-3).\n");
                break;
            }

            printf("\n=== SORTING ===\n");
            printf("Original array: ");
            printArray(arr, n);

            // Замеряем время
            double timeTaken = getSortTime(arr, n);
            if (timeTaken < 0) {
                printf("Error measuring sort time.\n");
                break;
            }

            // Сортируем оригинальный массив
            sortirovka(arr, n);

            printf("Sorted array: ");
            printArray(arr, n);
            printf("\nSorting time: %.6f seconds (%.3f ms)\n",
                timeTaken, timeTaken * 1000.0);
            printf("Number of elements: %d\n", n);

            // Сохраняем в файл
            if (save_to_file(arr, n, "output.txt") == 0) {
                printf("Result saved to output.txt\n");
            }
            else {
                printf("Error saving to file!\n");
            }
            break;
        }

        case 5: {  // Выход
            printf("Exiting program. Goodbye!\n");
            if (arr != NULL) {
                free(arr);
                arr = NULL;
            }
            return 0;
        }

        default:
            printf("Invalid option. Please choose 1-5.\n");
            break;
        }
    }

    return 0;
}