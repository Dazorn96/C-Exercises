#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void SelectionSort(int *array, int size);
int GetArrayMinIndex(int *array, int from, int to);
void PrintArray(int *array, int size);

void main()
{
    int *array = malloc(sizeof(int) * 10);

    srand(time(NULL));

    for(int i = 0; i < 10; i++) {
        array[i] = rand() % 100;
    }

    SelectionSort(array, 10);
}

void SelectionSort(int *array, int size) {
    PrintArray(array, size);

    for(int i = 0; i < size; i++) {
        int m = GetArrayMinIndex(array, i, size - 1);

        printf("CHOSEN %d AS MINIMUM VALUE\n\n", array[m]);

        int temp = array[i];
        array[i] = array[m];
        array[m] = temp;

        PrintArray(array, size);
    }
}

int GetArrayMinIndex(int *array, int from, int to) {
    int m = from;

    for(int i = from + 1; i <= to; i++) {
        if(array[i] < array[m]) {
            m = i;
        }
    }

    return m;
}

void PrintArray(int *array, int size) {
    printf("_____ ARRAY STATUS _____\n");

    for(int i = 0; i < size; i++) {
        printf("%d", array[i]);
        
        if(i + 1 < size) {
            printf(" - ");
        }
    }

    printf("\n\n");
}