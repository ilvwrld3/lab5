//
// Created by Ilya Atmazhitov on 04.01.2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для считывания и проверки массива из текстового файла

//void readArrayFromFile(const char* fileName, int arr[], int size) {
//    // Открываем файл для чтения
//    FILE* file = fopen(fileName, "r");
//    if (file == NULL) {
//        printf("Ошибка открытия файла\n");
//        return;
//    }
//
//    // Считываем элементы массива из файла
//    for (int i = 0; i < size; i++) {
//        fscanf(file, "%d", &arr[i]);
//    }
//
//    // Закрываем файл
//    fclose(file);
//}

typedef struct {
    int id;
    int importanceLevel;
    char text[100];
} LogEntry;


void printRes(LogEntry arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d %d %s\n", arr[i].id, arr[i].importanceLevel, arr[i].text);
    }
}



// Направление сортировки:

int compare_ask(const void *a, const void *b) {
    const LogEntry *logA = (const LogEntry *)a;
    const LogEntry *logB = (const LogEntry *)b;

    // Сравниваем по уровню важности, затем по идентификатору
    if (logA->importanceLevel == logB->importanceLevel) {
        return logA->id - logB->id;
    } else {
        return logA->importanceLevel - logB->importanceLevel;
    }
}


// Функция для быстрой сортировки:

void quickSort(LogEntry *arr, int low, int high, int (*compare)(const void *, const void *), int direction, int sortField) {
    if (low < high) {
        LogEntry pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (sortField == 1) {
                if (direction * (arr[j].id - pivot.id) < 0) {
                    i++;
                    LogEntry temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            } else if (sortField == 2) {
                if (direction * (arr[j].importanceLevel - pivot.importanceLevel) < 0) {
                    i++;
                    LogEntry temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }

        LogEntry temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;

        quickSort(arr, low, pi - 1, compare, direction, sortField);
        quickSort(arr, pi + 1, high, compare, direction, sortField);
    }
}



// Функция для гномьей сортировки:


void gnomeSort(LogEntry *arr, int size, int (*compare)(const void *, const void *), int direction, int sortField) {
    int index = 0;

    while (index < size) {
        if (index == 0) {
            index++;
        } else {
            if (direction * compare(&arr[index - 1], &arr[index]) < 0) {  // если direction отрицательное - меняем условие
                index++;
            } else {
                LogEntry temp = arr[index];
                arr[index] = arr[index - 1];
                arr[index - 1] = temp;
                index--;

                if (sortField == 1) {
                    if (index == 0) {
                        index++;
                    }
                }
            }
        }
    }
}





// Функция для сортировки Шелла:

void shellSort(LogEntry *arr, int size, int (*compare)(const void *, const void *), int direction, int sortField) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            LogEntry temp = arr[i];
            int j;

            for (j = i; j >= gap; j -= gap) {
                if (sortField == 1) {
                    if (direction * (compare(&arr[j - gap], &temp)) > 0) {
                        arr[j] = arr[j - gap];
                    } else {
                        break;
                    }
                } else if (sortField == 2) {
                    if (direction * (compare(&arr[j - gap], &temp)) > 0) {
                        arr[j] = arr[j - gap];
                    } else {
                        break;
                    }
                }
            }

            arr[j] = temp;
        }
    }
}





int main(){
    int n; // n - количество элементов
    int Field; // поле, по которому осуществляется сортировка
    printf("Введите количество сравниваемых структур: ");
    scanf("%d", &n);
    LogEntry logs[n];

    int choice, choice1, choice2;
    int sign = 1;

    // printf("Выберите ввод массива:\n");
    // printf("1. с клавиатуры\n");
    // printf("2. из текстового файла\n");
    // printf("3. из бинарного файла\n");
    // scanf("%d", &choice1);

    // if (choice1 == 1){
    //  fillArray(arr1, n);
    // }

    // if (choice1 == 2){
    //  char beg_name;
    //  fillArrayFromFile(arr2, n, &beg_name);
    // }

    while (1) {
        printf("\n___________________\n");
        printf("1. Выберите алгоритм сортировки. \n");
        printf("2. Введите поле структуры. \n");
        printf("3. Выберите направление сортировки. \n");
        printf("0. Выйти. \n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Выберите поле для сортировки:\n");
                printf("1. По идентификатору.\n");
                printf("2. По уровню важности.\n");
                scanf("%d", &Field);


                printf("Выберите сортировку:\n");
                printf("1. Быстрая сортировка (Quick sort):\n");
                printf("2. Гномья сортировка (Gnome sort):\n");
                printf("3. Сортировка Шелла (Shell sort):\n");
                scanf("%d", &choice1);

                if (choice1 == 1){
                    quickSort(logs, 0, n - 1, compare_ask, sign, Field);
                    printRes(logs, n);
                }

                if (choice1 == 2){
                    gnomeSort(logs, n, compare_ask, sign, Field);
                    printRes(logs, n);

                }

                if (choice1 == 3){
                    shellSort(logs, n, compare_ask, sign, Field);
                    printRes(logs, n);

                }

                break;
            case 2:

                for (int i = 0; i < n; i++) {
                    printf("Введите ID: ");
                    scanf("%d", &logs[i].id);
                    printf("Введите уровень важности (1 - debug, 2 - info, 3 - warn, 4 - error, 5 - fatal): ");
                    scanf("%d", &logs[i].importanceLevel);
                    printf("Введите текст: ");
                    scanf(" %[^\n]", logs[i].text);
                }


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
