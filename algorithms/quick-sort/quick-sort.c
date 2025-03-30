#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for(int j = low; j < high; j++) {
        if(array[j] <= pivot) {
            i++;

            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;

    return i + 1;
}

void quicksort(int array[], int low, int high) {
    if(low < high) {
        int pivot_index = partition(array, low, high);

        quicksort(array, low, pivot_index - 1);
        quicksort(array, pivot_index + 1, high);
    }
}

int main() {
    srand(time(NULL));
    int array[MAX];

    for(int i = 0; i < MAX; i++) {
        array[i] = rand() % 1000;
    }

    quicksort(array, 0, MAX - 1);

    for(int i = 0; i < MAX; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}