//Сортировка
void sortirovka(int arr[], int n) {
    int i, j, minIndex, temp;

    for (i = 0; i < n - 1; i++) {
        minIndex = i;

        // Ищем минимальный элемент
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Сдвиг вправо для устойчивости
        temp = arr[minIndex];
        for (j = minIndex; j > i; j--) {
            arr[j] = arr[j - 1];
        }
        arr[i] = temp;
    }
}
