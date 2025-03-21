#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_SET_SIZE 100

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node *hashSet[HASH_SET_SIZE] = {NULL};

int hashFunction(const char *value) {
    int sum = 0;
    for (int i = 0; value[i] != '\0'; i++) {
        sum += value[i];
    }
    return sum % HASH_SET_SIZE;
}

bool search(const char *value) {
    int index = hashFunction(value);
    Node* current = hashSet[index];

    while(current != NULL) {
        if(strcmp(current->value, value) == 0) {
            return true;
        }

        current = current->next;
    }

    return false;
}

void add(const char *value) {
    if(search(value)) {
        printf("%s is already in the hash set\n", value);
        return;
    }
    
    int index = hashFunction(value);
    Node *current = hashSet[index];

    while(current != NULL) {
        if(strcmp(current->value, value) == 0) {
            return;
        }
        current = current->next;
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = strdup(value);
    newNode->next = hashSet[index];
    hashSet[index] = newNode;
}

void delete(const char *value) {
    int index = hashFunction(value);
    Node* current = hashSet[index];
    Node* prev = NULL;

    while(current != NULL) {
        if(strcmp(current->value, value) == 0) {
            if(prev == NULL) {
                hashSet[index] = current->next;
            } else {
                prev->next = current->next;
            }

            free(current->value);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("No %s found\n", value);
}

int size() {
    int count = 0;
    for(int i = 0; i < HASH_SET_SIZE; i++) {
        Node* current = hashSet[i];

        while(current != NULL) {
            count++;
            current = current->next;
        }
    }

    return count;
}

void show() {
    for(int i = 0; i < HASH_SET_SIZE; i++) {
        printf("%d: ", i);

        Node* current = hashSet[i];
        while (current != NULL) {
            printf("%s -> ", current->value);
            current = current->next;
        }
        
        printf("NULL\n");
    }
}

int main() {
    add("Bob");
    add("Adele");
    add("Amanda");
    add("Stuart");
    add("Stuart");

    show();
    return 0;
}