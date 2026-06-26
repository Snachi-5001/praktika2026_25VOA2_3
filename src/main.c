//добовление массива
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "file_io.h"
#include "menu.h"

int main() {
    // Статический массив созданный заранее
    int arr[] = { 64, 25, 12, 22, 11, 90, 3, 45, 18, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("sortirovka viborom \n");
    printf("ishoidni masiv: ");
    printArray(arr, n);

    sortirovka(arr, n);

    printf("otsortirivani massiv: ");
    printArray(arr, n);
    return 0;
}