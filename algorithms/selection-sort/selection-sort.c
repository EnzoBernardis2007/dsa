#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

/*
    ALGORITHM: Selection Sort
*/

int main() {
    srand(time(NULL));
    int array[MAX];

    // create unsorted array
    for (int i = 0; i < MAX; i++) {
        array[i] = rand() % 10000;
    }

    // selection sort
    for (int i = 0; i < MAX - 1; i++) { 
        int index_lowest_value = i;  

        for (int j = i + 1; j < MAX; j++) {
            if (array[j] < array[index_lowest_value]) {
                index_lowest_value = j;
            }
        }

        if (index_lowest_value != i) {
            int temp = array[i];
            array[i] = array[index_lowest_value];
            array[index_lowest_value] = temp;
        }
    }

    // show
    for (int i = 0; i < MAX; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
