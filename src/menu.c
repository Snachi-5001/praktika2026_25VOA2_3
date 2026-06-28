#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "sort.h"
#include "file_io.h"

// Функция очистки буфера ввода
static void clearInputBuffer() {
    while (getchar() != '\n');
}

// Освобождение памяти
void clearArray(ProgramState* state) {
    if (state->arr != NULL) {
        free(state->arr);
        state->arr = NULL;
    }
    state->n = 0;
    state->hasData = 0;
}

// Вывод меню
void printMenu() {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║        SORTING PROGRAM MENU            ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║  1. Enter numbers manually             ║\n");
    printf("║  2. Generate random numbers            ║\n");
    printf("║  3. Read from file (input.txt)         ║\n");
    printf("║  4. Sort and measure time              ║\n");
    printf("║  5. Save to file (output.txt)          ║\n");
    printf("║  6. Clear array                        ║\n");
    printf("║  7. Show current array                 ║\n");
    printf("║  8. Exit                               ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("Choose an option (1-8): ");
}

// 1. Ручной ввод
void handleManualInput(ProgramState* state) {
    clearArray(state);

    printf("How many numbers? ");
    int count;
    if (scanf("%d", &count) != 1 || count <= 0) {
        printf("Invalid count. Please enter a positive number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    state->arr = (int*)malloc(count * sizeof(int));
    if (state->arr == NULL) {
        printf("Memory allocation error!\n");
        return;
    }

    printf("Enter %d numbers separated by space or newline:\n", count);
    for (int i = 0; i < count; i++) {
        if (scanf("%d", &state->arr[i]) != 1) {
            printf("Invalid input! Please enter integers only.\n");
            clearArray(state);
            clearInputBuffer();
            return;
        }
    }
    clearInputBuffer();

    state->n = count;
    state->hasData = 1;
    printf("✓ Array loaded successfully! (%d numbers)\n", count);
    printf("Array: ");
    printArray(state->arr, state->n);
}

// 2. Генерация случайных чисел
void handleRandomGeneration(ProgramState* state) {
    clearArray(state);

    printf("How many random numbers to generate? ");
    int count;
    if (scanf("%d", &count) != 1 || count <= 0) {
        printf("Invalid count. Please enter a positive number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    printf("Enter min value: ");
    int min, max;
    if (scanf("%d", &min) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }
    printf("Enter max value: ");
    if (scanf("%d", &max) != 1 || max < min) {
        printf("Invalid input or max < min!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    state->arr = (int*)malloc(count * sizeof(int));
    if (state->arr == NULL) {
        printf("Memory allocation error!\n");
        return;
    }

    srand((unsigned int)time(NULL));
    for (int i = 0; i < count; i++) {
        state->arr[i] = min + rand() % (max - min + 1);
    }

    state->n = count;
    state->hasData = 1;
    printf("✓ Generated %d random numbers in range [%d, %d]\n", count, min, max);
    printf("Array: ");
    printArray(state->arr, state->n);
}

// 3. Чтение из файла
void handleFileInput(ProgramState* state) {
    clearArray(state);

    printf("Reading from input.txt...\n");
    state->n = read_from_file(&state->arr, "input.txt");

    if (state->n > 0) {
        state->hasData = 1;
        printf("✓ Successfully read %d numbers from input.txt\n", state->n);
        printf("Array: ");
        printArray(state->arr, state->n);
    }
    else {
        state->hasData = 0;
        printf("✗ Failed to read from file. Please create input.txt with numbers.\n");
    }
}

// 4. Сортировка и замер времени
void handleSortAndMeasure(ProgramState* state) {
    if (!state->hasData || state->arr == NULL || state->n <= 0) {
        printf("✗ No data! Please load or generate numbers first (options 1-3).\n");
        return;
    }

    printf("\n=== SORTING ===\n");
    printf("Original array: ");
    printArray(state->arr, state->n);

    // Замеряем время
    double timeTaken = getSortTime(state->arr, state->n);
    if (timeTaken < 0) {
        printf("Error measuring sort time.\n");
        return;
    }

    // Сортируем оригинальный массив
    sortirovka(state->arr, state->n);

    printf("Sorted array: ");
    printArray(state->arr, state->n);
    printf("\n⏱ Sorting time: %.6f seconds (%.3f ms)\n",
        timeTaken, timeTaken * 1000.0);
    printf("📊 Number of elements: %d\n", state->n);
}

// 5. Сохранение в файл
void handleSaveToFile(ProgramState* state) {
    if (!state->hasData || state->arr == NULL || state->n <= 0) {
        printf("✗ No data! Please load or generate numbers first (options 1-3).\n");
        return;
    }

    if (save_to_file(state->arr, state->n, "output.txt") == 0) {
        printf("✓ Result saved to output.txt (%d numbers)\n", state->n);
    }
    else {
        printf("✗ Error saving to file!\n");
    }
}

// 6. Очистка массива
void handleClearArray(ProgramState* state) {
    if (state->hasData && state->arr != NULL) {
        clearArray(state);
        printf("✓ Array cleared.\n");
    }
    else {
        printf("ℹ No data to clear.\n");
    }
}

// 7. Показать текущий массив
void handleShowArray(ProgramState* state) {
    if (!state->hasData || state->arr == NULL || state->n <= 0) {
        printf("✗ No data available.\n");
        return;
    }

    printf("Current array (%d numbers): ", state->n);
    printArray(state->arr, state->n);
}

// 8. Выход
void handleExit(ProgramState* state) {
    clearArray(state);
    printf("👋 Exiting program. Goodbye!\n");
}