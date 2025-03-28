#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

/*
    ALGORITHM: Bubble sort
    time complexity: O(n²)
*/

int main() {
    srand(time(NULL));
    int array[MAX];

    // create unsorted array
    for(int i = 0; i < MAX; i++) {
        array[i] = rand() % 10000;
    }

    // bubble sort
    for(int i = 0; i < MAX - 1; i++) {
        int swapped = 0; // 0 = false

        for(int j = 0; j < MAX - i - 1; j++) {
            if(array[j] > array[j + 1]) {
                int temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
                swapped = 1;
            }
        }
        
        if(!swapped) {
            break;
        }
    }
    
    // show
    for(int i = 0; i < MAX; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");
    return 0;
}