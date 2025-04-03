#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

void connect(char array[], int adjacency_matrix[][SIZE], char a, char b, int weight, int both) {
    int a_index = -1, b_index = -1;
    for (int i = 0; i < SIZE; i++) {
        if (array[i] == a) {
            a_index = i;
        }
        if (array[i] == b) {
            b_index = i;
        }
    }

    if (a_index == -1 || b_index == -1) {
        return;
    }

    adjacency_matrix[a_index][b_index] = weight;

    if (both) {
        adjacency_matrix[b_index][a_index] = weight;
    }
}

void reset(int adjacency_matrix[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            adjacency_matrix[i][j] = 0;
        }
    }
}

int is_directed(int adjacency_matrix[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (adjacency_matrix[i][j] != adjacency_matrix[j][i]) {
                return 1;
            }
        }
    }
    return 0;
}

void print_adjacency_matrix(char array[], int adjacency_matrix[][SIZE], int size) {
    printf("  ");
    for (int i = 0; i < size; i++) {
        printf("%c ", array[i]);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%c ", array[i]);
        for (int j = 0; j < size; j++) {
            printf("%d ", adjacency_matrix[i][j]);
        }
        printf("\n");
    }
}

int has_loop(int adjacency_matrix[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if(adjacency_matrix[i][i] != 0) {
            return 1;
        }
    }
    
    return 0;
}

int main() {
    char array[] = { 'A', 'B', 'C', 'D', 'E', 'F' };

    int adjacency_matrix[SIZE][SIZE] = {0};

    connect(array, adjacency_matrix, 'A', 'B', 1, 1);

    print_adjacency_matrix(array, adjacency_matrix, SIZE);

    printf("%d", has_loop(adjacency_matrix));

    return 0;
}
