#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

/*
    ALGORITHM: Insert sort
*/

int main() {
    srand(time(NULL));
    int array[MAX];

    // create unsorted array
    for(int i = 0; i < MAX; i++) {
        array[i] = rand() % 1000;
    }

    // insert sort
    for(int i = 1; i < MAX; i++) {
        int insert_index = i;
        int current_value = array[insert_index]; // value to be inserted

        // move bigger elements to the right
        // while j is bigger than 0 and element is bigger than current value
        for(int j = i - 1; j >= 0 && array[j] > current_value; j--) {
            array[j + 1] = array[j];
            insert_index = j;
        }

        array[insert_index] = current_value; // insert value to the correct position
    }

    // show
    for(int i = 0; i < MAX; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}