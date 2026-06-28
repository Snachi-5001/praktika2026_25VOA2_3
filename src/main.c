#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int main() {
    ProgramState state = { NULL, 0, 0 };
    int choice;

    while (1) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1: handleManualInput(&state); break;
        case 2: handleRandomGeneration(&state); break;
        case 3: handleFileInput(&state); break;
        case 4: handleSortAndMeasure(&state); break;
        case 5: handleSaveToFile(&state); break;
        case 6: handleClearArray(&state); break;
        case 7: handleShowArray(&state); break;
        case 8: handleExit(&state); return 0;
        default:
            printf("Invalid option. Please choose 1-8.\n");
            break;
        }
    }

    return 0;
}