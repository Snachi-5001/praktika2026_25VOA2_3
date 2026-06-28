#ifndef MENU_H
#define MENU_H

// Структура для хранения состояния программы
typedef struct {
    int* arr;        // указатель на массив
    int n;           // размер массива
    int hasData;     // флаг наличия данных (1 - есть, 0 - нет)
} ProgramState;

// Прототипы функций меню
void printMenu();
void handleManualInput(ProgramState* state);
void handleRandomGeneration(ProgramState* state);
void handleFileInput(ProgramState* state);
void handleSortAndMeasure(ProgramState* state);
void handleSaveToFile(ProgramState* state);      
void handleClearArray(ProgramState* state);      
void handleShowArray(ProgramState* state);       
void handleExit(ProgramState* state);
void clearArray(ProgramState* state);

#endif