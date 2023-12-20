#include <stdio.h>
#include <stdlib.h>

// Функция для считывания и проверки массива из текстового файла

void readArrayFromFile(const char* fileName, int arr[], int size) {
    // Открываем файл для чтения
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return;
    }

    // Считываем элементы массива из файла
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    // Закрываем файл
    fclose(file);
}

// Функция для вывода массива:
void printArray(int **arr, int size);

void printArray(int **array, int n) {
    for (int i = 1; i < n + 1; i++) {
        printf("%3d", i);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%3d", (*array)[i]);
    }
    printf("\n\n");
}

// Функция для ввода массива с клавиатуры:

void fillArray(int* arr, int size) {
    int i;
    for (int i = 0; i < size; i++) {
        printf("Введите элемент массива №%d: ", i+1);
        int input;
        while (scanf("%d", &input) != 1) {
            printf("Ошибка! Введите целое число: ");
            while (getchar() != '\n'); // Очистка входного буфера
        }
        arr[i] = input;
    }
}

// Направление сортировки:

int compare_ask(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}


// Функция для быстрой сортировки:

void quickSort(int *arr, int low, int high, int (*compare)(const void *, const void *), int direction) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (direction * compare(&arr[j], &pivot) < 0) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;

        quickSort(arr, low, pi - 1, compare, direction);
        quickSort(arr, pi + 1, high, compare, direction);
    }
}


// Функция для гномьей сортировки:


void gnomeSort(int *arr, int size, int (*compare)(const void *, const void *), int direction) {
    int index = 0;
    
    while (index < size) {
        if (index == 0 || direction * compare(&arr[index], &arr[index - 1]) >= 0) {
            index++;
        } else {
            int temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index - 1] = temp;
            
            index--;
        }
    }
}



// Функция для сортировки Шелла:

void shellSort(int arr[], int size, int (*compare)(const void *, const void *), int direction) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;

            for (j = i; j >= gap && direction * compare(&arr[j - gap], &temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}




int main(){
	int n; // n - количество элементов
	printf("Введите количество элементов массива: ");
	scanf("%d", &n);

	// Выделение памяти под массив:
	int* arr1 = (int*)malloc(n * sizeof(int));
	int* arr2 = (int*)malloc(n * sizeof(int));
	int choice, choice1, choice2;
    int sign = 1;

	// printf("Выберите ввод массива:\n");
    // printf("1. с клавиатуры\n");
    // printf("2. из текстового файла\n");
    // printf("3. из бинарного файла\n");
    // scanf("%d", &choice1);

    // if (choice1 == 1){
    // 	fillArray(arr1, n);
    // }

    // if (choice1 == 2){
    // 	char beg_name;
    // 	fillArrayFromFile(arr2, n, &beg_name);
    // }

    while (1) {
        printf("\n___________________\n");
        printf("1. Выберите алгоритм сортировки. \n");
        printf("2. Введите массив\n");
        printf("3. Выберите направление сортировки\n");
        printf("0. Выйти\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Выберите сортировку:\n");
                printf("1. Быстрая сортировка (Quick sort):\n");
                printf("2. Гномья сортировка (Gnome sort):\n");
                printf("3. Сортировка Шелла (Shell sort):\n");
                scanf("%d", &choice1);

                if (choice1 == 1){
                    quickSort(arr1, 0, n - 1, compare_ask, sign);
                    printArray(&arr1, n);
                }

                if (choice1 == 2){
                    gnomeSort(arr1, n, compare_ask, sign);
                    printArray(&arr1, n);

                }

                if (choice1 == 3){
                    shellSort(arr1, n, compare_ask, sign);
                    printArray(&arr1, n);

                }

                break;
            case 2:
                fillArray(arr1, n);
                break;
            case 3:
            	printf("Выберите направление сортировки:\n");
                printf("1. По возрастанию.\n");
                printf("2. По убыванию.\n");
                scanf("%d", &choice2);

                if (choice2 == 1){
                    sign = 1;
                }

                if (choice2 == 2){
                    sign = -1;
                }

                else{
                    printf("Ошибка ввода!");
                }


                break;
                
            case 0:
                exit(0);
                break;

        }
    }

    return 0;
}
