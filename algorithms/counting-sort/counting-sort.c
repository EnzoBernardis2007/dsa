#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
int max_value(int array[], int size) {
    int max_value = array[0];

    for(int i = 0; i < size; i++) {
        if(array[i] > max_value) {
            max_value = array[i];
        }
    }

    return max_value;
}

int main() {
    srand(time(NULL));
    int array[MAX];

    // initialize unsorted array
    for (int i = 0; i < MAX; i++) {
        array[i] = rand() % 10;
    }

    int size = max_value(array, MAX) + 1;
    int count_array[size];
    
    // initialize count array
    for (int i = 0; i < size; i++) {
        count_array[i] = 0;
    }

    for (int i = 0; i < MAX; i++) {
        count_array[array[i]]++;
    }
    
    for (int i = 0; i < size; i++) {
        printf("Number %d appeared %d times\n", i, count_array[i]);
    }
    
    return 0;
}