#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int get_max(int array[], int n) {
    int max = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

void counting_sort(int array[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(array[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        array[i] = output[i];
}

void radixSort(int array[], int n) {
    int max = get_max(array, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
        counting_sort(array, n, exp);
}


int main() {
    srand(time(NULL));
    int array[MAX];

    for(int i = 0; i < MAX; i++) {
        array[i] = rand() % 1000;
    }

    int n = sizeof(array) / sizeof(array[0]);

    radixSort(array, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
